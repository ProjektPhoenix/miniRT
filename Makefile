NAME		:= miniRT
CFLAGS_prod	:= -Wall -Wextra -Werror -Ofast
CFLAGS_gdb	:= -Wall -Wextra -Werror -g -Wunreachable-code -O3 
CFLAGS_dev	:= -Wall -Wextra -Werror -Wunreachable-code -fsanitize=address -O3
LIBFTDIR	:= srcs/libft
LIBFT		:= ${LIBFTDIR}/libft.a

ifeq ($(shell uname), Linux)
MINILIBXDIR	:= minilibx-linux
LIBS		:= -L./${MINILIBXDIR} -lmlx \
			-L/lib/ -lX11 -lXext -lm\
			-L./${LIBFTDIR} -lft
else
MINILIBXDIR	:= minilibx_opengl
LIBS		:= -L./${MINILIBXDIR} -lmlx \
			-framework OpenGL -framework AppKit -lm \
			-L./${LIBFTDIR} -lft
endif

MINILIBX	:= ${MINILIBXDIR}/libmlx.a
INCL		:= -Iincludes -Iusr/include -I${LIBFTDIR} -I${MINILIBXDIR}
SRCS		:= srcs/main.c srcs/exits.c srcs/input/parsing.c srcs/input/parsing_utils.c srcs/input/process_utils.c \
			srcs/display/window_mngmt.c srcs/display/loop.c srcs/display/draw_image.c \
			srcs/vector_utils/vector_math.c srcs/hit_points/hit_objects.c srcs/display/viewport_and_canvas.c \
      		srcs/color/colors.c srcs/hit_points/find_closest.c srcs/color/color_light_utils.c \
			srcs/hit_points/cylinder.c srcs/input/init_helper.c srcs/input/error_check.c srcs/input/process_input.c
OBJS		:= ${SRCS:.c=.o}
SHELL		:= /bin/bash
HDS		:= 
RM		:= rm -rf
# Change to clang to ensure same behavior on non-school terminals
CC		:= cc

GREEN_LIGHT 	:= \033[38;5;120m
RESET 		:= \033[0m

# debug-specific compilation flags (`MODE=gdb MODE=dev MODE=plain`)
ifeq ($(MODE),gdb)
 CFLAGS = ${CFLAGS_gdb}
else ifeq ($(MODE),dev)
 CFLAGS = ${CFLAGS_dev}
else
 CFLAGS = ${CFLAGS_prod}
endif

define progress_bar
    @total=$$(($(words $(SRCS)))); \
    count=1; \
    while [ $$count -le $$total ]; do \
        src=$$(echo $(SRCS) | cut -d' ' -f$$count); \
        percentage=$$((count * 100 / total)); \
        bar=""; \
        n=0; \
        while [ $$n -lt $$((percentage / 5)) ]; do \
            bar=$${bar}#; \
            n=$$((n + 1)); \
        done; \
        printf "\r$(BOLD)$(GREEN_LIGHT)[%-20s] %d%%$(RESET)" "$$bar" "$$percentage"; \
        obj=$${src%.c}.o; \
        $(CC) $(CFLAGS) $(INCL) -c $$src -o $$obj; \
        count=$$((count + 1)); \
    done; \
    echo ""
endef

all: ${NAME}

${NAME}: ${OBJS} ${LIBFT} ${MINILIBX}
	@${CC} ${OBJS} ${LIBS} -o ${NAME}
	@${RM} ${OBJS}

${LIBFT}:
	@make -C ${LIBFTDIR} &> /dev/null \
	&& printf "Building libft.a\n"

${MINILIBX}:
	@make -C $(MINILIBXDIR) &> /dev/null \
	&& printf "Building libmlx.a\n"

%.o : %.c
	$(progress_bar)
	
clean:
	@${RM} ${OBJS} \
	&& printf "Removing program object files.\n"
	@${MAKE} -C ${MINILIBXDIR} clean \
	&& printf "Removing minilibx object files"
	@${MAKE} -C ${LIBFTDIR} clean \
	&& printf "Removing any object and temporary files.\n"

fclean: clean
	@${RM} ${NAME} ${LIBFT} ${MINILIBX}

re: fclean all

.PHONY: all clean fclean re

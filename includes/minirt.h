#ifndef MINIRT_H
# define MINIRT_H

#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <errno.h>
#include <stdlib.h>
#include <stdbool.h>
#include "vector_setup.h"
#include "vector_math.h"
#include "mlx_wrapper.h"
#include "scene.h"

# define WIN_TITLE "miniRT"
# define TITLEBAR_HEIGHT 10;

typedef struct	s_pxl {
	int	a;
	int	b;
	t_color	color;
}	t_pxl;

typedef struct s_viewp
{
	int		height;
	int		width;
	t_vec	dir_x;
	t_vec	dir_y;
	t_ray	**ray;
}	t_viewp;

typedef struct	s_minirt
{
	t_interface	screen;
	t_scene		scene;
	t_viewp		vp;
	t_img		img;
}	t_minirt;

/* utils */
void	calculate_rays(t_minirt *rt);
void	cleanup_exit(t_minirt *rt, char *mssg, int status);
void	cleanup_scene(t_scene *scene);
void	cleanup_scene_exit(t_scene *scene, char *mssg, int status);
void	draw_image(t_minirt *rt);
bool	draw_pixel(t_img *img, t_pxl *pxl);
int		error_return(char *mssg);
int		error_exit(char *mssg);
int		error_exit_status(char *mssg, int status);
void	free_array(char **str);
int		ft_key_hook(int keycode, t_minirt *rt);
bool	init_img(t_minirt *rt);
int		init_mlx_interface(t_minirt *rt);
int		loop_cleanup(t_minirt *rt);
void	minirt_init_loop(t_minirt *rt);

#endif 

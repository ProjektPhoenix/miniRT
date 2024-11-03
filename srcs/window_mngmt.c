/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window_mngmt.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpriess <rpriess@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 14:25:07 by rpriess           #+#    #+#             */
/*   Updated: 2024/11/03 18:34:04 by rpriess          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mlx.h>
#include <interface.h>
#include <error.h>
#include <stddef.h>

# define WIN_TITLE "miniRT"

typedef struct	s_pxl {
	int	x;
	int	y;
	t_vec	color;
} t_pxl;

/*
 * Input: image struct to write to, coordinate of pxl in image and pxl color.
 * Function modifies img content.
 * Returns: "0" upon success, "1" if pxl coordinates are outside image boundaries,
 * "2" if color information cannot be interpreted and "3" in case of other errors.
 */
static bool	draw_pixel(t_img *img, t_pxl *pxl)
{
	unsigned int	color;

	color = uint_color_from_rgb(pxl->color, "endian");
	
	if (pxl->x > img_main->width || pxl->y > img_main->height)
		return (1);
	ft_memcpy(img_main->content + (y * img_main->line + x * img_main->bpp / 8), color, img_main->bpp / 8);
	return (0);
}

static void	draw_frame(t_img *img, t_color *color, int width)
{
	
}

/*
 * the function allows to save an mlx image to an xpm image file, which can be
 * viewed later using other means. Files are saved in a hidden directory ".output"
 * relative to the working directory.
 */
void	save_img_to_xpm()
{
	
}

void	init_interface(t_interface *screen)
{
	screen->mlx = NULL;
	screen->mlx = mlx_init();
	if (!screen->mlx)
		strerror("MLX could not be initialized");
	// get_screen_size()
	screen->width = 600;
	screen->height = 400;
	screen->win_ptr = NULL;
	screen->img_content = NULL;
	
}

void	*create_new_window(t_interface *screen, char* win_title)
{
	screen->win_ptr = mlx_new_window(screen->mlx, screen->width, screen->height, win_title);
	if (!screen->win_ptr)
		return (NULL);
	return (screen->win_ptr);
}

int	main()
{
	t_interface	screen;
	t_img		img_main;

	init_interface(&screen);
	if (!create_new_window(&screen, WIN_TITLE))
		return (1);
	screen.img_ptr = mlx_new_image(screen.mlx, screen.width, screen.height);
	if (!screen.img_ptr)
		return (2);
	screen.img_content = mlx_get_data_addr(screen.img_ptr, &screen.img_bpp, &screen.img_line, &screen.img_endian);

	write_img(&screen)
	destroy_img
	destroy_win
}

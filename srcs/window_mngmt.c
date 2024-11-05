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

#include "vector_setup.h"
#include "miniRT.h"
#include <mlx.h>
#include <mlx_wrapper.h>
#include <error.h>
#include <stdbool.h>
#include <libft.h>

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
// static bool	draw_pixel(t_img *img, t_pxl *pxl)
// {
// 	unsigned int	color;

// 	color = mlx_get_color_value()
	
// 	if (pxl->x > img->width || pxl->y > img->height)
// 		return (1);
// 	ft_memcpy(img->content + (pxl->y * img->line + pxl->x * img->bpp / 8), color, img->bpp / 8);
// 	return (0);
// }

// static void	draw_frame(t_img *img, t_color *color, int width)
// {
	
// }

/*
 * the function allows to save an mlx image to an xpm image file, which can be
 * viewed later using other means. Files are saved in a hidden directory ".output"
 * relative to the working directory.
 */
// void	save_img_to_xpm()
// {
	
// }

static void	init_img(t_img	*mlx_img)
{
	mlx_img->content = mlx_get_data_addr(mlx_img, &mlx_img->bpp, &mlx_img->line, &mlx_img->endian);
}

static void	init_interface(t_interface *screen)
{
	screen->mlx = NULL;
	screen->mlx = mlx_init();
	if (!screen->mlx)
		error_exit("MLX could not be initialized");
	// get_screen_size()
	screen->width = 900;
	screen->height = 600;
	screen->win = NULL;
}

static void	*create_new_window(t_interface *screen, char* win_title)
{
	screen->win = mlx_new_window(screen->mlx, screen->width, screen->height, win_title);
	if (!screen->win)
	{
		mlx_destroy_display(screen->mlx);
		error_exit("Creating MLX window failed.");
	}
	return (screen->win);
}

void	draw_image(t_minirt *rt)
{
	printf("Function draw_image.\n");
	// prepare_viewport()
	// draw_viewport_to_img()
	mlx_put_image_to_window(rt->screen.mlx, rt->screen.win, rt->img.ptr, 0, 0);
	printf("Image put to window returned.\n");
}

int	init_mlx_interface(t_minirt *rt)
{
	init_interface(&rt->screen);
	create_new_window(&rt->screen, WIN_TITLE);
	rt->img.ptr = mlx_new_image(rt->screen.mlx, rt->screen.width, rt->screen.height - 70);
	if (!rt->img.ptr)
	{
		mlx_destroy_window(rt->screen.mlx, rt->screen.win);
		mlx_destroy_display(rt->screen.mlx);
		error_exit("Creating MLX img failed.");
	}
	init_img(&rt->img);
	return (0);
}

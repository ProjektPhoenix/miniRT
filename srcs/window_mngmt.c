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

void	init_img(t_minirt *rt)
{
	rt->img.width = rt->screen.width;
	rt->img.height = rt->screen.height;
	rt->img.ptr = mlx_new_image(rt->screen.mlx, rt->img.width, rt->img.height);
	if (!rt->img.ptr)
	{
		mlx_destroy_window(rt->screen.mlx, rt->screen.win);
		mlx_destroy_display(rt->screen.mlx);
		error_exit("Creating MLX img failed.");
	}
	rt->img.content = mlx_get_data_addr(rt->img.ptr, &(rt->img.bpp), &(rt->img.line), &(rt->img.endian));
	printf("Init_img complete, results:\n");
	printf("Address of rt->img.ptr: %p\n", rt->img.ptr);
}

static bool	init_interface(t_interface *screen)
{
	screen->mlx = NULL;
	screen->mlx = mlx_init();
	if (!screen->mlx)
		return (false);
	// get_screen_size() // minus TITLEBAR_HEIGHT
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

int	init_mlx_interface(t_minirt *rt)
{
	if (!init_interface(&rt->screen))
		cleanup_scene_exit(&(rt->scene), "MLX could not be initialized", 1);
	create_new_window(&rt->screen, WIN_TITLE);
	init_img(rt);
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window_mngmt.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpriess <rpriess@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 14:25:07 by rpriess           #+#    #+#             */
/*   Updated: 2025/01/24 21:27:45 by rpriess          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector_setup.h"
#include "minirt.h"
#include "error_utils.h"
#include <mlx.h>
#include <mlx_wrapper.h>
#ifdef __LINUX__
# include <error.h>
#endif
#include <stdbool.h>
#include <libft.h>

#include "debug.h"

bool	init_img(t_minirt *rt)
{
	rt->img.width = rt->screen.width;
	rt->img.height = rt->screen.height;
	rt->img.ptr = mlx_new_image(rt->screen.mlx, \
								rt->img.width, rt->img.height);
	if (!rt->img.ptr)
		return (false);
	rt->img.content = mlx_get_data_addr(rt->img.ptr, &(rt->img.bpp), \
										&(rt->img.line), &(rt->img.endian));
	return (true);
}

static bool	init_interface(t_interface *screen)
{
	int	x;
	int	y;

	x = 0;
	y = 0;
	screen->mlx = NULL;
	screen->mlx = mlx_init();
	if (!screen->mlx)
		return (false);
	mlx_get_screen_size(screen->mlx, &x, &y);
	if (x > 0 && y > 0)
	{
		screen->width = x * WIDTH_RATIO;
		screen->height = y * HEIGHT_RATIO;
	}
	else
	{
		screen->width = 900;
		screen->height = 600;
	}
	screen->win = NULL;
	return (true);
}

static bool	create_new_window(t_interface *screen, char *win_title)
{
	screen->win = mlx_new_window(screen->mlx, screen->width, \
									screen->height, win_title);
	if (!screen->win)
		return (false);
	return (true);
}

int	init_mlx_interface(t_minirt *rt)
{
	if (!init_interface(&rt->screen))
		cleanup_scene_exit(&(rt->scene), "MLX could not be initialized.", 1);
	if (!create_new_window(&rt->screen, WIN_TITLE))
	{
		cleanup_scene(&(rt->scene));
		#ifdef __linux__
		mlx_destroy_display(rt->screen.mlx);
		#endif
		free(rt->screen.mlx);
		error_exit_status("Creating MLX window failed.", 1);
	}
	if (!init_img(rt))
	{
		cleanup_scene(&(rt->scene));
		mlx_destroy_window(rt->screen.mlx, rt->screen.win);
		#ifdef __linux__
		mlx_destroy_display(rt->screen.mlx);
		#endif
		free(rt->screen.mlx);
		error_exit_status("Creating MLX img failed.", 1);
	}
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window_mngmt.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Henriette <Henriette@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 14:25:07 by rpriess           #+#    #+#             */
/*   Updated: 2024/12/02 19:29:21 by Henriette        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector_setup.h"
#include "minirt.h"
#include <mlx.h>
#include <mlx_wrapper.h>
#ifdef __LINUX__
	#include <error.h>
#endif
#include <stdbool.h>
#include <libft.h>

#include "debug.h"

bool	init_img(t_minirt *rt)
{
	rt->img.width = rt->screen.width;
	rt->img.height = rt->screen.height;
	rt->img.ptr = mlx_new_image(rt->screen.mlx, rt->img.width, rt->img.height);
	if (!rt->img.ptr)
		return (false);
	rt->img.content = mlx_get_data_addr(rt->img.ptr, &(rt->img.bpp), &(rt->img.line), &(rt->img.endian));
	debug("Defined image size: width - %i, height - %i", rt->img.width, rt->img.height);
	return (true);
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
	return (true);
}

static bool	create_new_window(t_interface *screen, char* win_title)
{
	screen->win = mlx_new_window(screen->mlx, screen->width, screen->height, win_title);
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
		error_exit_status("Creating MLX window failed.", 1);
	}
	if (!init_img(rt))
	{
		cleanup_scene(&(rt->scene));
		mlx_destroy_window(rt->screen.mlx, rt->screen.win);
		#ifdef __linux__
			mlx_destroy_display(rt->screen.mlx);
		#endif
		error_exit_status("Creating MLX img failed.", 1);
	}
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hzimmerm <hzimmerm@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 20:07:30 by rpriess           #+#    #+#             */
/*   Updated: 2025/01/21 13:24:47 by hzimmerm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mlx.h>
#ifdef __linux__
	#include <X11/Xlib.h>
#elif __APPLE__
	#include <OpenGL/gl.h>
#endif
#include <libft.h>
#include "minirt.h"
#include "debug.h"

/*
static void	check_modifier_keycodes(t_spine *spine, int keycode)
{
	if (keycode == 'a' || keycode == 'A')
		spine->map.yaw_angle = -0.392699081698724;
	if (keycode == 'd' || keycode == 'D')
		spine->map.yaw_angle = 0.392699081698724;
	if (keycode == 'w' || keycode == 'W')
		spine->map.roll_angle = 0.392699081698724;
	if (keycode == 's' || keycode == 'S')
		spine->map.roll_angle = -0.392699081698724;
	if (keycode == 'l' || keycode == 'L')
		spine->map.pitch_angle = 0.392699081698724;
	if (keycode == 'k' || keycode == 'K')
		spine->map.pitch_angle = -0.392699081698724;
	if (keycode == '+' || keycode == '=' || keycode == 'i' || keycode == 'I')
		spine->map.spacing = spine->map.spacing / 1.2;
	if (keycode == '-' || keycode == '_' || keycode == 'o' || keycode == 'O')
		spine->map.spacing = spine->map.spacing * 1.2;
}*/

int	ft_key_hook(int keycode, t_minirt *rt)
{
	debug("");
	if (keycode == 0xff1b || keycode == 'q' || keycode == 53)
		cleanup_exit(rt, NULL, 0);
	// check_modifier_keycodes(spine, keycode);
	// if (keycode == 'r' || keycode == 'R')
	// 	reset_projection(rt);
	// minirt_redraw(rt);
    // draw_image(rt);
	return (0);
}

void	minirt_init_loop(t_minirt *rt)
{
	debug("loop init");
	mlx_key_hook(rt->screen.win, ft_key_hook, rt);
	#ifdef __linux__
		mlx_hook(rt->screen.win, DestroyNotify, \
					NoEventMask, loop_cleanup, rt);
	#elif __APPLE__
		mlx_hook(rt->screen.win, 17, 0, loop_cleanup, rt);
	#endif
	mlx_loop(rt->screen.mlx);
}

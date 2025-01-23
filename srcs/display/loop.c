/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpriess <rpriess@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 20:07:30 by rpriess           #+#    #+#             */
/*   Updated: 2025/01/23 22:30:11 by rpriess          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mlx.h>
#ifdef __linux__
# include <X11/Xlib.h>
#elif __APPLE__
# include <OpenGL/gl.h>
#endif
#include <libft.h>
#include "minirt.h"
#include "debug.h"

int	ft_key_hook(int keycode, t_minirt *rt)
{
	debug("");
	if (keycode == 0xff1b || keycode == 'q' || keycode == 53)
		cleanup_exit(rt, NULL, 0);
	if (keycode == 'r' || keycode == 'R')
		draw_image(rt);
	return (0);
}

void	minirt_init_loop(t_minirt *rt)
{
	debug("loop init");
	mlx_key_hook(rt->screen.win, ft_key_hook, rt);
	mlx_hook(rt->screen.win, 17, 0, loop_cleanup, rt);
	mlx_loop(rt->screen.mlx);
}

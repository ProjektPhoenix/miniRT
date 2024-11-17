/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   viewport_and_canvas.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpriess <rpriess@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/17 18:08:15 by rpriess           #+#    #+#             */
/*   Updated: 2024/11/17 19:37:03 by rpriess          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"
#include "vector_setup.h"
#include "vector_math.h"
#include <math.h>

static t_vec	get_viewport_upper_left()
{
	
}

static t_vec	get_viewport_center()
{
	
}

static double	get_viewport_width(t_scene *scene)
{
	double	width;

	width = 2 * sin(scene->camera.fov * M_PI / 180.0);
	return (width);
}

static double	get_viewport_height(t_img *img, double width)
{
	double	height;

	height = width * img->height / img.width;
	return (width);
}

//static t_vec	get_

static void	calculate_rays(t_minirt *rt)
{
	int		a;
	int		b;
	t_vec	vp_center;
	t_ray	temp_ray;

	a = 0;
	b = 0;
	temp_ray.orig = rt->scene->camera.pos;
	rt->
	while (b < rt->img.height)
	{
		while (a < rt->img.width)
		{
			
			temp_ray.dir = vec1_minus_vec2();
			
			a++;
		}
		a = 0;
	}
}

void	init_viewport(t_minirt *rt)
{
	rt->vp.width = get_viewport_width(rt->scene);
	rt->vp.height = get_viewport_height(rt->img, rt->vp.width);
//	rt->vp.dir_x = 
}

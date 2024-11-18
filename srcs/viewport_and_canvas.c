/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   viewport_and_canvas.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hzimmerm <hzimmerm@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/17 18:08:15 by rpriess           #+#    #+#             */
/*   Updated: 2024/11/18 21:31:12 by hzimmerm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "vector_setup.h"
#include "vector_math.h"
#include "scene.h"
#include <math.h>

// static t_vec	get_viewport_width_uvec()
// {
// 	t_vec	width_uvec;
// 	t_point	vp_ur;
// 	t_point	vp_ul;

// 	vp_ul = C + vp_uvec + z + height/2
// 	vp_ur = 

// 	width_uvec = get_unit_vector()
// 	return (width_uvec);
// }

// static	t_vec	get_viewport_height_uvec()
// {
// 	t_point;
// }

// static t_point	get_viewport_upper_left()
// {
	
// }

// static t_point	get_viewport_center(t_scene)
// {
	
// }

// static double	get_viewport_width(t_scene *scene)
// {
// 	double	width;

// 	width = 2 * tan(scene->camera.fov * M_PI / 360.0);
// 	return (width);
// }

// static double	get_viewport_height(t_img *img, double width)
// {
// 	double	height;

// 	height = width * img->height / img->width;
// 	return (height);
// }

//static t_vec	get_

void	calculate_rays(t_minirt *rt)
{
	t_ray	ray;
	t_pxl	pxl;
	double	y;
	double	z;

	ray.orig.e[0] = 0;
	ray.dir.e[0] = 1;
	ray.dir.e[1] = 0;
	ray.dir.e[2] = 0;
	pxl.a = 0;
	pxl.b = 0;
	z = -15;
	y = -20;
	while (z <= 10)
	{
		while (y <= 20)
		{
			ray.orig.e[1] = y;
			ray.orig.e[2] = z;
			pxl.color = get_ray_color(&ray, &(rt->scene));
			draw_pixel(rt->img.ptr, &pxl);
			y = y + 40/900;
			(pxl.a)++;
		}
		y = -20;
		z = z + 25/600;
		(pxl.b)++;
	}
}

// static void	calculate_rays(t_minirt *rt)
// {
// 	int		a;
// 	int		b;
// 	t_vec	vp_center;
// 	t_ray	temp_ray;

// 	a = 0;
// 	b = 0;
// 	temp_ray.orig = rt->scene.camera.pos;
// 	rt->
// 	while (b < rt->img.height)
// 	{
// 		while (a < rt->img.width)
// 		{
			
// 			temp_ray.dir = vec1_minus_vec2();
			
// 			a++;
// 		}
// 		a = 0;
// 	}
// }

// void	init_viewport(t_minirt *rt)
// {
// 	rt->vp.width = get_viewport_width(rt->scene);
// 	rt->vp.height = get_viewport_height(rt->img, rt->vp.width);
// //	rt->vp.dir_x = 
// }

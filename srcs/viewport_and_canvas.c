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

#include "debug.h"

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

static t_vec	get_viewport_delta_h(t_minirt *rt)
{
	t_vec	delta_h;
	t_vec	delta_w;
	t_vec	camdir;

	delta_w = rt->vp.delta_w;
	camdir = rt->scene.camera.dir;
	if (delta_w.e[1] != 0 && camdir.e[2] != 0)
	{
		delta_h.e[0] = sqrt(1 / (1.0 + pow(delta_w.e[0], 2)/pow(delta_w.e[1], 2) + pow(camdir.e[0]/camdir.e[2] - camdir.e[1] * delta_w.e[0] / (delta_w.e[1] * camdir.e[2]), 2)));
		delta_h.e[1] = -1.0 * delta_w.e[0] * delta_h.e[0] / delta_w.e[1];
		delta_h.e[2] = sqrt(1.0 - pow(delta_h.e[0], 2) - pow(delta_h.e[1], 2));
	}
	else if (camdir.e[2] == 0)
	{
		delta_h.e[0] = 0.0;
		delta_h.e[1] = 0.0;
		delta_h.e[2] = -1.0;
	}
	else if (delta_w.e[1] == 0)
	{
		delta_h.e[0] = 0.0;
		delta_h.e[1] = 1.0 / (1.0 + pow(camdir.e[1], 2) / pow(camdir.e[2], 2));
		delta_h.e[2] = -1.0 * delta_h.e[1] * camdir.e[1] / camdir.e[2];
	}
	debug("The viewport unit vector for traversing the height is: (%f,%f,%f)", delta_h.e[0], delta_h.e[1], delta_h.e[2]);
	return (delta_h);
}

/*
 * SONDERFÄLLE BERÜCKSICHTIGEN !!!
 */
static t_vec	get_viewport_delta_w(t_scene *scene)
{
	t_vec	delta_w;

	delta_w.e[2] = 0.0;
	if (scene->camera.dir.e[0] == 0 && scene->camera.dir.e[1] == 0)
	{
		delta_w.e[0] = 1.0;
		delta_w.e[1] = 0.0;
	}
	else
	{
		delta_w.e[0] = sqrt(pow(scene->camera.dir.e[1], 2) / (pow(scene->camera.dir.e[0], 2) + pow(scene->camera.dir.e[1], 2)));
		delta_w.e[1] = sqrt(1.0 - pow(delta_w.e[0], 2));
	}
	debug("The viewport unit vector for traversing the width is: (%f,%f,%f)", delta_w.e[0], delta_w.e[1], delta_w.e[2]);
	return (delta_w);
}

// static t_point	get_viewport_center(t_scene *scene)
// {
// 	t_point	vp_center;

// 	vp_center = add_vectors(scene->camera.pos, get_unit_vector(scene->camera.dir));
// 	return (vp_center);
// }

static double	get_viewport_width(t_scene *scene)
{
	double	width;

	width = 2 * tan(scene->camera.fov * M_PI / 360.0);
	debug("Viewport width is %f", width);
	return (width);
}

static double	get_viewport_height(t_img *img, double width)
{
	double	height;

	height = width * img->height / img->width;
	debug("Viewport height is %f", height);
	return (height);
}

//static t_vec	get_

void	calculate_rays(t_minirt *rt)
{
	t_ray	ray;
	t_pxl	pxl;
	double	y;
	double	z;

	debug("");
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
			// pxl.color.e[0] = 255;
			// pxl.color.e[1] = 50;
			// pxl.color.e[2] = 50;
			draw_pixel(&(rt->img), &pxl);
			y = y + 40.0/900.0;
			(pxl.a)++;
		}
		y = -20;
		z = z + 25.0/600.0;
		pxl.a = 0;
		(pxl.b)++;
	}
	debug("Calculated all rays");
}

static void	calculate_rays(t_minirt *rt)
{
	int		a;
	int		b;
	t_pxl	pxl_canvas;
	t_point	pxl_vp;
	t_ray	ray;

	pxl_canvas.a = 0;
	pxl_canvas.b = 0;
	ray.orig = rt->scene.camera.pos;
	while (pxl_canvas.b < rt->img.height)
	{
		while (pxl_canvas.a < rt->img.width)
		{
			pxl_vp.e[0] = 
			pxl_vp.e[1] =
			pxl_vp.e[2] = 
			ray.dir = get_unit_vector(vec1_minus_vec2(pxl_vp, rt->scene.camera.pos));
			pxl_canvas.color = get_ray_color(&ray, &(rt->scene));
			draw_pixel(&(rt->img), &pxl_canvas);
			pxl_canvas.a++;
		}
		pxl_canvas.a = 0;
		pxl_canvas.b++;
	}
}

void	init_viewport(t_minirt *rt)
{
	rt->vp.width = get_viewport_width(&(rt->scene));
	rt->vp.height = get_viewport_height(&(rt->img), rt->vp.width);
	rt->vp.delta_w = get_viewport_delta_w(&(rt->scene));
	rt->vp.delta_h = get_viewport_delta_h(rt);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   viewport_and_canvas.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hzimmerm <hzimmerm@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/17 18:08:15 by rpriess           #+#    #+#             */
/*   Updated: 2024/12/13 14:10:20 by hzimmerm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "vector_setup.h"
#include "vector_math.h"
#include "scene.h"
#include <libft.h>
#include <math.h>

#include "debug.h"

/*
 * SONDERFÄLLE BERÜCKSICHTIGEN !!!
 * CHECK AGAIN ALL CASES
 */
static t_vec	get_viewport_uvec_h(t_minirt *rt)
{
	t_vec	uvec_h;
	t_vec	uvec_w;
	t_vec	camdir;

	uvec_w = rt->vp.uvec_w;
	camdir = get_unit_vector(rt->scene.camera.dir);
	if (uvec_w.e[1] != 0 && camdir.e[2] != 0)
	{
		uvec_h.e[0] = sqrt(1 \
					/ (1.0 + pow(uvec_w.e[0], 2)/pow(uvec_w.e[1], 2) \
						+ pow(camdir.e[0]/camdir.e[2] - camdir.e[1] \
						* uvec_w.e[0] / (uvec_w.e[1] * camdir.e[2]), 2)));
		uvec_h.e[1] = ft_abs(uvec_w.e[0] * uvec_h.e[0] / uvec_w.e[1]);
		uvec_h.e[2] = -1 * sqrt(1.0 - pow(uvec_h.e[0], 2) \
								- pow(uvec_h.e[1], 2));
	}
	else if (camdir.e[2] == 0)
	{
		uvec_h.e[0] = 0.0;
		uvec_h.e[1] = 0.0;
		uvec_h.e[2] = -1.0;
	}
	else if (uvec_w.e[1] == 0)
	{
		uvec_h.e[0] = 0.0;
		uvec_h.e[1] = 1.0 / (1.0 + pow(camdir.e[1], 2) \
										/ pow(camdir.e[2], 2));
		uvec_h.e[2] = -1.0 * uvec_h.e[1] \
						* camdir.e[1] / camdir.e[2];
	}
	if ((camdir.e[0] > 0 && camdir.e[2] < 0) \
		|| (camdir.e[0] > 0 && camdir.e[2] < 0))
		uvec_h.e[0] = -1 * uvec_h.e[0];
	if ((camdir.e[1] > 0 && camdir.e[2] < 0) \
		|| (camdir.e[1] > 0 && camdir.e[2] < 0))
		uvec_h.e[1] = -1 * uvec_h.e[1];
	uvec_h = get_unit_vector(uvec_h);
	// debug("The viewport unit vector for traversing the height is: \
	// (%f,%f,%f)", uvec_h.e[0], uvec_h.e[1], uvec_h.e[2]);
	return (uvec_h);
}

/*
 * SONDERFÄLLE BERÜCKSICHTIGEN !!!
 * CHECK AGAIN ALL CASES
 */
static t_vec	get_viewport_uvec_w(t_scene *scene)
{
	t_vec	uvec_w;
	t_vec	camdir;

	camdir = get_unit_vector(scene->camera.dir);

	uvec_w.e[2] = 0.0;
	if (camdir.e[0] == 0 && camdir.e[1] == 0)
	{
		uvec_w.e[0] = 1.0;
		uvec_w.e[1] = 0.0;
	}
	else
	{
		uvec_w.e[0] = sqrt(pow(camdir.e[1], 2) \
					/ (pow(camdir.e[0], 2) + pow(camdir.e[1], 2)));
		uvec_w.e[1] = sqrt(1.0 - pow(uvec_w.e[0], 2));
	}
	if (camdir.e[0] < 0)
		uvec_w.e[1] = -1 * uvec_w.e[1];
	if (camdir.e[1] > 0)
		uvec_w.e[0] = -1 * uvec_w.e[0];
	uvec_w = get_unit_vector(uvec_w);
	// debug("The viewport unit vector for traversing the width is: \
	// (%f,%f,%f)", uvec_w.e[0], uvec_w.e[1], uvec_w.e[2]);
	return (uvec_w);
}

static t_point	get_ray_dir_from_canvas_pxl(t_minirt *rt, t_pxl pxl)
{
	t_viewp	vp;	
	t_point	vp_pxl;
	t_vec	ray_dir;																																																																																																																																																						

	vp = rt->vp;
	vp_pxl = add_multiple_vectors(3, vp.upperleft, \
					scalar_mply_vector((double)pxl.a + 0.5, vp.delta_w), \
					scalar_mply_vector((double)pxl.b + 0.5, vp.delta_h));
	ray_dir = get_unit_vector(vec1_minus_vec2(vp_pxl, rt->scene.camera.pos));
	return (ray_dir);
}

static double	get_viewport_width(t_scene *scene)
{
	double	width;

	width = 2 * tan(scene->camera.fov * M_PI / 360.0);
	return (width);
}

static double	get_viewport_height(t_img *img, double width)
{
	double	height;

	height = width * (double)img->height / (double)img->width;
	return (height);
}

// REMOVE BEFORE SUBMISSION
/*
static void	test_output_viewport_rays(t_minirt *rt)
{
	t_pxl	pxl_canvas;
	t_ray	ray;

	ray.orig = rt->scene.camera.pos;
	pxl_canvas.a = rt->img.width / 2;
	pxl_canvas.b = rt->img.height / 2;
	ray.dir = get_ray_dir_from_canvas_pxl(rt, pxl_canvas);
	debug("\nVIEWPORT: CENTRAL RAY\nPixel: (%d, %d)\nOrigin: \
			(%f, %f, %f), Direction: (%f, %f, %f)\n", \
			pxl_canvas.a, pxl_canvas.b, ray.orig.e[0], ray.orig.e[1], \
			ray.orig.e[2], ray.dir.e[0], ray.dir.e[1], ray.dir.e[2]);
	pxl_canvas.a = 0;
	pxl_canvas.b = 0;
	ray.dir = get_ray_dir_from_canvas_pxl(rt, pxl_canvas);
	debug("\nVIEWPORT: UPPER LEFT\nPixel: (%d, %d)\nOrigin: \
			(%f, %f, %f), Direction: (%f, %f, %f)\n", \
			pxl_canvas.a, pxl_canvas.b, ray.orig.e[0], ray.orig.e[1], \
			ray.orig.e[2], ray.dir.e[0], ray.dir.e[1], ray.dir.e[2]);
	pxl_canvas.a = rt->img.width;
	pxl_canvas.b = 0;
	ray.dir = get_ray_dir_from_canvas_pxl(rt, pxl_canvas);
	debug("\nVIEWPORT: UPPER RIGHT\nPixel: (%d, %d)\nOrigin: \
			(%f, %f, %f), Direction: (%f, %f, %f)\n", \
			pxl_canvas.a, pxl_canvas.b, ray.orig.e[0], ray.orig.e[1], \
			ray.orig.e[2], ray.dir.e[0], ray.dir.e[1], ray.dir.e[2]);
	pxl_canvas.a = 0;
	pxl_canvas.b = rt->img.height;
	ray.dir = get_ray_dir_from_canvas_pxl(rt, pxl_canvas);
	debug("\nVIEWPORT: LOWER LEFT\nPixel: (%d, %d)\nOrigin: \
			(%f, %f, %f), Direction: (%f, %f, %f)\n", \
			pxl_canvas.a, pxl_canvas.b, ray.orig.e[0], ray.orig.e[1], \
			ray.orig.e[2], ray.dir.e[0], ray.dir.e[1], ray.dir.e[2]);
	pxl_canvas.a = rt->img.width;
	pxl_canvas.b = rt->img.height;
	ray.dir = get_ray_dir_from_canvas_pxl(rt, pxl_canvas);
	debug("\nVIEWPORT: LOWER RIGHT\nPixel: (%d, %d)\nOrigin: \
			(%f, %f, %f), Direction: (%f, %f, %f)\n", \
			pxl_canvas.a, pxl_canvas.b, ray.orig.e[0], ray.orig.e[1], \
			ray.orig.e[2], ray.dir.e[0], ray.dir.e[1], ray.dir.e[2]);
}*/
/*
static void	test_selected_rays(t_minirt *rt)
{
	t_pxl	pxl_canvas;
	t_ray	ray;

	ray.orig = rt->scene.camera.pos;
	ray.dir = get_unit_vector(vec1_minus_vec2(create_triple(15,15,0), \
								ray.orig));
	pxl_canvas.color = get_ray_color(&ray, &rt->scene);
	draw_pixel(&(rt->img), &pxl_canvas);

	pxl_canvas.a = 500;
	pxl_canvas.b = 150;
	ray.dir = get_ray_dir_from_canvas_pxl(rt, pxl_canvas);
	pxl_canvas.color = get_ray_color(&ray, &(rt->scene));
	draw_pixel(&(rt->img), &pxl_canvas);

	pxl_canvas.a = 400;
	pxl_canvas.b = 150;
	ray.dir = get_ray_dir_from_canvas_pxl(rt, pxl_canvas);
	pxl_canvas.color = get_ray_color(&ray, &(rt->scene));
	draw_pixel(&(rt->img), &pxl_canvas);

	pxl_canvas.a = 450;
	pxl_canvas.b = 300;
	ray.dir = get_ray_dir_from_canvas_pxl(rt, pxl_canvas);
	pxl_canvas.color = get_ray_color(&ray, &(rt->scene));
	draw_pixel(&(rt->img), &pxl_canvas);
}*/

void	calculate_rays(t_minirt *rt)
{
	t_pxl	pxl_canvas;
	t_ray	ray;

	ray.orig = rt->scene.camera.pos;
	// test_output_viewport_rays(rt);
	// test_selected_rays(rt);
	pxl_canvas.a = 0;
	pxl_canvas.b = 0;
	while (pxl_canvas.b < rt->img.height)
	{
		while (pxl_canvas.a < rt->img.width)
		{
			ray.dir = get_ray_dir_from_canvas_pxl(rt, pxl_canvas);
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
	rt->vp.uvec_w = get_viewport_uvec_w(&(rt->scene));
	rt->vp.uvec_h = get_viewport_uvec_h(rt);
	rt->vp.delta_w = scalar_mply_vector(rt->vp.width \
						/ (double)rt->img.width, rt->vp.uvec_w);
	rt->vp.delta_h = scalar_mply_vector(rt->vp.height \
						/ (double)rt->img.height, rt->vp.uvec_h);
	rt->vp.upperleft = add_multiple_vectors(4, rt->scene.camera.pos, \
						get_unit_vector(rt->scene.camera.dir), \
						scalar_mply_vector(\
						-0.5 * rt->vp.width, rt->vp.uvec_w), \
						scalar_mply_vector(\
						-0.5 * rt->vp.height, rt->vp.uvec_h));
	debug("Viewport width: %f", rt->vp.width);
	debug("Viewport height: %f", rt->vp.height);
	debug("Viewport delta w: (%f, %f, %f)", \
			rt->vp.delta_w.e[0], rt->vp.delta_w.e[1], rt->vp.delta_w.e[2]);
	debug("Viewport delta h: (%f, %f, %f)", \
			rt->vp.delta_h.e[0], rt->vp.delta_h.e[1], rt->vp.delta_h.e[2]);
	debug("Calculated coordinates of viewport upper left corner: \
			(%f, %f, %f)", rt->vp.upperleft.e[0], rt->vp.upperleft.e[1], \
			rt->vp.upperleft.e[2]);
}

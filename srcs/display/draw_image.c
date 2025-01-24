/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_image.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpriess <rpriess@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 09:29:46 by rpriess           #+#    #+#             */
/*   Updated: 2025/01/23 22:15:23 by rpriess          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "mlx_wrapper.h"
#include <libft.h>
#include <mlx.h>
#include <stdbool.h>
#include <math.h>

#include "debug.h"
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
/*
 * Input: image struct to write to, coordinate of pxl in image and pxl color.
 * Function puts pixel color according to pxl coordinate into img content.
 */
static bool	draw_pixel(t_img *img, t_pxl *pxl)
{
	unsigned int	color;

	color = ft_rgb_color((int)pxl->color.e[0], \
						(int)pxl->color.e[1], (int)pxl->color.e[2]);

	if (pxl->a > img->width || pxl->b > img->height \
		|| pxl->a < 0 || pxl->b < 0)
		return (1);
	ft_memcpy(img->content + (pxl->b * img->line + pxl->a * img->bpp / 8), \
				&color, img->bpp / 8);
	return (0);
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

static void	calculate_rays(t_minirt *rt)
{
	t_pxl	pxl_canvas;
	t_ray	ray;

	ray.orig = rt->scene.camera.pos;
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

void	draw_image(t_minirt *rt)
{
	init_viewport(rt);
	init_helper(rt);
	calculate_rays(rt);
	mlx_put_image_to_window(rt->screen.mlx, rt->screen.win, \
							rt->img.ptr, 0, 0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   viewport.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpriess <rpriess@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/17 18:08:15 by rpriess           #+#    #+#             */
/*   Updated: 2025/01/24 16:14:18 by rpriess          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "vector_setup.h"
#include "vector_math.h"
#include "scene.h"
#include <libft.h>
#include <math.h>

#include "debug.h"


static t_vec	get_uvec_h_std_case(t_vec uvec_w, t_vec camdir)
{
	t_vec	uvec_h;

	uvec_h.e[0] = sqrt(1 / (1.0 + pow(uvec_w.e[0], 2) / pow(uvec_w.e[1], 2) \
					+ pow(camdir.e[0] / camdir.e[2] - camdir.e[1] \
					* uvec_w.e[0] / (uvec_w.e[1] * camdir.e[2]), 2)));
	uvec_h.e[1] = ft_abs(uvec_w.e[0] * uvec_h.e[0] / uvec_w.e[1]);
	uvec_h.e[2] = -1 * sqrt(1.0 - pow(uvec_h.e[0], 2) \
							- pow(uvec_h.e[1], 2));
	return (uvec_h);
}

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
		uvec_h = get_uvec_h_std_case(uvec_w, camdir);
	else if (camdir.e[2] == 0)
		uvec_h = create_triple(0.0, 0.0, -1.0);
	else if (uvec_w.e[1] == 0)
	{
		uvec_h.e[0] = 0.0;
		uvec_h.e[1] = 1.0 / \
						(1.0 + pow(camdir.e[1], 2) / pow(camdir.e[2], 2));
		uvec_h.e[2] = -1.0 * uvec_h.e[1] * camdir.e[1] / camdir.e[2];
	}
	if (camdir.e[0] > 0 && camdir.e[2] < 0)
		uvec_h.e[0] = -1 * uvec_h.e[0];
	if (camdir.e[1] > 0 && camdir.e[2] < 0)
		uvec_h.e[1] = -1 * uvec_h.e[1];
	uvec_h = get_unit_vector(uvec_h);
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
	return (uvec_w);
}

static void	set_viewport_dimensions(t_minirt *rt)
{
	rt->vp.width = 2 * tan(rt->scene.camera.fov * M_PI / 360.0);
	rt->vp.height = rt->vp.width \
					* (double)rt->img.height / (double)rt->img.width;
}

void	init_viewport(t_minirt *rt)
{
	set_viewport_dimensions(rt);
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
}

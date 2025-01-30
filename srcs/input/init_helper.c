/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_helper.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpriess <rpriess@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 22:11:40 by rpriess           #+#    #+#             */
/*   Updated: 2025/01/26 14:29:42 by rpriess          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "debug.h"
#include <stdbool.h>

static bool	camera_inside_cylinder(t_cylinder *cyl)
{
	double			dist_along_axis;
	double			dist_along_base;
	t_cyl_helper	c;

	c = cyl->c;
	dist_along_axis = dot_product(c.cyl_dir_unit, \
						vec1_minus_vec2(c.ray_orig, c.cyl_base));
	dist_along_base = get_magnitude(vec1_minus_vec2(vec1_minus_vec2(\
						c.ray_orig, c.cyl_base), \
						scalar_mply_vector(dot_product(vec1_minus_vec2(\
						c.ray_orig, c.cyl_base), c.cyl_dir_unit), \
						c.cyl_dir_unit)));
	if (dist_along_axis > 0 && dist_along_axis < cyl->height \
		&& dist_along_base < cyl->c.radius)
		return (true);
	return (false);
}

static void	init_cyl_helper(t_scene *scene)
{
	t_cylinder	*temp_cyl;

	temp_cyl = scene->cyl;
	while (temp_cyl)
	{
		temp_cyl->c.cyl_dir_unit = get_unit_vector(temp_cyl->dir);
		temp_cyl->c.cyl_base = vec1_minus_vec2(temp_cyl->center, \
								scalar_mply_vector(temp_cyl->height / 2, \
												temp_cyl->c.cyl_dir_unit));
		temp_cyl->c.cyl_top = add_vectors(temp_cyl->center, \
								scalar_mply_vector(temp_cyl->height / 2, \
												temp_cyl->c.cyl_dir_unit));
		temp_cyl->c.ray_orig = scene->camera.pos;
		temp_cyl->c.orig_to_base = vec1_minus_vec2(temp_cyl->c.cyl_base, \
													scene->camera.pos);
		temp_cyl->c.orig_to_top = vec1_minus_vec2(temp_cyl->c.cyl_top, \
													scene->camera.pos);
		temp_cyl->c.radius = temp_cyl->diameter / 2;
		temp_cyl->c.cam_inside = camera_inside_cylinder(temp_cyl);
		temp_cyl = temp_cyl->next;
	}
}

void	init_helper(t_minirt *rt)
{
	init_cyl_helper(&(rt->scene));
}

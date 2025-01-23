/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpriess <rpriess@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 16:30:37 by rpriess           #+#    #+#             */
/*   Updated: 2025/01/23 21:39:47 by rpriess          ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "vector_setup.h"
#include "vector_math.h"
#include "debug.h"
#include <math.h>
#include <stdbool.h>

void	find_intersetion_cyl_lids(t_cyl_helper *c, double *distance)
{
	double	temp;

	temp = -1.0;
	if (dot_product(c->cyl_dir_unit, c->ray_dir_unit) != 0)
	{
		temp = dot_product(c->cyl_dir_unit, c->orig_to_base) \
				/ dot_product(c->cyl_dir_unit, c->ray_dir_unit);
		if (temp >= 0 && (*distance == -1.0 || temp < *distance) \
			&& pow(get_magnitude(vec1_minus_vec2(scalar_mply_vector(temp, \
			c->ray_dir_unit), c->orig_to_base)), 2) <= pow(c->radius, 2))
		{
			*distance = temp;
			c->normal_v = scalar_mply_vector(-1, c->cyl_dir_unit);
		}
		temp = -1.0;
		temp = dot_product(c->cyl_dir_unit, c->orig_to_top) \
				/ dot_product(c->cyl_dir_unit, c->ray_dir_unit);
		if (temp >= 0 && (*distance == -1.0 || temp < *distance) \
			&& pow(get_magnitude(vec1_minus_vec2(scalar_mply_vector(temp, \
			c->ray_dir_unit), c->orig_to_top)), 2) <= pow(c->radius, 2))
		{
			*distance = temp;
			c->normal_v = c->cyl_dir_unit;
		}
	}
}

static double	dist_from_cyl_base(t_cyl_helper *c, double distance)
{
	double			dist_base;
	t_point			hit_point;

	dist_base = -1.0;
	hit_point = add_vectors(c->cam_pos, \
							scalar_mply_vector(distance, c->ray_dir_unit));
	dist_base = dot_product(c->cyl_dir_unit, \
							vec1_minus_vec2(hit_point, c->cyl_base));
	return (dist_base);
}

static void	check_solution_and_assign_normal_v(t_cyl_helper *c, \
							double *distance, double temp, double height)
{
	double	dist_base;

	dist_base = dist_from_cyl_base(c, temp);
	if (temp >= 0 && (*distance == -1.0 || temp < *distance)
		&& dist_base >= 0 && dist_base <= height)
	{
		*distance = temp;
		c->normal_v = get_unit_vector(vec1_minus_vec2(vec1_minus_vec2( \
					scalar_mply_vector(*distance, c->ray_dir_unit), \
					scalar_mply_vector(dist_base, c->cyl_dir_unit)), 
					c->cyl_base));
	}
}

/*
 * Returns closest distance on ray to cylinder tube if an intersection
 * exits, otherwise returns -1.0
 */
static double	find_intersection_cyl_tube(t_cyl_helper *c, double height)
{
	double	distance;
	double	discriminant;
	double	temp;
	double	b;
	t_vec	a;

	distance = -1.0;
	discriminant = -1.0;
	a = scalar_mply_vector(-1.0, \
							cross_product(c->ray_dir_unit, c->cyl_dir_unit));
	discriminant = dot_product(a, a) * c->radius * c->radius \
					- pow(dot_product(c->orig_to_base, a), 2);
	if (discriminant >= 0 && get_magnitude(a) != 0)
	{
		b = dot_product(a, scalar_mply_vector(-1.0, \
					cross_product(c->orig_to_base, c->cyl_dir_unit)));
		temp = (b + sqrtf(discriminant)) / dot_product(a, a);
		check_solution_and_assign_normal_v(c, &distance, temp, height);
		temp = (b - sqrtf(discriminant)) / dot_product(a, a);
		check_solution_and_assign_normal_v(c, &distance, temp, height);
	}
	return (distance);
}

/* 
 * takes as input a ray and a cylinder, 
 * returns -1.0 if no intersection has been found
 * returns 0 if camera is inside object or exactly on the surface
 * otherwise returns t for closest hitpoint.
 */
double	find_t_cylinder(t_ray *ray, t_cylinder *cyl)
{
	double			t;
	double			distance;
	t_cyl_helper	c;

	t = -1.0;
	distance = -1.0;
	c = cyl->c;
	c.ray_dir_unit = ray->dir;
	if (cyl->c.cam_inside)
		return (0);
	distance = find_intersection_cyl_tube(&c, cyl->height);
	find_intersetion_cyl_lids(&c, &distance);
	if (distance >= 0)
		t = distance;
	cyl->c = c;
	return (t);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hzimmerm <hzimmerm@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 16:30:37 by rpriess           #+#    #+#             */
/*   Updated: 2025/01/19 17:03:10 by hzimmerm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector_setup.h"
#include "vector_math.h"
#include "debug.h"
#include <math.h>
#include <stdbool.h>

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

/* takes as input a ray and a cylinder, 
 *	returns -1.0 if no intersection has been found
 *	returns 0 if camera is inside object or exactly on the surface
 *	otherwise returns t for closest hitpoint.
 */
double	find_t_cylinder(t_ray *ray, t_cylinder *cyl)
{
	double			t;
	double			temp;
	double			temp2;
	double			distance;
	t_cyl_helper	c;

	t = -1.0;
	temp = -1.0;
	temp2 = -1.0;
	distance = -1.0;
	c = cyl->c;
	c.ray_dir_unit = ray->dir;
	// debug("Cylinder direction unit vector: (%f,%f,%f)", \
	// 		c.cyl_dir_unit.e[0], c.cyl_dir_unit.e[1], c.cyl_dir_unit.e[2]);
	// debug("Ray direction unit vector: (%f,%f,%f)", \
	// 		ray->dir.e[0], ray->dir.e[1], ray->dir.e[2]);
	// debug("Cylinder base coordinates: (%f,%f,%f)", \
	// 		c.cyl_base.e[0], c.cyl_base.e[1], c.cyl_base.e[2]);
	// debug("Vector origin to cylinder base: (%f,%f,%f)", \
	// 		c.orig_to_base.e[0], c.orig_to_base.e[1], c.orig_to_base.e[2]);
	// debug("Cylinder radius: %f", c.radius);
	c.cross_ray_cyl = scalar_mply_vector(-1.0, \
							cross_product(ray->dir, c.cyl_dir_unit));
	// debug("Cross product ray and cyl direction: (%f,%f,%f)", \
	// 	c.cross_ray_cyl.e[0], c.cross_ray_cyl.e[1], c.cross_ray_cyl.e[2]);
	// debug("Value of discrimant components:\n\
	// 		dot product of cross ray/cyl with itself: \
	// 		%f\nRadius: %f\nDot product base and cross ray/cyl vector: %f", \
	// 		dot_product(c.cross_ray_cyl, c.cross_ray_cyl), \
	// 				c.radius, dot_product(c.orig_to_base, c.cross_ray_cyl));
	c.discriminant = dot_product(c.cross_ray_cyl, c.cross_ray_cyl) \
					* c.radius * c.radius \
					- pow(dot_product(c.orig_to_base, c.cross_ray_cyl), 2);
	if (cyl->c.cam_inside)
		return (0);
	if (c.discriminant >= 0 && get_magnitude(c.cross_ray_cyl) != 0)
	{
		distance = dot_product(c.cross_ray_cyl, \
					scalar_mply_vector(-1.0, \
					cross_product(c.orig_to_base, c.cyl_dir_unit)));
		temp = (distance + sqrtf(c.discriminant)) \
							/ dot_product(c.cross_ray_cyl, c.cross_ray_cyl);
		temp2 = (distance - sqrtf(c.discriminant)) \
							/ dot_product(c.cross_ray_cyl, c.cross_ray_cyl);
		if (temp2 >= 0 && dist_from_cyl_base(&c, temp2) >= 0 \
			&& dist_from_cyl_base(&c, temp2) <= cyl->height)
		{
			distance = temp2;
			c.normal_v = get_unit_vector(vec1_minus_vec2(vec1_minus_vec2(\
						scalar_mply_vector(distance, c.ray_dir_unit), \
						scalar_mply_vector(dist_from_cyl_base(&c, temp2), \
			c.cyl_dir_unit)), c.cyl_base));
		}
		else
			temp2 = -1.0;
		if (temp >= 0 && (temp2 < 0 || temp < temp2) \
			&& dist_from_cyl_base(&c, temp) >= 0 \
			&& dist_from_cyl_base(&c, temp) <= cyl->height)
		{
			distance = temp;
			c.normal_v = get_unit_vector(vec1_minus_vec2(vec1_minus_vec2(\
						scalar_mply_vector(distance, c.ray_dir_unit), \
						scalar_mply_vector(dist_from_cyl_base(&c, temp), \
						c.cyl_dir_unit)), c.cyl_base));
		}
		else
			temp = -1.0;
		if (temp < 0 && temp2 < 0)
			distance = -1.0;
	}
	if (dot_product(c.cyl_dir_unit, ray->dir) != 0)
	{
		temp = -1.0;
		temp2 = -1.0;
		temp = dot_product(c.cyl_dir_unit, c.orig_to_base) \
				/ dot_product(c.cyl_dir_unit, ray->dir);
		if (temp < 0 \
			|| pow(get_magnitude(vec1_minus_vec2(scalar_mply_vector(temp, \
				ray->dir), c.orig_to_base)), 2) > pow(c.radius, 2)) 
				// do I need to base on cam position here?
			temp = -1.0;
		temp2 = dot_product(c.cyl_dir_unit, c.orig_to_top) \
				/ dot_product(c.cyl_dir_unit, ray->dir);
		if (temp2 < 0 \
			|| pow(get_magnitude(vec1_minus_vec2(scalar_mply_vector(temp2, \
				ray->dir), c.orig_to_top)), 2) > pow(c.radius, 2))
			temp2 = -1.0;
		if (temp2 >= 0 && (distance == -1.0 || temp2 < distance))
		{
			distance = temp2;
			c.normal_v = c.cyl_dir_unit;
		}
		if (temp >= 0 && (distance == -1.0 || temp < distance))
		{
			distance = temp;
			c.normal_v = scalar_mply_vector(-1, c.cyl_dir_unit);
		}
		if (distance >= 0)
			t = distance;
	}
	// debug("Distance of cyl hit point: %f", distance);
	// debug("t cylinder: %f", t);
	cyl->c = c;
	// debug("Cyl hitpoint normal vector: (%f,%f,%f)", \
	// 	cyl->c.normal_v.e[0], cyl->c.normal_v.e[1], cyl->c.normal_v.e[2]);
	return (t);
}

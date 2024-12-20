/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpriess <rpriess@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 16:30:37 by rpriess           #+#    #+#             */
/*   Updated: 2024/12/09 16:30:46 by rpriess          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "vector_setup.h"
#include "vector_math.h"
#include "debug.h"
#include <math.h>

static double	dist_from_base(t_cylinder *cyl, double distance)
{
	t_cyl_helper	c;
	double			dist_base;
	t_point			hit_point;

	c = cyl->c;
	dist_base = -1.0;
	hit_point = add_vectors(c.cam_pos, scalar_mply_vector(distance, c.ray_dir_unit));
	dist_base = dot_product(c.cyl_dir_unit, vec1_minus_vec2(hit_point, c.cyl_base));
	// debug("Dist base: %f", dist_base);
	return (dist_base);
}

/* takes as input a ray and a cylinder, 
 *	- returns -1.0 if no intersection has been found
 *	- returns 0 if camera is inside object or exactly on the surface 
 *	- otherwise returns t for closest hitpoint.
 */
double	find_t_cylinder(t_ray *ray, t_cylinder *cyl)
{
	double			t;
	double			temp;
	double			temp2;
	double			dist_base;
	double			distance;
	t_cyl_helper	c;

	t = -1.0;
	temp = -1.0;
	temp2 = -1.0;
	dist_base = -1.0;
	distance = -1.0;
	c = cyl->c;
	c.ray_dir_unit = ray->dir;
	// debug("Ray direction unit vector: (%f,%f,%f)", c.ray_dir_unit.e[0], c.ray_dir_unit.e[1], c.ray_dir_unit.e[2]);
	c.cross_ray_cyl = scalar_mply_vector(-1, cross_product(ray->dir, c.cyl_dir_unit));
	// debug("Cross product ray and cyl direction: (%f,%f,%f)", c.cross_ray_cyl.e[0], c.cross_ray_cyl.e[1], c.cross_ray_cyl.e[2]);
	c.discriminant = dot_product(c.cross_ray_cyl, c.cross_ray_cyl) * c.radius * c.radius - pow(dot_product(c.orig_to_base, c.cross_ray_cyl), 2);
	// debug("Cylinder discrimant: %f", c.discriminant);
	if (c.discriminant < 0 || get_magnitude(c.cross_ray_cyl) == 0)
		t = -1.0;
	else
	{
		distance = dot_product(c.cross_ray_cyl, scalar_mply_vector(-1, cross_product(c.orig_to_base, c.cyl_dir_unit)));
		temp = (distance + sqrtf(c.discriminant))/ dot_product(c.cross_ray_cyl, c.cross_ray_cyl);
		temp2 = (distance - sqrtf(c.discriminant))/ dot_product(c.cross_ray_cyl, c.cross_ray_cyl);
		if (temp2 > 0)
			distance = temp2;
		if (temp > 0 && temp < distance)
			distance = temp;
		if (temp <= 0 && temp <= 0)
			distance = -1.0;
	}
	if (distance > 0)
	{
		dist_base = dist_from_base(cyl, distance);
		// debug("Distance to base: %f", dist_base);
		if (dist_base >= 0 && dist_base <= cyl->height)
			t = distance;
	}
	if (dot_product(c.cyl_dir_unit, ray->dir) != 0)
	{
		distance = -1.0;
		temp = -1.0;
		temp2 = -1.0;
		temp = dot_product(c.cyl_dir_unit, c.orig_to_base) / dot_product(c.cyl_dir_unit, ray->dir);
		if (temp < 0 || pow(get_magnitude(vec1_minus_vec2(scalar_mply_vector(temp, ray->dir), c.orig_to_base)), 2) > pow(c.radius, 2))
			temp = -1.0;
		temp2 = dot_product(c.cyl_dir_unit, c.orig_to_top) / dot_product(c.cyl_dir_unit, ray->dir);
		if (temp2 < 0 || pow(get_magnitude(vec1_minus_vec2(scalar_mply_vector(temp2, ray->dir), c.orig_to_top)), 2) > pow(c.radius, 2))
			temp2 = -1.0;
		if (temp2 > 0)
			distance = temp2;
		if (temp > 0 && temp < distance)
			distance = temp;
		if (distance > 0 && (t == -1.0 || distance < t))
			t = distance;
	}
	return (t);
}

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
#include <math.h>

// static double	get_t_cyl_curve(t_ray *ray, t_cylinder *cylinder)
// {
	
// }

// static t_ray	*transform_ray_to_cyl_system(t_ray *ray, t_cylinder *cyl)
// {
// 	t_ray	*trans_ray;

// 	trans_ray->orig = add_multiple_vectors(3, ray->orig, -1 * cyl->center, cyl->height * get_unit_vector(cyl->dir) / 2);
// 	trans_ray->dir
// }


static double	dist_from_base(t_cyl_helper *c, double distance)
{
	return (dot_product(c->cyl_dir_unit, vec1_minus_vec2(scalar_mply_vector(distance, c->ray_dir_unit), c->orig_to_base)));
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
	t_cyl_helper	c;
	double			dist_base;
	double			distance;

	t = -1;
	temp = -1;
	c.cyl_base = add_vectors(cyl->center, scalar_mply_vector(-1 *cyl->height / 2, cyl->dir));
	c.ray_dir_unit = get_unit_vector(ray->dir);
	c.orig_to_base = vec1_minus_vec2(c.cyl_base, ray->orig);
	c.radius = cyl->diameter;
	c.cross_ray_cyl = cross_product(c.ray_dir_unit, c.cyl_dir_unit);
	c.discriminant = dot_product(c.cross_ray_cyl, c.cross_ray_cyl) * c.radius * c.radius - pow(dot_product(c.orig_to_base, c.cross_ray_cyl), 2);
	if (c.discriminant < 0)
		t = -1.0;
	else if (get_magnitude(c.cross_ray_cyl) == 0)
		t = -1.0;
	else
		distance = dot_product(c.cross_ray_cyl, cross_product(c.orig_to_base, c.cyl_dir_unit));
		if (c.discriminant != 0)
		{
			temp = (distance + sqrtf(c.discriminant))/ dot_product(c.cross_ray_cyl, c.cross_ray_cyl);
			temp2 = (distance + sqrtf(c.discriminant))/ dot_product(c.cross_ray_cyl, c.cross_ray_cyl);
			if (temp >= temp2)
				distance = temp;
			else
				distance = temp2;
		}
	debug("Distance to cylinder tube:", distance);
	dist_base = dist_from_base(&c, distance);
	if (dist_base < 0 || dist_base > cyl->height)
		t = -1.0;
	else
		t = distance;
	//get closest intersection from curved cylinder surface and save in temp
	//save temp to t
	//get intersection from bottom lid and save in temp
	//save temp to t if smaller than t and > 0
	//get intersection from top lid and save in temp
	//save temp to t if smaller than t and > 0
	return (t);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit_objects.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hzimmerm <hzimmerm@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/17 14:58:46 by hzimmerm          #+#    #+#             */
/*   Updated: 2025/01/24 20:25:37 by hzimmerm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scene.h"
#include "vector_setup.h"
#include "vector_math.h"
#include "debug.h"

// The position of the hit point, P(t), 
// is calculated using the ray equation: P(t)=O+t⋅D
// O: Origin of the ray, ray.orig (a 3D vector).
// D: Direction of the ray, ray.dir (a normalized 3D vector).
// t: Scalar value representing the distance along the ray to the hit point.
static t_point	get_hit_point(t_ray *ray, double t)
{
	t_vec	scaled_dir;
	t_point	hit_point;

	scaled_dir = scalar_mply_vector(t, ray->dir);
	hit_point = add_vectors(ray->orig, scaled_dir);
	return (hit_point);
}

/* get ray, return color:
	- calculate hit point, yes no, where 
	- find which is shortest distance
	- check if light hits too 
	- calculate / interpolate color */
t_color	get_ray_color(t_ray *ray, t_scene *scene)
{
	t_closest	obj;
	t_color		color;

	obj.distance = INFINITY;
	obj.id = -1;
	obj.hit_point = create_triple(0, 0, 0);
	obj.col = create_triple(0, 0, 0);
	find_closest(ray, scene, &obj);
	if (obj.distance == 0)
		return (create_triple(0, 0, 0));
	else if (obj.distance != INFINITY)
	{
		obj.hit_point = get_hit_point(ray, obj.distance);
		if (obj.type == SPHERE)
			obj.normal_v = get_normal_v_sph(obj.hit_point, obj.center);
		color = calculate_obj_color(scene, &obj);
	}
	else
		color = create_triple(0, 0, 0);
	return (color);
}

double	find_t_plane(t_ray *ray, t_plane *plane)
{
	double	d;
	double	denominator;
	double	t;

	denominator = dot_product(plane->ortho, ray->dir);
	if (denominator > 0)
	{
		plane->ortho.e[0] = -plane->ortho.e[0];
		plane->ortho.e[1] = -plane->ortho.e[1];
		plane->ortho.e[2] = -plane->ortho.e[2];
	}
	denominator = dot_product(plane->ortho, ray->dir);
	if (fabs(denominator) < 1e-4)
		return (INFINITY);
	d = -1 * dot_product(plane->ortho, plane->pos);
	t = -1 * ((dot_product(plane->ortho, ray->orig) + d) / denominator);
	return (t);
}

static double	get_discrim(t_ray *ray, t_sphere *sphere, double *c, double *b)
{
	t_vec	orig_to_csph;
	double	radius;
	double	a;
	double	result;

	orig_to_csph = vec1_minus_vec2(ray->orig, sphere->center);
	a = dot_product(ray->dir, ray->dir);
	*b = 2.0 * dot_product(ray->dir, orig_to_csph);
	radius = sphere->diameter / 2.0;
	*c = dot_product(orig_to_csph, orig_to_csph) - (radius * radius);
	result = ((*b) * (*b)) - (4.0 * a * (*c));
	return (result);
}

// takes as input a ray and a sphere, returns -1 if no intersection has been 
//found or a double t which is th position of intersection on the ray 
// 	- returns -1 if no intersection has been found
// 	- returns 0 if camera is inside object or exactly on the surface 
// 	- otherwise returns closest intersection t
double	find_t_sphere(t_ray *ray, t_sphere *sphere)
{
	double	b;
	double	c; 
	double	discriminant;
	double	t1;
	double	t2;

	discriminant = get_discrim(ray, sphere, &c, &b);
	if (discriminant < 0)
		return (-1.0);
	if (c < 0)
		return (0);
	if (discriminant == 0)
	{
		t1 = -b / (2.0 * dot_product(ray->dir, ray->dir));
		if (t1 > 0)
			return (t1);
		else
			return (-1);
	}
	t1 = (-b - sqrt(discriminant)) / (2.0 * dot_product(ray->dir, ray->dir));
	t2 = (-b + sqrt(discriminant)) / (2.0 * dot_product(ray->dir, ray->dir));
	return (fmin(t1, t2));
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit_objects.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Henriette <Henriette@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/17 14:58:46 by hzimmerm          #+#    #+#             */
/*   Updated: 2025/01/19 21:37:15 by Henriette        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scene.h"
#include "vector_setup.h"
#include "vector_math.h"
#include "debug.h"

/* get ray, return color:
	- calculate hit point, yes no, where 
	- find which is shortest distance
	- check if light hits too 
	- calculate / interpolate color */
t_color	get_ray_color(t_ray *ray, t_scene *scene)
{
	t_closest	obj;
	t_color 	color;

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

double find_t_plane(t_ray *ray, t_plane *plane, int mode)
{
	t_vec norm_v;
	double d;
	double denominator;
	double t;

	norm_v = get_unit_vector(plane->ortho);
	denominator = dot_product(norm_v, ray->dir);
	if (mode == 1)
	{
		if (fabs(denominator) < 1e-4)
			return (INFINITY);
	}
	else
	{
		if (fabs(denominator) < 0.7)
			return (INFINITY);
	}
	d = -1 * dot_product(norm_v, plane->pos);
	t = -1 * ((dot_product(norm_v, ray->orig) + d) / denominator);
	return (t);
}


/* takes as input a ray and a sphere, returns -1 if no intersection has been found 
or a double t which is th position of intersection on the ray 
	- returns -1 if no intersection has been found
	- returns 0 if camera is inside object or exactly on the surface 
	- otherwise returns closest intersection t */
double find_t_sphere(t_ray *ray, t_sphere *sphere)
{
	double b;
	double c; 
	double discriminant;
	double	t1;
	double	t2;

	discriminant = get_discriminant(ray, sphere, &c, &b);
	if (discriminant < 0)
    		return (-1.0);
	if (c < 0)
		return (0);
	if (discriminant == 0)
	{
		t1 = -b / (2.0 * dot_product(ray->dir, ray->dir));
		if (t1 > 0)
			return t1;
		else
			return -1;
	}
	t1 = (-b - sqrt(discriminant)) / (2.0 * dot_product(ray->dir, ray->dir));
	t2 = (-b + sqrt(discriminant)) / (2.0 * dot_product(ray->dir, ray->dir));
	return (fmin(t1, t2));
}

double	get_discriminant(t_ray *ray, t_sphere *sphere, double *c, double *b)
{
	t_vec orig_to_csph;
	double radius;
	double a;
	double	result;

	orig_to_csph = vec1_minus_vec2(ray->orig, sphere->center);
	a = dot_product(ray->dir, ray->dir);
	*b = 2.0 * dot_product(ray->dir, orig_to_csph);
	radius = sphere->diameter / 2.0;
	*c = dot_product(orig_to_csph, orig_to_csph) - (radius * radius);
	result = ((*b) * (*b)) - (4.0 * a * (*c));
	return (result);
}

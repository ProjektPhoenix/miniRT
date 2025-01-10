/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit_objects.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hzimmerm <hzimmerm@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/17 14:58:46 by hzimmerm          #+#    #+#             */
/*   Updated: 2025/01/10 18:28:26 by hzimmerm         ###   ########.fr       */
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
	//return (create_triple(255, 0, 0));
	t_closest	obj;
	t_color 	color;
	//color = create_triple(255, 255, 255); // just to test intersection calculation before color calculation

	//debug("ray origin: %.2f, %.2f, %.2f -  ray direction: %.2f, %.2f, %.2f\n", ray->orig.e[0],  ray->orig.e[1],  ray->orig.e[2],  ray->dir.e[0],  ray->dir.e[1],  ray->dir.e[2]);
	obj.distance = INFINITY;
	obj.id = -1;
	obj.hit_point = create_triple(0, 0, 0);
	obj.col = create_triple(0, 0, 0);
	find_closest(ray, scene, &obj); // find the closest intersection
	//debug("object distance: %.2f\n", obj.distance);
	if (obj.distance == 0)
	{
		//debug("obj.distance = 0\n");
		return (create_triple(0, 0, 0)); //return black
	} 
	else if (obj.distance != INFINITY) // if distance has been updated, meaning object has been hit
	{
		//debug("object has been hit\n");
		//color = create_triple(255,0, 0);
		obj.hit_point = get_hit_point(ray, obj.distance);
		color = calculate_obj_color(scene, &obj);
	}
	else
		color = create_triple(0, 0, 0);
	return (color);
}

void	find_closest(t_ray *ray, t_scene *scene, t_closest *obj)
{
	t_sphere	*temp_s;
	t_plane	*temp_p;
	double	t;

	temp_s = scene->sphere;
	while(temp_s)
	{
		t = find_t_sphere(ray, temp_s); // find t_sphere returns negative value if no hit point or hit point behind camera
		//debug("t: %.2f\n", t);
		if (t >= 0 && t < obj->distance)
		{
			obj->distance = t;
			if (obj->distance == 0)
				break;
			obj->id = temp_s->id;
			//debug("object id: %d sphere id: %d\n", obj->id, temp_s->id);
			obj->col = temp_s->col;
			obj->type = SPHERE;
			obj->center = temp_s->center;
		}
		temp_s = temp_s->next;
	}
	temp_p = scene->plane;
	while (temp_p)
	{
		t = find_t_plane(ray, temp_p);
		//if (t != INFINITY)
			//debug("t: %.2f\n", t);
		if (t >= 0 && t < obj->distance)
		{
			obj->distance = t;
			if (obj->distance == 0)
				break;
			obj->id = temp_p->id;
			obj->col = temp_p->col;
			obj->type = PLANE;
			obj->normal_v = temp_p->ortho;
		}
		temp_p = temp_p->next;
	}
	//continue with other objects
}

double find_t_plane(t_ray *ray, t_plane *plane)
{
	t_vec norm_v;
	double d; // signed distance from world origin 0 ,0, 0 to plane 
	double denominator;
	double t;

	norm_v = get_unit_vector(plane->ortho);
	//debug("norm vec unit : %f, %f, %f\n", norm_v.e[0], norm_v.e[1], norm_v.e[2]);
	denominator = dot_product(norm_v, ray->dir);
	if (fabs(denominator) < 1e-6) // if denominator is 0: both vectors are parallel, so no intersection -  taking into account float point precision margin 
	{
		//debug("denom is 0\n");
		return (INFINITY);
	}
	d = -1 * dot_product(norm_v, plane->pos);
	//debug("d is %f\n", d);
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
	if (discriminant < 0) //no intersection
    		return (-1.0);
	if (c < 0) //check if point is inside or outside of sphere
	{
		debug("POINT IS INSIDE SPHERE");
		return (0);
	}
	if (discriminant == 0) //tangent 
	{
		t1 = -b / (2.0 * dot_product(ray->dir, ray->dir));
		if (t1 > 0)
			return t1;
		else
			return -1;
	}
	t1 = (-b - sqrt(discriminant)) / (2.0 * dot_product(ray->dir, ray->dir));
	t2 = (-b + sqrt(discriminant)) / (2.0 * dot_product(ray->dir, ray->dir));
	//debug("t1: %.2f - t2: %.2f\n", t1, t2);
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

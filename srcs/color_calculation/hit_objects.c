/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit_objects.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hzimmerm <hzimmerm@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/17 14:58:46 by hzimmerm          #+#    #+#             */
/*   Updated: 2024/12/08 21:35:10 by hzimmerm         ###   ########.fr       */
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
	{
		//debug("backgroudn color\n");
		color = calculate_background_color(scene);
	}
	return (color);
}

void	find_closest(t_ray *ray, t_scene *scene, t_closest *obj)
{
	t_sphere	*temp;
	double	t;

	temp = scene->sphere;
	while(temp)
	{
		t = find_t_sphere(ray, temp); // find t_sphere returns negative value if no hit point or hit point behind camera
		//debug("t: %.2f\n", t);
		if (t >= 0 && t < obj->distance)
		{
			obj->distance = t;
			obj->id = temp->id;
			obj->col = temp->col;
			obj->type = SPHERE;
			if (obj->distance == 0)
				break;
			obj->center = temp->center;
		}
		temp = temp->next;
	}
	
	//continue with other objects
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
	//debug("dot product ray dir orig to csph: %.2f\n", dot_product(ray->dir, orig_to_csph));
	*b = 2.0 * dot_product(ray->dir, orig_to_csph);
	//debug("orig_to_csph: %.2f, %.2f, %.2f\n", orig_to_csph.e[0], orig_to_csph.e[1], orig_to_csph.e[2]);
	//debug("ray direction: %.2f, %.2f, %.2f\n", ray->dir.e[0], ray->dir.e[1], ray->dir.e[2]);
	//debug("a: %.2f, b: %.2f, c: %.2f\n", a, *b, *c);
	radius = sphere->diameter / 2.0;
	*c = dot_product(orig_to_csph, orig_to_csph) - (radius * radius);
	result = ((*b) * (*b)) - (4.0 * a * (*c));
	return (result);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit_objects.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hzimmerm <hzimmerm@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/17 14:58:46 by hzimmerm          #+#    #+#             */
/*   Updated: 2024/11/17 19:02:40 by hzimmerm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scene.h"
#include "vector_setup.h"
#include "vector_math.h"

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
	obj.hit_point = create_point(0, 0, 0);
	find_closest(ray, scene, &obj);
	if (obj.distance != INFINITY)
	{
		obj.hit_point = get_hit_point(ray, obj.distance);
		color = calculate_obj_color(ray, scene, &obj);
	}
	else
		color = calculate_background_color(ray, scene);
	return (color);
}

void	find_closest(t_ray *ray, t_scene *scene, t_closest *obj)
{
	t_sphere	*temp;
	double	t;	

	temp = scene->sphere;
	while(temp)
	{
		t = find_t_sphere(ray, temp); // find t_sphere returns -1 if no hit point 
		if (t > 0 && t < obj->distance)
		{
			obj->distance = t;
			obj->id = temp->id;
		}
		temp = temp->next;
	}
	//continue with other objects
}

/* takes as input a ray and a sphere, returns -1 if no intersection has been found or a double t which is th position of intersection on the ray */
double find_t_sphere(t_ray *ray, t_sphere *sphere)
{
	t_vec orig_to_csph;
	double dot_a;
	double c; //check if point is inside or outside of sphere
	double discriminant;

	orig_to_csph = vec1_minus_vec2(sphere->center, ray->orig);
	dot_a = 2.0 * dot_product(ray->dir, orig_to_csph);
	c = dot_product(orig_to_csph, orig_to_csph) - ((sphere->diameter * sphere->diameter) / 4);
	discriminant = dot_a * dot_a - 4 * dot_product(ray->dir, ray->dir) * c;
	if (discriminant < 0)
    		return (-1.0); //no intersection
	// outsource diese obere Rechnung und dann mach einen Test, ob orig innerhalb oder ausserhalb ist, wenn innerhalb oder genau drauf dann mach Pixel schwarz
	
}
t_color	calculate_obj_color(t_ray *ray, t_scene *scene, t_closest *obj)
{
	
}


t_color	calculate_background_color(t_ray *ray, t_scene *scene)
{
	
}




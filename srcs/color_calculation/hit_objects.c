/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit_objects.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hzimmerm <hzimmerm@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/17 14:58:46 by hzimmerm          #+#    #+#             */
/*   Updated: 2024/11/17 17:27:58 by hzimmerm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scene.h"
#include "vector_setup.h"

/* get ray, return color:
	- calculate hit point, yes no, where 
	- find which is shortest distance
	- check if light hits too 
	- calculate / interpolate color */

t_color	get_ray_color(t_ray ray, t_scene *scene)
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

void	find_closest(t_ray ray, t_scene *scene, t_closest *obj)
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
double find_t_sphere(t_ray ray, t_sphere *sphere)
{
	t_vec orig_to_center_sph;
	double dot_a;
	double dot_b;
	double sqrt_discriminant;

	orig_to_center_sph = vec1_minus_vec2(sphere->center, ray.orig);
	/*double a = vec3_dot(&r->dir, &r->dir); // a: This is the dot product of the ray direction with itself a=B⋅B 
	double b = -2.0 * vec3_dot(&r->dir, &oc); // b: This is the dot product of the ray direction and the vector from the ray origin to the sphere center (oc), scaled by −2.0: b=−2(B⋅oc)
	double c = vec3_dot(&oc, &oc) - radius * radius; // calculates the squared distance from the ray origin to the sphere, minus the square of the radius. This term checks if the ray starts inside or outside the sphere.
	double discriminant = b * b - 4 * a * c; // Calculate the discriminant
	if (discriminant < 0)
    		return (-1.0); //no intersection
	
		return ((-b - sqrt(discriminant)) / (2.0 * a));*/
	
}
t_color	calculate_obj_color(t_ray ray, t_scene *scene, t_closest *obj)
{
	
}


t_color	calculate_background_color(t_ray ray, t_scene *scene)
{
	
}




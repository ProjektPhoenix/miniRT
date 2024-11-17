/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit_objects.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hzimmerm <hzimmerm@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/17 14:58:46 by hzimmerm          #+#    #+#             */
/*   Updated: 2024/11/17 16:24:33 by hzimmerm         ###   ########.fr       */
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
		obj.hit_point = get_hit_point(ray, scene, obj.distance);
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


t_color	calculate_obj_color(t_ray ray, t_scene *scene, t_closest *obj)
{
	
}


t_color	calculate_background_color(t_ray ray, t_scene *scene)
{
	
}

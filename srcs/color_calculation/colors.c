/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hzimmerm <hzimmerm@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 18:12:12 by hzimmerm          #+#    #+#             */
/*   Updated: 2024/11/18 21:07:19 by hzimmerm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "scene.h"
#include "vector_setup.h"
#include "vector_math.h"
#include "debug.h"

t_color	calculate_obj_color(t_scene *scene, t_closest *obj)
{
	t_ray	l_ray;
	bool	blocked;
	double l_dist;
	double attenuation;
	t_color	color;
	
	l_ray.orig = obj->hit_point;
	l_ray.dir = vec1_minus_vec2(scene->light.pos, l_ray.orig);
	blocked = false;
	if (check_blocking_objects(&l_ray, scene) == -1)
		blocked = true;
	color = add_vectors(scalar_mply_vector(scene->amb.intens, scene->amb.col), obj->col);
	if (blocked == false)
	{
		l_dist = get_magnitude(l_ray.dir);
		attenuation = 1.0 / (l_dist * l_dist);
		scene->light.intens = scene->light.intens * attenuation;
		color = add_vectors(color, scalar_mply_vector(scene->light.intens, scene->light.col));
	}
	return (color);
}

/* checks if any objects are in the way of the hit point and the light 
	- for now only sphere, needs to be expanded to other objects */
int	check_blocking_objects(t_ray *l_ray, t_scene *scene)
{
	t_sphere	*temp;

	temp = scene->sphere;
	while(temp)
	{
		if (find_t_sphere(l_ray, temp) != -1)
			return (-1);
		temp = temp->next;
	}
	// continue with other objects
	return (0);
}

t_color	calculate_background_color(t_scene *scene)
{
	t_color	amb;
	t_color	light;
	t_color	backg_c;

	amb = scalar_mply_vector(scene->amb.intens, scene->amb.col);
	light = scalar_mply_vector(scene->light.intens, scene->light.col);
	backg_c = add_vectors(amb, light);
	return (backg_c);	
}

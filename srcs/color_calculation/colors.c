/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Henriette <Henriette@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 18:12:12 by hzimmerm          #+#    #+#             */
/*   Updated: 2024/11/29 18:00:29 by Henriette        ###   ########.fr       */
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
	//debug("l_ray dir %.2f, %.2f, %.2f\n", l_ray.dir.e[0], l_ray.dir.e[1], l_ray.dir.e[2]);
	blocked = false;
	if (check_blocking_objects(&l_ray, scene) == -1) //for now returns 0, needs to be checked and adjusted
		blocked = true;
	color = add_vectors(scalar_mply_vector(scene->amb.intens, scene->amb.col), obj->col);
	//color = obj->col;
	if (blocked == false)
	{
		//debug("inside blocked false\n");
		l_dist = get_magnitude(l_ray.dir);
		debug("distance to light from hit point: %.2f\n", l_dist);
		attenuation = 1.0 / (l_dist * l_dist + 100);
		if (attenuation < 0.1)
			attenuation = 0.1;
		//scene->light.intens = scene->light.intens *1000 * attenuation;
		color = add_vectors(color, scalar_mply_vector(scene->light.intens, scene->light.col));
	}
	return (color);
}

/* checks if any objects are in the way of the hit point and the light 
	- for now only sphere, needs to be expanded to other objects */
int	check_blocking_objects(t_ray *l_ray, t_scene *scene)
{
	return (0);
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
	//return (backg_c);	
	return (create_triple(0, 0, 0));
}

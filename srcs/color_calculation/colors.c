/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Henriette <Henriette@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 18:12:12 by hzimmerm          #+#    #+#             */
/*   Updated: 2024/12/02 16:18:15 by Henriette        ###   ########.fr       */
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

	obj->normal_v = assign_normal(scene, obj);
	make_light_ray(&l_ray, scene, obj);
	//debug("l_ray dir %.2f, %.2f, %.2f\n", l_ray.dir.e[0], l_ray.dir.e[1], l_ray.dir.e[2]);
	blocked = check_blocking_objects(&l_ray, scene);
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

t_vec	assign_normal(t_scene *scene, t_closest *obj)
{
	if (obj->type == SPHERE)
	{
		return (get_normal_v_sph(obj->hit_point, obj->center));
	}
	return (create_triple(0, 0, 0)); // this just placeholder until other shapes are added
}

void	make_light_ray(t_ray *l_ray, t_scene *scene, t_closest *obj)
{
	double offset;

	offset = 1e-4;
	l_ray->orig = add_vectors(obj->hit_point, scalar_mply_vector(offset, obj->normal_v));
	l_ray->dir = vec1_minus_vec2(scene->light.pos, l_ray->orig);
	l_ray->dir = get_unit_vector(l_ray->dir);
}

/* checks if any objects are in the way of the hit point and the light 
	- for now only sphere, needs to be expanded to other objects */
int	check_blocking_objects(t_ray *l_ray, t_scene *scene)
{
	t_sphere	*temp;
	double	t;

	temp = scene->sphere;
	while(temp)
	{
		t = find_t_sphere(l_ray, temp);
		if (t == -1) // no intersection
			
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

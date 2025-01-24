/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hzimmerm <hzimmerm@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 18:12:12 by hzimmerm          #+#    #+#             */
/*   Updated: 2025/01/24 20:20:35 by hzimmerm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scene.h"
#include "vector_setup.h"
#include "vector_math.h"
#include "debug.h"

// calculates the final color of the object in different steps:
// - mixes the ambient light with the object color
// - checks if other objects block the way to the light source and if not,
// - calls the function to add light contribution
t_color	calculate_obj_color(t_scene *scene, t_closest *obj)
{
	t_col_mix	mix;
	t_color		amb_contr;
	t_ray		l_ray;
	bool		blocked;

	make_light_ray(&l_ray, scene, obj);
	l_ray.dist = get_magnitude(l_ray.dir);
	l_ray.dir = get_unit_vector(l_ray.dir);
	mix.norm_obj = normalise_color(obj->col);
	mix.norm_amb = normalise_color(scene->amb.col);
	amb_contr = scalar_mply_vector(scene->amb.intens, mix.norm_amb);
	mix.final = multiply_cols(amb_contr, mix.norm_obj);
	blocked = check_blocking_obj(&l_ray, scene, obj);
	if (!blocked)
		add_light(&l_ray, &mix, scene, obj);
	mix.final.e[0] = fmin(mix.final.e[0] * 255.0, 255.0);
	mix.final.e[1] = fmin(mix.final.e[1] * 255.0, 255.0);
	mix.final.e[2] = fmin(mix.final.e[2] * 255.0, 255.0);
	return (mix.final);
}

// calculates and adds the diffuse light based on the angle between 
// the light ray and the object normal vector - 
// calls the specular light function and adds this on top
void	add_light(t_ray *l_ray, t_col_mix *mix, t_scene *scene, t_closest *obj)
{
	t_color	diff;
	t_color	spec;

	mix->diff_intens = fmax(dot_product(l_ray->dir, obj->normal_v), 0.0);
	diff = scalar_mply_vector(mix->diff_intens * scene->light.intens, \
		mix->norm_obj);
	diff = multiply_cols(diff, scene->light.col);
	mix->final = add_vectors(mix->final, diff);
	spec = specular_light(l_ray, scene, obj);
	mix->final = add_vectors(mix->final, spec);
}

// helper function to refactor check_blocking_objects function below
static bool	check_cyls_blocking(t_ray *l_ray, t_scene *scene, t_closest *obj)
{
	t_cylinder	*temp_c;
	double		t;

	temp_c = scene->cyl;
	while (temp_c)
	{
		if (temp_c->id != obj->id)
		{
			t = find_t_cylinder(l_ray, temp_c);
			if (t > 0 && t < l_ray->dist)
				return (true);
		}
		temp_c = temp_c->next;
	}
	return (false);
}

static bool	check_planes_blocking(t_ray *l_ray, t_scene *scene, t_closest *obj)
{
	t_plane		*temp_p;
	double		t;

	temp_p = scene->plane;
	while (temp_p)
	{
		if (temp_p->id != obj->id)
		{
			t = find_t_plane(l_ray, temp_p);
			if (t > 1e-4 && t < l_ray->dist)
				return (true);
		}
		temp_p = temp_p->next;
	}
	return (false);
}

// checks if any objects are in the way of the hit point and the light 
// 	- for now only sphere, needs to be expanded to other objects
bool	check_blocking_obj(t_ray *l_ray, t_scene *scene, t_closest *obj)
{
	t_sphere	*temp_s;
	double		t;

	temp_s = scene->sphere;
	while (temp_s)
	{
		if (temp_s->id != obj->id)
		{
			t = find_t_sphere(l_ray, temp_s); 
			if (t > 0 && t < l_ray->dist)
				return (true);
		}
		temp_s = temp_s->next;
	}
	if (check_planes_blocking(l_ray, scene, obj) || 
		check_cyls_blocking(l_ray, scene, obj))
		return (true);
	return (false);
}

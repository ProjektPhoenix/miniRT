/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hzimmerm <hzimmerm@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 18:12:12 by hzimmerm          #+#    #+#             */
/*   Updated: 2025/01/19 16:44:37 by hzimmerm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "scene.h"
#include "vector_setup.h"
#include "vector_math.h"
#include "debug.h"

static t_color multiply_cols(t_color col1, t_color col2)
{
	t_color col;

	col.e[0] = col1.e[0] * col2.e[0];
	col.e[1] = col1.e[1] * col2.e[1];
	col.e[2] = col1.e[2] * col2.e[2];
	return (col);
}

t_color normalise_color(t_color col)
{
	t_color color;
	
	color.e[0] = col.e[0] / 255.0;
	color.e[1] = col.e[1] / 255.0;
	color.e[2] = col.e[2] / 255.0;
	return (color);
}

t_color	calculate_obj_color(t_scene *scene, t_closest *obj)
{
	t_col_mix mix;
	t_color amb_contr;
	t_ray	l_ray;
	bool	blocked;

	make_light_ray(&l_ray, scene, obj);
	l_ray.dist = get_magnitude(l_ray.dir);
	l_ray.dir = get_unit_vector(l_ray.dir);
	mix.norm_obj = normalise_color(obj->col);
	mix.norm_amb = normalise_color(scene->amb.col);
	amb_contr = scalar_mply_vector(scene->amb.intens, mix.norm_amb);
	mix.final = multiply_cols(amb_contr, mix.norm_obj);
	blocked = check_blocking_objects(&l_ray, scene);
	if (!blocked)
		add_light(&l_ray, &mix, scene, obj);
	mix.final.e[0] = fmin(mix.final.e[0] * 255.0, 255.0);
	mix.final.e[1] = fmin(mix.final.e[1] * 255.0, 255.0);
	mix.final.e[2] = fmin(mix.final.e[2] * 255.0, 255.0);
	return (mix.final);
}

void	add_light(t_ray *l_ray, t_col_mix *mix, t_scene *scene, t_closest *obj)
{
	t_color diff;
	t_color spec;

	mix->diff_intens = fmax(dot_product(l_ray->dir, obj->normal_v), 0.0);
	diff = scalar_mply_vector(0.9 * mix->diff_intens * scene->light.intens, mix->norm_obj);
	diff = multiply_cols(diff, scene->light.col);
	mix->final = add_vectors(mix->final, diff);
	spec = specular_light(l_ray, scene, obj);
	mix->final = add_vectors(mix->final, spec);
}

t_color specular_light(t_ray *l_ray, t_scene *scene, t_closest *obj)
{
	t_spec_l spec;
	t_color spec_contr;
	
	spec.reflectivity = 0.3;
	if (obj->id % 2)
		spec.shininess = 5;
	else
		spec.shininess = 30;
	
	spec.reflect_dir = reflection(&l_ray->dir, &obj->normal_v);
	spec.view_dir = get_unit_vector(vec1_minus_vec2(scene->camera.pos, obj->hit_point));
	spec.intens = fmax(dot_product(spec.reflect_dir, spec.view_dir), 0.0);
	spec.intens = pow(spec.intens, spec.shininess);
	spec_contr = scalar_mply_vector(spec.intens * scene->light.intens, scene->light.col);
	spec_contr = scalar_mply_vector(spec.intens * spec.reflectivity, spec_contr);
	return (spec_contr);
}

t_color reflection(t_vec *l_ray_dir, t_vec *normal)
{
	t_color	reflect;
	double dot;

	dot = dot_product(*l_ray_dir, *normal);
	if (dot < - 1.0)
		dot = -1.0;
	if (dot > 1.0)
		dot = 1.0;
	reflect.e[0] = 2 * dot * normal->e[0] - l_ray_dir->e[0];
	reflect.e[1] = 2 * dot * normal->e[1] - l_ray_dir->e[1];
	reflect.e[2] = 2 * dot * normal->e[2] - l_ray_dir->e[2];
	return (get_unit_vector(reflect));
}

void	make_light_ray(t_ray *l_ray, t_scene *scene, t_closest *obj)
{
	double offset;

	offset = 1e-4;
	l_ray->orig = add_vectors(obj->hit_point, scalar_mply_vector(offset, obj->normal_v));
	//l_ray->orig = obj->hit_point;
	l_ray->dir = vec1_minus_vec2(scene->light.pos, l_ray->orig);
}

/* checks if any objects are in the way of the hit point and the light 
	- for now only sphere, needs to be expanded to other objects */
//bool	check_blocking_objects(t_ray *l_ray, t_scene *scene, t_closest *obj)
bool	check_blocking_objects(t_ray *l_ray, t_scene *scene)
{
	t_sphere	*temp_s;
	double		t;
	t_plane		*temp_p;
	t_cylinder	*temp_c;
	
	temp_s = scene->sphere;
	while(temp_s)
	{
		t = find_t_sphere(l_ray, temp_s); //unit vector uebergeben 
		if (t > 0 && t < l_ray->dist)
		{
			//debug("sphere is blocking light\n");
			return (true);
		}
		temp_s = temp_s->next;
	}
	temp_p = scene->plane;
	while (temp_p)
	{
		t = find_t_plane(l_ray, temp_p);
		if (t > 0 && t < l_ray->dist)
			return (true);
		temp_p = temp_p->next;
	}
	temp_c = scene->cyl;
	while (temp_c)
	{
		t = find_t_cylinder(l_ray, temp_c);
			if (t > 0 && t < l_ray->dist)
				return (true);
		temp_c = temp_c->next;
	}
	return (false);
}

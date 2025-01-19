/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hzimmerm <hzimmerm@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 18:12:12 by hzimmerm          #+#    #+#             */
/*   Updated: 2025/01/10 18:27:40 by hzimmerm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "scene.h"
#include "vector_setup.h"
#include "vector_math.h"
#include "debug.h"

static t_color multiply_vecs(t_color col1, t_color col2)
{
	t_color col;

	col.e[0] = col1.e[0] * col2.e[0];
	col.e[1] = col1.e[1] * col2.e[1];
	col.e[2] = col1.e[2] * col2.e[2];
	return (col);
}

/*static t_color	debug_norm_vecs(t_closest *obj)
{
	t_vec debug_normal;
	t_color debug_color ;

	debug_normal = obj->normal_v;
	debug_color = create_triple(((debug_normal.e[0] + 1.0) * 127.5),((debug_normal.e[1] + 1.0) * 127.5),((debug_normal.e[2] + 1.0) * 127.5));
	return (debug_color);
}*/

static t_color normalise_color(t_color col)
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
	t_ray	l_ray;
	bool	blocked;

	// if (obj->type != PLANE)
	// 	obj->normal_v = assign_normal(obj); // move to SPHERE find closest
	make_light_ray(&l_ray, scene, obj);
	l_ray.dist = get_magnitude(l_ray.dir);
	l_ray.dir = get_unit_vector(l_ray.dir);
	mix.norm_obj = normalise_color(obj->col);
	mix.norm_amb = normalise_color(scene->amb.col);
	mix.norm_light = normalise_color(scene->light.col);
	t_color amb_contr = scalar_mply_vector(scene->amb.intens, mix.norm_amb);
	mix.final = multiply_vecs(amb_contr, mix.norm_obj);
	blocked = check_blocking_objects(&l_ray, scene, obj);
	if (!blocked)
		add_light(&l_ray, &mix, scene, obj);
	mix.final.e[0] = fmin(mix.final.e[0] * 255.0, 255.0);
	mix.final.e[1] = fmin(mix.final.e[1] * 255.0, 255.0);
	mix.final.e[2] = fmin(mix.final.e[2] * 255.0, 255.0);
	return (mix.final);
}

void	add_light(t_ray *l_ray, t_col_mix *mix, t_scene *scene, t_closest *obj)
{
	double reflectivity = 0.3;
	mix->diff_intens = fmax(dot_product(l_ray->dir, obj->normal_v), 0.0);
	t_color diff = scalar_mply_vector(0.9 * mix->diff_intens * scene->light.intens, mix->norm_obj);
	mix->final = add_vectors(mix->final, diff);
	t_vec reflect_dir_R = reflection(&l_ray->dir, &obj->normal_v);
	t_vec view_dir_V = get_unit_vector(vec1_minus_vec2(scene->camera.pos, obj->hit_point));
	double 	spec_intens = fmax(dot_product(reflect_dir_R, view_dir_V), 0.0);
	spec_intens = pow(spec_intens, 5);
	t_color spec = scalar_mply_vector(spec_intens * scene->light.intens, scene->light.col);
	spec = scalar_mply_vector(spec_intens * reflectivity, spec);
	mix->final = add_vectors(mix->final, spec);
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

t_vec	assign_normal(t_closest *obj)
{
	if (obj->type == SPHERE)
	{
		return (get_normal_v_sph(obj->hit_point, obj->center));
	}
	
	return (create_triple(0, 0, 0)); // this just placeholder until other shapes are added
}

void	make_light_ray(t_ray *l_ray, t_scene *scene, t_closest *obj)
{
	//double offset;

	//offset = 1e-4;
	//l_ray->orig = add_vectors(obj->hit_point, scalar_mply_vector(offset, obj->normal_v));
	l_ray->orig = obj->hit_point;
	l_ray->dir = vec1_minus_vec2(scene->light.pos, l_ray->orig);
}

/* checks if any objects are in the way of the hit point and the light 
	- for now only sphere, needs to be expanded to other objects */
bool	check_blocking_objects(t_ray *l_ray, t_scene *scene, t_closest *obj)
{
	t_sphere	*temp_s;
	double		t;
	t_plane		*temp_p;
	t_cylinder	*temp_c;
	
	temp_s = scene->sphere;
	while(temp_s)
	{
		if (obj->id != temp_s->id) // take out? object could block itself from light
		{
			t = find_t_sphere(l_ray, temp_s); //unit vector uebergeben 
			if (t > 0 && t < l_ray->dist)
			{
				//debug("sphere is blocking light\n");
				return (true);
			}
		}
		temp_s = temp_s->next;
	}
	temp_p = scene->plane;
	while (temp_p)
	{
		if (obj->id != temp_p->id) // take out? object could block itself from light
		{
			t = find_t_plane(l_ray, temp_p);
			if (t > 0 && t < l_ray->dist)
				return (true);
		}
		temp_p = temp_p->next;
	}
	temp_c = scene->cyl;
	while (temp_c)
	{
		if (obj->id != temp_c->id) // take out? object could block itself from light
		{
			t = find_t_cylinder(l_ray, temp_c);
			if (t > 0 && t < l_ray->dist)
				return (true);
		}
		temp_c = temp_c->next;
	}
	return (false);
}

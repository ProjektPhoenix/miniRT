/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hzimmerm <hzimmerm@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 18:12:12 by hzimmerm          #+#    #+#             */
/*   Updated: 2025/01/10 18:21:07 by hzimmerm         ###   ########.fr       */
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
t_vec invert_vec(t_vec vec)
{
	return (create_triple(-vec.e[0], -vec.e[1], -vec.e[2]));
}

t_color	calculate_obj_color(t_scene *scene, t_closest *obj)
{
	t_col_mix mix;
	t_ray	l_ray;
	bool	blocked;

	if (obj->type != PLANE)
		obj->normal_v = assign_normal(obj);
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
	{
		double reflectivity = 0.3;
		mix.diff_intens = fmax(dot_product(l_ray.dir, obj->normal_v), 0.0);
		t_color diff = scalar_mply_vector(0.9 * mix.diff_intens * scene->light.intens, mix.norm_obj);
		//diff = scalar_mply_vector(1 - reflectivity, diff);
		mix.final = add_vectors(mix.final, diff);
		/*t_vec income_vec = invert_vec(l_ray.dir);
		t_vec temp_normal = scalar_mply_vector(2.0 * - (dot_product(income_vec, obj->normal_v)), obj->normal_v);
		t_vec reflect_vec = get_unit_vector(add_vectors(temp_normal, income_vec));
		double spec_intens = fmax(-dot_product(reflect_vec, income_vec), 0.0);
		spec_intens = powf(spec_intens, 10);
		//t_color spec_col = create_triple(1, 1, 1);
		t_color spec_col = scalar_mply_vector(spec_intens * scene->light.intens, scene->light.col);
		//t_color spec = scalar_mply_vector(spec_intens, mix.norm_light);
		mix.final = add_vectors(mix.final, spec_col);*/
	
	t_vec reflect_dir_R = reflection(&l_ray.dir, &obj->normal_v);
	t_vec view_dir_V = get_unit_vector(vec1_minus_vec2(scene->camera.pos, obj->hit_point));
	double 	spec_intens = fmax(dot_product(reflect_dir_R, view_dir_V), 0.0);
	spec_intens = pow(spec_intens, 5);
	t_color spec = scalar_mply_vector(spec_intens * scene->light.intens, scene->light.col);
	spec = scalar_mply_vector(spec_intens * reflectivity, spec);
	mix.final = add_vectors(mix.final, spec);
	}
	/*mix.final = colmix_ambient_object(&mix, obj, scene);
	if (!blocked)
		add_light(&l_ray, &mix, scene, obj);*/
	mix.final.e[0] = fmin(mix.final.e[0] * 255.0, 255.0);
	mix.final.e[1] = fmin(mix.final.e[1] * 255.0, 255.0);
	mix.final.e[2] = fmin(mix.final.e[2] * 255.0, 255.0);
	return (mix.final);
}

void	add_light(t_ray *l_ray, t_col_mix *mix, t_scene *scene, t_closest *obj)
{
	t_color diff_light;
	//double att_factor;
	/*t_vec reflect_dir;
	double spec_intens;
	t_vec view_dir;
	t_color spec_light;*/

	mix->diff_intens = fmax(dot_product(l_ray->dir, obj->normal_v), 0.0);
	//debug("dot product: %f - distance light: %f\n", mix->diff_intens, l_ray->dist);
	//mix->attenuation = 1.0 / (l_ray->dist * l_ray->dist);
	//mix->attenuation = exp(-0.1 * l_ray->dist);
	//mix->attenuation = 1.0 / (1.0 + 0.1 * l_ray->dist + 0.01 * l_ray->dist * l_ray->dist);
	//att_factor = 150 / (l_ray->dist + 1);
	//mix->diff_intens *= mix->attenuation * 10;
	//debug("diff_intens:%.2f\n", mix->diff_intens);
	//debug("light distance:%.2f\n", l_ray->dist);
	diff_light = scalar_mply_vector(scene->light.intens * mix->diff_intens, mix->norm_light);
	if (!scene->amb.intens)
		mix->diff_contr = add_vectors(diff_light, scalar_mply_vector(scene->light.intens, mix->norm_obj));
	else
		mix->diff_contr = add_vectors(diff_light, scalar_mply_vector(scene->light.intens, mix->final));
	mix->final = add_vectors(mix->final, mix->diff_contr);
	/*reflect_dir = reflection(&l_ray->dir, &obj->normal_v);
	view_dir = vec1_minus_vec2(get_unit_vector(scene->camera.dir), obj->hit_point);
	spec_intens = fmax(dot_product(reflect_dir, get_unit_vector(view_dir)), 0.0);
	spec_intens = pow(spec_intens, 160);
	spec_intens /= (l_ray->dist * l_ray->dist);
	//spec_intens /= (1.0 + 0.1 * l_ray->dist + 0.01 * l_ray->dist * l_ray->dist);
	spec_light = scalar_mply_vector(scene->light.intens * spec_intens, mix->norm_light);
	mix->final = add_vectors(mix->final, scalar_mply_vector(0.3, spec_light));*/
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
	//printf("l_ray_dir: %.2f, %.2f, %.2f - dot: %.2f\n",
		//l_ray_dir->e[0], l_ray_dir->e[1], l_ray_dir->e[2], dot);
	reflect.e[0] = 2 * dot * normal->e[0] - l_ray_dir->e[0];
	reflect.e[1] = 2 * dot * normal->e[1] - l_ray_dir->e[1];
	reflect.e[2] = 2 * dot * normal->e[2] - l_ray_dir->e[2];

	/*reflect.e[0] = l_ray_dir->e[0] - 2 * dot * normal->e[0];
	reflect.e[1] = l_ray_dir->e[1] - 2 * dot * normal->e[1];
	reflect.e[2] = l_ray_dir->e[2] - 2 * dot * normal->e[2];*/
	//printf("reflect vec: %.2f, %.2f, %.2f\n",
		//reflect.e[0], reflect.e[1], reflect.e[2]);
	return (get_unit_vector(reflect));
}

t_color	colmix_ambient_object(t_col_mix *mix, t_closest *obj, t_scene *scene)
{
	t_color col;

	mix->norm_obj = normalise_color(obj->col);
	mix->norm_amb = normalise_color(scene->amb.col);
	mix->norm_light = normalise_color(scene->light.col);
	mix->amb_contr= scalar_mply_vector(scene->amb.intens, mix->norm_amb);
	//debug("ambient contribution: %.2f, %.2f , %.2f - amb intensity: %.2f, amb norm col: %.2f, %.2f, %.2f\n", mix->amb_contr.e[0], mix->amb_contr.e[1], mix->amb_contr.e[2], scene->amb.intens, mix->norm_amb.e[0], mix->norm_amb.e[1], mix->norm_amb.e[2]);
	//col = add_vectors(mix->amb_contr, scalar_mply_vector(scene->amb.intens, mix->norm_obj));
	col = add_vectors(mix->amb_contr, scalar_mply_vector(scene->amb.intens, mix->norm_obj));
	//debug("col ambient object mix: %.2f, %.2f , %.2f\n", col.e[0], col.e[1], col.e[2]);
	return (col);
}

/*double	diffuse_shading
{
	
}*/

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
	double	t;
	t_plane *temp_p;
	
	temp_s = scene->sphere;
	while(temp_s)
	{
		if (obj->id != temp_s->id)
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
		if (obj->id != temp_p->id)
		{
			t = find_t_plane(l_ray, temp_p);
			if (t > 0 && t < l_ray->dist)
				return (true);
		}
		temp_p = temp_p->next;
	}
	// continue with other objects
	return (false);
}

t_color	calculate_background_color(t_scene *scene)
{
	//t_color	amb;
	//t_color	light;
	//t_color	backg_c;

	(void)scene;
	//amb = scalar_mply_vector(scene->amb.intens, scene->amb.col);
	//light = scalar_mply_vector(scene->light.intens, scene->light.col);
	//backg_c = add_vectors(amb, light);
	//return (backg_c);	
	return (create_triple(0, 0, 0));
}

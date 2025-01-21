/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_light_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hzimmerm <hzimmerm@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/19 18:01:47 by hzimmerm          #+#    #+#             */
/*   Updated: 2025/01/21 13:39:33 by hzimmerm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scene.h"
#include "vector_setup.h"
#include "vector_math.h"

t_color	reflection_vector(t_vec *l_ray_dir, t_vec *normal)
{
	t_color	reflect;
	double	dot;

	dot = dot_product(*l_ray_dir, *normal);
	if (dot < -1.0)
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
	double	offset;
	t_vec	offset_vec;

	offset = 1e-4;
	offset_vec = scalar_mply_vector(offset, obj->normal_v);
	l_ray->orig = add_vectors(obj->hit_point, offset_vec);
	l_ray->dir = vec1_minus_vec2(scene->light.pos, l_ray->orig);
}

t_color	specular_light(t_ray *l_ray, t_scene *scene, t_closest *obj)
{
	t_spec_l	spec;
	t_color		spec_contr;

	spec.reflectivity = 0.3;
	if (obj->id % 2)
		spec.shininess = 5;
	else
		spec.shininess = 30;
	spec.reflect_dir = reflection_vector(&l_ray->dir, &obj->normal_v);
	spec.view_dir = get_unit_vector(vec1_minus_vec2(scene->camera.pos, \
		obj->hit_point));
	spec.intens = fmax(dot_product(spec.reflect_dir, spec.view_dir), 0.0);
	spec.intens = pow(spec.intens, spec.shininess);
	spec_contr = scalar_mply_vector(spec.intens * scene->light.intens, \
		scene->light.col);
	spec_contr = scalar_mply_vector(spec.intens * spec.reflectivity, \
		spec_contr);
	return (spec_contr);
}

t_color	multiply_cols(t_color col1, t_color col2)
{
	t_color	col;

	col.e[0] = col1.e[0] * col2.e[0];
	col.e[1] = col1.e[1] * col2.e[1];
	col.e[2] = col1.e[2] * col2.e[2];
	return (col);
}

t_color	normalise_color(t_color col)
{
	t_color	color;

	color.e[0] = col.e[0] / 255.0;
	color.e[1] = col.e[1] / 255.0;
	color.e[2] = col.e[2] / 255.0;
	return (color);
}

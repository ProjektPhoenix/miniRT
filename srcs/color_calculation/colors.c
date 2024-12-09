/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hzimmerm <hzimmerm@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 18:12:12 by hzimmerm          #+#    #+#             */
/*   Updated: 2024/12/09 19:00:42 by hzimmerm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "scene.h"
#include "vector_setup.h"
#include "vector_math.h"
#include "debug.h"

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

	obj->normal_v = assign_normal(obj);
	make_light_ray(&l_ray, scene, obj);
	blocked = check_blocking_objects(&l_ray, scene, obj);
	mix.final = colmix_ambient_object(&mix, obj, scene);
	if (!blocked)
		add_light(&l_ray, &mix, scene, obj->normal_v);
	mix.final.e[0] = fmin(mix.final.e[0] * 255.0, 255.0);
	mix.final.e[1] = fmin(mix.final.e[1] * 255.0, 255.0);
	mix.final.e[2] = fmin(mix.final.e[2] * 255.0, 255.0);
	return (mix.final);
}

void	add_light(t_ray *l_ray, t_col_mix *mix, t_scene *scene, t_vec norm)
{
	double l_dist;
	t_color diff_light;

	l_dist = get_magnitude(l_ray->dir);
	l_ray->dir = get_unit_vector(l_ray->dir);
	mix->diff_intens = fmax(dot_product(l_ray->dir, norm), 0.0);
	mix->attenuation = 1.0 / (l_dist * l_dist);
	//mix->attenuation = 1.0 / (1.0 + 0.1 * l_dist + 0.01 * l_dist * l_dist);
	mix->diff_intens *= mix->attenuation * 100;
	//debug("diff_intens:%.2f\n", mix->diff_intens);
	diff_light = scalar_mply_vector(scene->light.intens * mix->diff_intens, mix->norm_light);
	if (!scene->amb.intens)
		mix->diff_contr = add_vectors(diff_light, scalar_mply_vector(mix->diff_intens * scene->light.intens, mix->norm_obj));
	else
		mix->diff_contr = add_vectors(diff_light, scalar_mply_vector(mix->diff_intens * scene->light.intens, mix->final));
	mix->final = add_vectors(mix->final, mix->diff_contr);
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
	t_sphere	*temp;
	double	t;

	
	temp = scene->sphere;
	while(temp)
	{
		if (obj->id != temp->id)
		{
			t = find_t_sphere(l_ray, temp); //unit vector uebergeben 
			if (t > 0 && t < get_magnitude(l_ray->dir))
			{
				debug("object is blocking light\n");
				return (true);
			}
		}
		temp = temp->next;
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

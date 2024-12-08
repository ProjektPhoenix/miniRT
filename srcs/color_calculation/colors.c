/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hzimmerm <hzimmerm@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 18:12:12 by hzimmerm          #+#    #+#             */
/*   Updated: 2024/12/08 22:11:17 by hzimmerm         ###   ########.fr       */
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

	t_ray	l_ray;
	bool	blocked;
	double l_dist;
	double diffuse_intens;
	double attenuation;
	t_color	color;
	t_color diffuse_contr;

	diffuse_contr = create_triple(0, 0, 0);	
	obj->normal_v = assign_normal(obj);
	//return (debug_norm_vecs(obj));
	make_light_ray(&l_ray, scene, obj);
	blocked = check_blocking_objects(&l_ray, scene, obj);
	//color = obj->col;
	t_color norm_obj_col = normalise_color(obj->col);
	t_color norm_amb_col = normalise_color(scene->amb.col);
	t_color norm_light_col = normalise_color(scene->light.col);
	t_color ambient_col = scalar_mply_vector(scene->amb.intens, norm_amb_col);
	color = add_vectors(ambient_col, norm_obj_col);
	//color = add_vectors(scalar_mply_vector(scene->amb.intens, scene->amb.col), obj->col);
	//debug("color before ligth calc: %.2f, %.2f, %.2f\n", color.e[0], color.e[1], color.e[2]);
	if (blocked == false)
	{
		l_dist = get_magnitude(l_ray.dir);
		//printf("\nDistance of light source: %f", l_dist);
		l_ray.dir = get_unit_vector(l_ray.dir);
		//printf(" - l_ray dir %.2f, %.2f, %.2f - ", l_ray.dir.e[0], l_ray.dir.e[1], l_ray.dir.e[2]);
		//printf(" - norm vec dir %.2f, %.2f, %.2f - ", obj->normal_v.e[0], obj->normal_v.e[1], obj->normal_v.e[2]);
		//printf("from hit_point %.2f, %.2f, %.2f\n", obj->hit_point.e[0], obj->hit_point.e[1], obj->hit_point.e[2]);
		
		//if (dot_product(l_ray.dir, obj->normal_v) >= 0)
		//printf("\nResult dot product diffusion intensity: %f for hitpoint: (%f, %f, %f)", dot_product(l_ray.dir, obj->normal_v), obj->hit_point.e[0], obj->hit_point.e[1], obj->hit_point.e[2]);
		diffuse_intens = fmax(dot_product(l_ray.dir, obj->normal_v), 0.0);
		//diffuse_intens = dot_product(l_ray.dir, obj->normal_v);
		// attenuation = 1.0 / (l_dist * l_dist);
		attenuation = 1.0 / (1.0 + 0.1 * l_dist + 0.01 * l_dist * l_dist);
		//debug("diffuse_intens: %f\n", diffuse_intens);
		//debug("attenuation: %f\n", attenuation);
		//if (attenuation < 0.1)
			//attenuation = 0.1;
		//debug("attenuation: %f\n", attenuation);
		//if (diffuse_intens < 0.0)
			//diffuse_intens = 0.0;
		//else
			//debug("dot product/diffuse intensity: %f\n", diffuse_intens);
		diffuse_intens *= attenuation * 300;
		
		t_color diffuse_light = scalar_mply_vector(scene->light.intens * diffuse_intens, norm_light_col);
		diffuse_contr = add_vectors(diffuse_light, norm_obj_col);
		//debug("diffuse_contr: %.2f, %.2f, %.2f\n", diffuse_contr.e[0], diffuse_contr.e[1], diffuse_contr.e[2]);
		////color = add_vectors(color, scalar_mply_vector(scene->light.intens * diffuse_intens, scene->light.col));
		//int intensity = (int)((diffuse_intens * 255.0));
		//return (create_triple(intensity, intensity, intensity));
		color = add_vectors(color, diffuse_contr);
		//debug("color after ligth calc: %.2f, %.2f, %.2f\n", color.e[0], color.e[1], color.e[2]);

	}
	int r_value = (int)(fmin(color.e[0] * 255.0, 255.0));
	int g_value = (int)(fmin(color.e[1] * 255.0, 255.0));
	int b_value = (int)(fmin(color.e[2] * 255.0, 255.0));
	return create_triple(r_value, g_value, b_value);
	//return (color);
}


/*  backup from last version commit
t_color	calculate_obj_color(t_scene *scene, t_closest *obj)
{
	t_ray	l_ray;
	bool	blocked;
	double l_dist;
	double diffuse_intens;
	double attenuation;
	t_color	color;

	obj->normal_v = assign_normal(obj);
	//return (debug_norm_vecs(obj));
	make_light_ray(&l_ray, scene, obj);
	blocked = check_blocking_objects(&l_ray, scene, obj);
	//color = obj->col;
	t_color norm_obj_col = normalise_color(obj->col);
	t_color norm_amb_col = normalise_color(scene->amb.col);
	t_color norm_light_col = normalise_color(scene->light.col);
	color = add_vectors(scalar_mply_vector(1 - scene->amb.intens, norm_obj_col), 
		scalar_mply_vector(scene->amb.intens, norm_amb_col));
	if (blocked == false)
	{
		l_dist = get_magnitude(l_ray.dir);
		l_ray.dir = get_unit_vector(l_ray.dir);
		//printf("l_ray dir %.2f, %.2f, %.2f - ", l_ray.dir.e[0], l_ray.dir.e[1], l_ray.dir.e[2]);
		//printf("from hit_point %.2f, %.2f, %.2f\n", obj->hit_point.e[0], obj->hit_point.e[1], obj->hit_point.e[2]);
		diffuse_intens = dot_product(l_ray.dir, obj->normal_v);
		attenuation = 1.0 / (l_dist * l_dist);
		if (diffuse_intens > 0.0)
		{
			diffuse_intens *= attenuation;
			diffuse_intens = fmin(diffuse_intens, 1.0);
			color = add_vectors(color, scalar_mply_vector(scene->light.intens * diffuse_intens, norm_light_col));
				//printf("Ambient Color: %.2f, %.2f, %.2f\n", scene->amb.col.e[0], scene->amb.col.e[1], scene->amb.col.e[2]);
//printf("Base Color: %.2f, %.2f, %.2f\n", obj->col.e[0], obj->col.e[1], obj->col.e[2]);
//printf("Ambient intensity: %.2f\n", scene->amb.intens);
printf("Mixed Color: %.2f, %.2f, %.2f\n", color.e[0], color.e[1], color.e[2]);
		}
	
		//debug("inside blocked false\n");
		//debug("distance to light from hit point: %.2f\n", l_dist);
		//debug("hit point:  %.2f, %.2f, %.2f, normal vector: %.2f, %.2f, %.2f\n", obj->hit_point.e[0], obj->hit_point.e[1], obj->hit_point.e[2], obj->normal_v.e[0], obj->normal_v.e[1], obj->normal_v.e[2]);
		diffuse_intes = dot_product(get_unit_vector(l_ray.dir), obj->normal_v);
		attenuation = 1.0 / (scene->light.atten_a + scene->light.atten_b * l_dist + scene->light.atten_c * l_dist * l_dist);
		if (diffuse_intes > 0.0)
		{
			//debug("diffuse intensity: %f\n", diffuse_intes);
			color = add_vectors(color, scalar_mply_vector(scene->light.intens * diffuse_intes, scene->light.col));
		}
	}
	int r_value = (int)(fmin(color.e[0] * 255.0, 255.0));
	int g_value = (int)(fmin(color.e[1] * 255.0, 255.0));
	int b_value = (int)(fmin(color.e[2] * 255.0, 255.0));
	return create_triple(r_value, g_value, b_value);*/
	//return (color);
//}

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
	double offset;

	offset = 1e-4;
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
	t_color	amb;
	t_color	light;
	t_color	backg_c;

	amb = scalar_mply_vector(scene->amb.intens, scene->amb.col);
	light = scalar_mply_vector(scene->light.intens, scene->light.col);
	backg_c = add_vectors(amb, light);
	//return (backg_c);	
	return (create_triple(0, 0, 0));
}

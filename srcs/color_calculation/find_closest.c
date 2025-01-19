/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_closest.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hzimmerm <hzimmerm@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/19 17:52:23 by hzimmerm          #+#    #+#             */
/*   Updated: 2025/01/19 18:00:00 by hzimmerm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scene.h"
#include "vector_setup.h"
#include "vector_math.h"


void	find_closest(t_ray *ray, t_scene *scene, t_closest *obj)
{
	double		t;

	search_spheres(&t, obj, ray, scene);
	search_planes(&t, obj, ray, scene);
	search_cylinders(&t, obj, ray, scene);
}

void search_spheres(double *t, t_closest *obj, t_ray *ray, t_scene *scene)
{
	t_sphere	*temp_s;

	temp_s = scene->sphere;
	while(temp_s)
	{
		*t = find_t_sphere(ray, temp_s);
		if (*t >= 0 && *t < obj->distance)
		{
			obj->distance = *t;
			if (obj->distance == 0)
				break;
			obj->id = temp_s->id;
			obj->col = temp_s->col;
			obj->type = SPHERE;
			obj->center = temp_s->center;
		}
		temp_s = temp_s->next;
	}
}

void search_planes(double *t, t_closest *obj, t_ray *ray, t_scene *scene)
{
	t_plane		*temp_p;

	temp_p = scene->plane;
	while (temp_p)
	{
		*t = find_t_plane(ray, temp_p);
		if (*t >= 0 && *t < obj->distance)
		{
			obj->distance = *t;
			if (obj->distance == 0)
				break;
			obj->id = temp_p->id;
			obj->col = temp_p->col;
			obj->type = PLANE;
			obj->normal_v = temp_p->ortho;
		}
		temp_p = temp_p->next;
	}
}


void search_cylinders(double *t, t_closest *obj, t_ray *ray, t_scene *scene)
{
	t_cylinder	*temp_c;

	temp_c = scene->cyl;
	while (temp_c)
	{
		*t = find_t_cylinder(ray, temp_c);
		if (*t >= 0 && *t < obj->distance)
		{
			obj->distance = *t;
			if (obj->distance == 0)
				break;
			obj->id = temp_c->id;
			obj->col = temp_c->col;
			obj->type = CYL;
			obj->normal_v = temp_c->c.normal_v;
		}
		temp_c = temp_c->next;
	}
}

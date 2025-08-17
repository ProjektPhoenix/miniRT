/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_check.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hzimmerm <hzimmerm@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 13:58:21 by hzimmerm          #+#    #+#             */
/*   Updated: 2025/01/24 20:15:04 by hzimmerm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "libft.h"
#include "scene.h"

static int	check_color(t_color col)
{
	if (col.e[0] < 0.0 || col.e[0] > 255.0 || col.e[1] < 0.0 
		|| col.e[1] > 255.0 || col.e[2] < 0.0 || col.e[2] > 255.0)
		return (printf("Error\nColor values need to be between 0 an 255\n"), 1);
	return (0);
}

static int	check_vec(t_vec vec)
{
	if (vec.e[0] == 0 && vec.e[1] == 0 && vec.e[2] == 0)
		return (printf("Error\nVectors cannot be 0,0,0\n"), 1);
	return (0);
}

static int	check_cylinder(t_scene *scene)
{
	t_cylinder	*tmp_c;

	tmp_c = scene->cyl;
	while (tmp_c)
	{
		if (check_color(tmp_c->col) || check_vec(tmp_c->dir) 
			|| tmp_c->diameter == 0)
			return (printf("Please verify details of "
					"cylinder id %d\n", tmp_c->id), 1);
		tmp_c = tmp_c->next;
	}
	return (0);
}

static int	check_objects(t_scene *scene)
{
	t_sphere	*tmp_s;
	t_plane		*tmp_p;

	tmp_s = scene->sphere;
	tmp_p = scene->plane;
	while (tmp_s)
	{
		if (check_color(tmp_s->col) || tmp_s->diameter == 0)
			return (printf("Please verify details of "
					"sphere id %d\n", tmp_s->id), 1);
		tmp_s = tmp_s->next;
	}
	while (tmp_p)
	{
		if (check_color(tmp_p->col) || check_vec(tmp_p->ortho))
			return (printf("Please verify details of "
					"plane id %d\n", tmp_p->id), 1);
		tmp_p = tmp_p->next;
	}
	if (check_cylinder(scene))
		return (1);
	return (0);
}

int	make_error_check(t_scene *scene, t_parse_flags *check)
{
	if (!check->flag_c)
		return (printf("Error\nProgram needs Camera\n"), 1);
	if (!check->flag_a && !check->flag_l)
		return (printf("Error\nProgram needs at least one light source\n"), 1);
	if (scene->camera.fov > 179.0)
		return (printf("Error\nCamera FOV has to be below 180\n"), 1);
	if (scene->camera.dir.e[0] == 0 && scene->camera.dir.e[1] == 0 
		&& scene->camera.dir.e[2] == 0)
		return (printf("Error\nCamera direction cannot be 0,0,0\n"), 1);
	if (scene->amb.intens > 1 || scene->amb.intens < 0)
		return (printf("Error\nAmbient intensity needs to be "
				"between 0 and 1\n"), 1);
	if (scene->light.intens > 1 || scene->light.intens < 0)
		return (printf("Error\nLight intensity needs to be between "
				"0 and 1\n"), 1);
	if (check_color(scene->amb.col) || check_color(scene->light.col))
		return (1);
	if (check_objects(scene))
		return (1);
	is_p_on_plane(scene);
	return (0);
}

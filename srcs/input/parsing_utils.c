/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hzimmerm <hzimmerm@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 13:26:08 by hzimmerm          #+#    #+#             */
/*   Updated: 2025/01/28 14:23:05 by hzimmerm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//#include "../../includes/vector_setup.h"
#include "minirt.h"
#include "libft.h"
#include "scene.h"

/* takes scene as input and initialises all basic variables */
void	init_scene(t_scene *scene, t_parse_flags *check)
{
	scene->camera.pos = create_triple(0, 0, 0);
	scene->camera.fov = 0;
	scene->amb.intens = 1.0;
	scene->amb.col = create_triple(0, 0, 0);
	scene->light.pos = create_triple(0, 0, 0);
	scene->light.intens = 0.0;
	scene->light.col = create_triple(1, 1, 1);
	scene->sphere = NULL;
	scene->cyl = NULL;
	scene->plane = NULL;
	scene->id_count = 0;
	scene->fd = -1;
	check->flag_a = false;
	check->flag_c = false;
	check->flag_l = false;
}

/* takes scene as argument, adds and returns a new sphere node */
t_sphere	*add_sphere_node(t_scene *scene)
{
	t_sphere	*new;
	t_sphere	*temp;

	new = malloc(sizeof(t_sphere));
	if (!new)
		cleanup_scene_exit(scene, "malloc fail\n", 1, NULL);
	new->col = create_triple(0, 0, 0);
	new->center = create_triple(0, 0, 0);
	new->diameter = 0.0;
	new->id = scene->id_count;
	scene->id_count++;
	new->next = NULL;
	if (!scene->sphere)
		scene->sphere = new;
	else
	{
		temp = scene->sphere;
		while (temp->next)
			temp = temp->next;
		temp->next = new;
	}
	return (new);
}

/* takes scene as argument, adds and returns a new dylinder node */
t_cylinder	*add_cylinder_node(t_scene *scene)
{
	t_cylinder	*new;
	t_cylinder	*temp;

	new = malloc(sizeof(t_cylinder));
	if (!new)
		cleanup_scene_exit(scene, "malloc fail\n", 1, NULL);
	new->center = create_triple(0, 0, 0);
	new->col = create_triple(0, 0, 0);
	new->dir = create_triple(0, 0, 0);
	new->diameter = 0.0;
	new->height = 0.0;
	new->id = scene->id_count;
	scene->id_count++;
	new->next = NULL;
	if (!scene->cyl)
		scene->cyl = new;
	else
	{
		temp = scene->cyl;
		while (temp->next)
			temp = temp->next;
		temp->next = new;
	}
	return (new);
}

/* takes scene as argument, adds and returns a new plane node */
t_plane	*add_plane_node(t_scene *scene)
{
	t_plane	*new;
	t_plane	*temp;

	new = malloc(sizeof(t_plane));
	if (!new)
		cleanup_scene_exit(scene, "malloc fail\n", 1, NULL);
	new->col = create_triple(0, 0, 0);
	new->ortho = create_triple(0, 0, 0);
	new->pos = create_triple(0, 0, 0);
	new->id = scene->id_count;
	scene->id_count++;
	new->next = NULL;
	if (!scene->plane)
		scene->plane = new;
	else
	{
		temp = scene->plane;
		while (temp->next)
			temp = temp->next;
		temp->next = new;
	}
	return (new);
}

int	contains_valid(char *str)
{
	int	i;
	int	point;

	i = 0;
	point = 0;
	if (!str || !str[0])
		return (0);
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i])
	{
		if (!(str[i] >= '0' && str[i] <= '9'))
		{
			if (str[i] == '.')
			{
				point++;
				if (point > 1)
					return (0);
			}
			else
				return (0);
		}
		i++;
	}
	return (1);
}

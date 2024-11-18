/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hzimmerm <hzimmerm@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 13:26:08 by hzimmerm          #+#    #+#             */
/*   Updated: 2024/11/18 15:51:59 by hzimmerm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//#include "../../includes/vector_setup.h"
#include "minirt.h"
#include "libft.h"
#include "scene.h"

/* takes scene as input and initialises all basic variables */
void	init_scene(t_scene *scene)
{
	scene->camera.pos.e[0] = 0.0;
	scene->camera.pos.e[1] = 0.0;
	scene->camera.pos.e[2] = 0.0;
	scene->camera.fov = 0;
	scene->ambient.intensity = 0.0;
	scene->ambient.col.e[0] = 0;
	scene->ambient.col.e[1] = 0;
	scene->ambient.col.e[2] = 0;
	scene->light.pos.e[0] = 0.0;
	scene->light.pos.e[1] = 0.0;
	scene->light.pos.e[2] = 0.0;
	scene->light.intensity = 0.0;
	scene->sphere = NULL;
	scene->cyl = NULL;
	scene->plane = NULL;
	scene->flag_A = false;
	scene->flag_C = false;
	scene->flag_L = false;
	scene->id_count = 0;
}
/* takes as input one line from the .rt file and the scene - checks if starting element is valid */
int	is_valid(char *str, t_scene *scene)
{
	if (ft_strncmp(str, "A", 2) && ft_strncmp(str, "C", 2) && ft_strncmp(str, "L", 2)
		&& ft_strncmp(str, "sp", 3) && ft_strncmp(str, "pl", 3) && ft_strncmp(str, "cy", 3))
		cleanup_scene_exit(scene, "Error\nValid elements only are: A, C, L, pl, sp and cy\n", 2);
	else if ((!ft_strncmp(str, "A", 2) && scene->flag_A == true) || (!ft_strncmp(str, "C", 2) && scene->flag_C == true)
		|| (!ft_strncmp(str, "L", 2) && scene->flag_L == true))
		cleanup_scene_exit(scene, "Error\nA, C and L can only be entered once\n", 2);
	return (1);
}

/* checks if the memory allocation of coord was succesful, otherwise frees and exits */
void	check_alloc(t_scene *scene, char **coord, char **array, char *mssg)
{
	if (!coord)
	{
		free_array(array);
		cleanup_scene_exit(scene, mssg, 2);
	}
}

/* takes scene as argument, adds and returns a new sphere node */
t_sphere	*add_sphere_node(t_scene *scene)
{
	t_sphere	*new;
	t_sphere	*temp;
	
	new = malloc(sizeof(t_sphere));
	if (!new)
		cleanup_scene_exit(scene, "malloc error\n", 2);
	new->center.e[0] = 0.0;
	new->center.e[1] = 0.0;
	new->center.e[2] = 0.0;
	new->col.e[0] = 0.0;
	new->col.e[1] = 0.0;
	new->col.e[2] = 0.0;
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
		cleanup_scene_exit(scene, "malloc error\n", 2);
	new->center.e[0] = 0.0;
	new->center.e[1] = 0.0;
	new->center.e[2] = 0.0;
	new->col.e[0] = 0.0;
	new->col.e[1] = 0.0;
	new->col.e[2] = 0.0;
	new->dir.e[0] = 0.0;
	new->dir.e[1] = 0.0;
	new->dir.e[2] = 0.0;
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
		cleanup_scene_exit(scene, "malloc error\n", 2);
	new->col.e[0] = 0.0;
	new->col.e[1] = 0.0;
	new->col.e[2] = 0.0;
	new->ortho.e[0] = 0.0;
	new->ortho.e[1] = 0.0;
	new->ortho.e[2] = 0.0;
	new->pos.e[0] = 0.0;
	new->pos.e[1] = 0.0;
	new->pos.e[2] = 0.0;
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

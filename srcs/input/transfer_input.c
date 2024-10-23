/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transfer_input.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hzimmerm <hzimmerm@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 16:17:51 by hzimmerm          #+#    #+#             */
/*   Updated: 2024/10/23 17:53:51 by hzimmerm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/vector_setup.h"
#include "../../includes/miniRT.h"
#include "../libft/libft.h"

void	process_c(char **array, t_scene *scene)
{
	char **coord;

	scene->flag_C = true;
	if (!array[1])
		cleanup_exit(scene, "Error\nCamera is missing features");
	coord = ft_split(array[1], ',');
	if (!coord)
	{
		free_array(array);
		cleanup_exit(scene, "Error in splitting camera position coordinates\n");
	}
	set_triple_from_string(&scene->camera.pos, coord);
	if (!array[2])
		cleanup_exit(scene, "Error\nCamera is missing orientation");
	coord = ft_split(array[2], ',');
	if (!coord)
	{
		free_array(array);
		cleanup_exit(scene, "Error in splitting camera orientation coordinates\n");
	}
	set_triple_from_string(&scene->camera.dir, coord);
	if (!array[3])
		cleanup_exit(scene, "Error\nCamera is missing FOV");
	scene->camera.fov = ft_atod(array[3]);
}

void	process_l(char **array, t_scene *scene)
{
	char **coord;

	scene->flag_L = true;
	if (!array[1])
		cleanup_exit(scene, "Error\nLight is missing features");
	coord = ft_split(array[1], ',');
	if (!coord)
	{
		free_array(array);
		cleanup_exit(scene, "Error in splitting light position coordinates\n");
	}
	set_triple_from_string(&scene->light.pos, coord);
	if (!array[2])
		cleanup_exit(scene, "Error\nLight is missing brightness ratio");
	scene->light.intensity = ft_atod(array[2]);
}


void	process_sp(char **array, t_scene *scene)
{
	char **coord;

	scene->flag_sp = true;
	if (!array[1])
		cleanup_exit(scene, "Error\nSphere is missing features");
	coord = ft_split(array[1], ',');
	if (!coord)
	{
		free_array(array);
		cleanup_exit(scene, "Error in splitting sphere center coordinates\n");
	}
	set_triple_from_string(&scene->sphere[scene->i].center, coord);
	if (!array[2])
		cleanup_exit(scene, "Error\nSphere is missing diameter");
	scene->sphere[scene->i].diameter = ft_atod(array[2]);
	if (!array[3])
		cleanup_exit(scene, "Error\nSphere is missing color");
	coord = ft_split(array[3], ',');
	if (!coord)
	{
		free_array(array);
		cleanup_exit(scene, "Error in splitting sphere center coordinates\n");
	}
	set_triple_from_string(&scene->sphere[scene->i].col, coord);
	(scene->i)++;
}

void	process_pl(char **array, t_scene *scene)
{
	char **coord;

	scene->flag_pl = true;
	if (!array[1])
		cleanup_exit(scene, "Error\nPlane is missing features");
	coord = ft_split(array[1], ',');
	if (!coord)
	{
		free_array(array);
		cleanup_exit(scene, "Error in splitting point in plane coordinates\n");
	}
	set_triple_from_string(&scene->plane[scene->j].pos, coord);
	if (!array[2])
		cleanup_exit(scene, "Error\nPlane is missing norm vector\n");
	coord = ft_split(array[2], ',');
	if (!coord)
	{
		free_array(array);
		cleanup_exit(scene, "Error in splitting plane norm vector coordinates\n");
	}
	set_triple_from_string(&scene->plane[scene->j].dir, coord);
	if (!array[3])
		cleanup_exit(scene, "Error\nPlane is missing color");
	coord = ft_split(array[3], ',');
	if (!coord)
	{
		free_array(array);
		cleanup_exit(scene, "Error in splitting sphere center coordinates\n");
	}
	set_triple_from_string(&scene->plane[scene->j].col, coord);
	(scene->j)++;
}


void	process_cy(char **array, t_scene *scene)
{
	char **coord;

	scene->flag_cy = true;
	if (!array[1])
		cleanup_exit(scene, "Error\nCylinder is missing features");
	coord = ft_split(array[1], ',');
	if (!coord)
	{
		free_array(array);
		cleanup_exit(scene, "Error in splitting cylinder center coordinates\n");
	}
	set_triple_from_string(&scene->cyl[scene->k].center, coord);
	if (!array[2])
		cleanup_exit(scene, "Error\nCylinder is missing norm vector\n");
	coord = ft_split(array[2], ',');
	if (!coord)
	{
		free_array(array);
		cleanup_exit(scene, "Error in splitting cylinder norm vector coordinates\n");
	}
	set_triple_from_string(&scene->cyl[scene->k].dir, coord);
	if (!array[3])
		cleanup_exit(scene, "Error\nCylinder is missing diameter");
	scene->cyl[scene->k].diameter = ft_atod(array[3]);
	if (!array[4])
		cleanup_exit(scene, "Error\nCylinder is missing height");
	scene->cyl[scene->k].height = ft_atod(array[4]);
	if (!array[5])
		cleanup_exit(scene, "Error\nCylinder is missing color");
	coord = ft_split(array[5], ',');
	if (!coord)
	{
		free_array(array);
		cleanup_exit(scene, "Error in splitting cylinder color\n");
	}
	set_triple_from_string(&scene->cyl[scene->k].col, coord);
	(scene->k)++;
}


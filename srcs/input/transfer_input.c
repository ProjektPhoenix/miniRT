/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transfer_input.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hzimmerm <hzimmerm@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 16:17:51 by hzimmerm          #+#    #+#             */
/*   Updated: 2024/11/18 20:09:56 by hzimmerm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector_setup.h"
#include "minirt.h"
#include "libft.h"
#include "scene.h"

/* transfers the input of a line starting with 'C' (camera) into the camera struct */
void	process_c(char **array, t_scene *scene)
{
	char **coord;

	scene->flag_C = true;
	if (!array[1])
		cleanup_scene_exit(scene, "Error\nCamera is missing features", 2);
	coord = ft_split(array[1], ',');
	check_alloc(scene, coord, array, "Error splitting camera position coordinates\n");
	set_triple_from_array(&scene->camera.pos, coord);
	if (!array[2])
		cleanup_scene_exit(scene, "Error\nCamera is missing orientation", 2);
	coord = ft_split(array[2], ',');
	check_alloc(scene, coord, array, "Error splitting camera orientation coordinates\n");
	set_triple_from_array(&scene->camera.dir, coord);
	if (!array[3])
		cleanup_scene_exit(scene, "Error\nCamera is missing FOV", 2);
	scene->camera.fov = ft_atod(array[3]);
}

/* transfers the input of a line starting with 'AL' (light) into the light struct */
void	process_l(char **array, t_scene *scene)
{
	char **coord;

	scene->flag_L = true;
	if (!array[1])
		cleanup_scene_exit(scene, "Error\nLight is missing features", 2);
	coord = ft_split(array[1], ',');
	check_alloc(scene, coord, array, "Error splitting light position coordinates\n");
	set_triple_from_array(&scene->light.pos, coord);
	if (!array[2])
		cleanup_scene_exit(scene, "Error\nLight is missing brightness ratio", 2);
	scene->light.intens = ft_atod(array[2]);
}

/* transfers the input of a line starting with 'sp' (sphere) into the sphere struct */
void	process_sp(char **array, t_scene *scene)
{
	t_sphere	*new;
	char **coord;

	if (!array[1])
		cleanup_scene_exit(scene, "Error\nSphere is missing features", 2);
	new = add_sphere_node(scene);
	coord = ft_split(array[1], ',');
	check_alloc(scene, coord, array, "Error splitting sphere center coordinates\n");
	set_triple_from_array(&new->center, coord);
	if (!array[2])
		cleanup_scene_exit(scene, "Error\nSphere is missing diameter", 2);
	new->diameter = ft_atod(array[2]);
	if (!array[3])
		cleanup_scene_exit(scene, "Error\nSphere is missing color", 2);
	coord = ft_split(array[3], ',');
	check_alloc(scene, coord, array, "Error splitting sphere center coordinates\n");
	set_triple_from_array(&new->col, coord);
}

/* transfers the input of a line starting with 'pl' (plane) into the plane struct */
void	process_pl(char **array, t_scene *scene)
{
	t_plane	*new;
	char **coord;

	if (!array[1])
		cleanup_scene_exit(scene, "Error\nPlane is missing features", 2);
	new = add_plane_node(scene);
	coord = ft_split(array[1], ',');
	check_alloc(scene, coord, array, "Error splitting point in plane coordinates\n");
	set_triple_from_array(&new->pos, coord);
	if (!array[2])
		cleanup_scene_exit(scene, "Error\nPlane is missing norm vector\n", 2);
	coord = ft_split(array[2], ',');
	check_alloc(scene, coord, array, "Error splitting plane norm vector coordinates\n");
	set_triple_from_array(&new->ortho, coord);
	if (!array[3])
		cleanup_scene_exit(scene, "Error\nPlane is missing color", 2);
	coord = ft_split(array[3], ',');
	check_alloc(scene, coord, array, "Error in splitting sphere center coordinates\n");
	set_triple_from_array(&new->col, coord);
}

/* transfers the input of a line starting with 'cy' (cylinder) into the cyl struct */
void	process_cy(char **array, t_scene *scene)
{
	t_cylinder	*new;
	char **coord;

	if (!array[1])
		cleanup_scene_exit(scene, "Error\nCylinder is missing features", 2);
	new = add_cylinder_node(scene);
	coord = ft_split(array[1], ',');
	check_alloc(scene, coord, array, "Error splitting cylinder center coordinates\n");
	set_triple_from_array(&new->center, coord);
	if (!array[2])
		cleanup_scene_exit(scene, "Error\nCylinder is missing norm vector\n", 2);
	coord = ft_split(array[2], ',');
	check_alloc(scene, coord, array, "Error splitting cylinder norm vector coordinates\n");
	set_triple_from_array(&new->dir, coord);
	if (!array[3])
		cleanup_scene_exit(scene, "Error\nCylinder is missing diameter", 2);
	new->diameter = ft_atod(array[3]);
	if (!array[4])
		cleanup_scene_exit(scene, "Error\nCylinder is missing height", 2);
	new->height = ft_atod(array[4]);
	if (!array[5])
		cleanup_scene_exit(scene, "Error\nCylinder is missing color", 2);
	coord = ft_split(array[5], ',');
	check_alloc(scene, coord, array, "Error splitting cylinder color\n");
	set_triple_from_array(&new->col, coord);
}


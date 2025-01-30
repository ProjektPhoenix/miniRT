/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_input.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hzimmerm <hzimmerm@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 16:17:51 by hzimmerm          #+#    #+#             */
/*   Updated: 2025/01/28 12:42:09 by hzimmerm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "libft.h"
#include "scene.h"

// transfers the input of a line starting with 
// 'C' (camera) into the camera struct
void	process_c(char **array, t_scene *scene, t_parse_flags *check)
{
	char	**coord;

	check->flag_c = true;
	if (!array[1])
		cleanup_scene_exit(scene, "Camera is missing features\n", 2, array);
	coord = split_and_check(scene, array[1], array, "Error splitting camera "
			"position coordinates\n");
	set_triple_from_array(&scene->camera.pos, coord, scene, array);
	if (!array[2])
		cleanup_scene_exit(scene, "Camera is missing orientation", \
			2, array);
	coord = split_and_check(scene, array[2], array, "Error splitting camera "
			"orientation coordinates\n");
	set_triple_from_array(&scene->camera.dir, coord, scene, array);
	if (!array[3] || !contains_valid(array[3]))
		cleanup_scene_exit(scene, "Camera has no or invalid FOV", 2, array);
	scene->camera.fov = ft_atod(array[3]);
}

// transfers the input of a line starting with 
// 'AL' (light) into the light struct
void	process_l(char **array, t_scene *scene, t_parse_flags *check)
{
	char	**coord;

	check->flag_l = true;
	if (!array[1])
		cleanup_scene_exit(scene, "Light is missing features\n", 2, array);
	coord = split_and_check(scene, array[1], array, "Error splitting light "
			"position coordinates\n");
	set_triple_from_array(&scene->light.pos, coord, scene, array);
	if (!array[2] || !contains_valid(array[2]))
		cleanup_scene_exit(scene, "Light has no or invalid brightness ratio", \
			2, array);
	scene->light.intens = ft_atod(array[2]);
	if (array[3])
	{
		coord = split_and_check(scene, array[3], array, "Error in "
				"splitting light colors\n");
		set_triple_from_array(&scene->light.col, coord, scene, array);
		scene->light.col = normalise_color(scene->light.col);
	}
}

// transfers the input of a line starting with 
// 'sp' (sphere) into the sphere struct
void	process_sp(char **array, t_scene *scene)
{
	t_sphere	*new;
	char		**coord;

	if (!array[1])
		cleanup_scene_exit(scene, "Sphere is missing features\n", 2, array);
	new = add_sphere_node(scene);
	coord = split_and_check(scene, array[1], array, "Error splitting sphere "
			"center coordinates\n");
	set_triple_from_array(&new->center, coord, scene, array);
	if (!array[2] || !contains_valid(array[2]))
		cleanup_scene_exit(scene, "Sphere has no or invalid diameter\n", \
			2, array);
	new->diameter = ft_atod(array[2]);
	if (!array[3])
		cleanup_scene_exit(scene, "Sphere is missing color\n", 2, array);
	coord = split_and_check(scene, array[3], array, "Error splitting sphere "
			"center coordinates\n");
	set_triple_from_array(&new->col, coord, scene, array);
}

// transfers the input of a line starting with 
// 'pl' (plane) into the plane struct
void	process_pl(char **array, t_scene *scene)
{
	t_plane	*new;
	char	**coord;

	if (!array[1])
		cleanup_scene_exit(scene, "Plane is missing features\n", 2, array);
	new = add_plane_node(scene);
	coord = split_and_check(scene, array[1], array, "Error splitting point in "
			"plane coordinates\n");
	set_triple_from_array(&new->pos, coord, scene, array);
	if (!array[2])
		cleanup_scene_exit(scene, "Plane is missing norm vector\n", 2, array);
	coord = split_and_check(scene, array[2], array, "Error splitting plane "
			"norm vector coordinates\n");
	set_triple_from_array(&new->ortho, coord, scene, array);
	if (!array[3])
		cleanup_scene_exit(scene, "Plane is missing color\n", 2, array);
	coord = split_and_check(scene, array[3], array, "Error in splitting "
			"sphere center coordinates\n");
	set_triple_from_array(&new->col, coord, scene, array);
}

// transfers the input of a line starting with 
// 'cy' (cylinder) into the cyl struct
void	process_cy(char **array, t_scene *scene)
{
	t_cylinder	*new;
	char		**coord;

	if (!array[1])
		cleanup_scene_exit(scene, "Cylinder is missing features\n", 2, array);
	new = add_cylinder_node(scene);
	coord = split_and_check(scene, array[1], array, "Error splitting cylinder "
			"center coordinates\n");
	set_triple_from_array(&new->center, coord, scene, array);
	if (!array[2])
		cleanup_scene_exit(scene, "Cylinder is missing norm vector\n", 2, array);
	coord = split_and_check(scene, array[2], array, "Error splitting cylinder "
			"norm vector coordinates\n");
	set_triple_from_array(&new->dir, coord, scene, array);
	if (!array[3] || !contains_valid(array[3]))
		cleanup_scene_exit(scene, "Cylinder has invalid diameter\n", 2, array);
	new->diameter = ft_atod(array[3]);
	if (!array[4] || !contains_valid(array[4]))
		cleanup_scene_exit(scene, "Cylinder has invalid height\n", 2, array);
	new->height = ft_atod(array[4]);
	if (!array[5])
		cleanup_scene_exit(scene, "Cylinder is missing color", 2, array);
	coord = split_and_check(scene, array[5], array, "Error splitting "
			"cylinder color\n");
	set_triple_from_array(&new->col, coord, scene, array);
}

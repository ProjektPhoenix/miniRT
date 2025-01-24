/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hzimmerm <hzimmerm@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 14:37:59 by hzimmerm          #+#    #+#             */
/*   Updated: 2025/01/24 20:21:43 by hzimmerm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "libft.h"
#include "scene.h"

//transfers the input of a line starting with 
//'A' (ambient light) into the ambl struct
void	process_a(char **array, t_scene *scene, t_parse_flags *check)
{
	char	**color;

	check->flag_a = true;
	if (!array[1])
		cleanup_scene_exit(scene, "Error\nAmbient light is missing features", 2);
	scene->amb.intens = ft_atod(array[1]);
	if (!array[2])
		cleanup_scene_exit(scene, "Error\nAmbient light is missing colors", 2);
	color = ft_split(array[2], ',');
	if (!color)
	{
		free_array(array);
		cleanup_scene_exit(scene, "Error in splitting "
			"ambient light colors\n", 2);
	}
	set_triple_from_array(&scene->amb.col, color, scene);
}

t_point	create_triple(double x, double y, double z)
{
	t_point	p;

	p.e[0] = x;
	p.e[1] = y;
	p.e[2] = z;
	return (p);
}

void	set_triple_from_array(t_vec *triple, char **coord, t_scene *scene)
{
	if (!coord[0] || !coord[1] || !coord[2])
		cleanup_scene_exit(scene, "Error: Please verify format for triplets, "
			"must be ints or floats without spaces\n", 1);
	triple->e[0] = ft_atod(coord[0]);
	triple->e[1] = ft_atod(coord[1]);
	triple->e[2] = ft_atod(coord[2]);
	free_array(coord);
	coord = NULL;
}

char	**split_and_check(t_scene *scene, char *str, char **arr, char *msg)
{
	char	**coord;

	coord = ft_split(str, ',');
	if (!coord)
	{
		free_array(arr);
		cleanup_scene_exit(scene, msg, 2);
	}
	return (coord);
}

int	is_p_on_plane(t_scene *scene)
{
	double	dot;
	t_plane	*temp;

	temp = scene->plane;
	while (temp)
	{
		temp->ortho = get_unit_vector(temp->ortho);
		dot = dot_product(temp->ortho, 
				vec1_minus_vec2(scene->light.pos, temp->pos));
		if (fabs(dot) < 1e-4)
			cleanup_scene_exit(scene, "Error: Light source cannot be "
				"on plane\n", 1);
		dot = dot_product(temp->ortho, 
				vec1_minus_vec2(scene->camera.pos, temp->pos));
		if (fabs(dot) < 1e-4)
			cleanup_scene_exit(scene, "Error: Camera cannot be "
				"on plane\n", 1);
		temp = temp->next;
	}
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hzimmerm <hzimmerm@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 13:02:42 by hzimmerm          #+#    #+#             */
/*   Updated: 2024/11/18 15:55:29 by hzimmerm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "libft.h"
#include "scene.h"

/* takes as arguments the name of the .rt file and the scene, prepares file for parsing 
needs to be added: propper error handling (file specs, minimum combination of elements etc.) */
int	parse_file(char *file, t_scene *scene)
{
	int	fd;
	char *line;

	init_scene(scene);
	fd = open(file, O_RDONLY);
	if (fd == -1)
		return (perror("Error opening file"), 1);
	line = get_next_line_new(fd);
	while (line)
	{
		if (line[0] != '\n')
			process_line(line, scene);
		free(line);
		line = NULL;
		line = get_next_line_new(fd);
	}
	close(fd);
	/* add check for enough elements to make plausible scene */
	print_file_testing(scene);
	return (0);
}

/* takes as arguments one line of the .rt file and the scene struct 
checks with the first elements of the line under which category it should be processed*/
void	process_line(char *line, t_scene *scene)
{
	char **line_elmts;

	line_elmts = ft_split_space(line);
	if (!line_elmts)
	{
		free(line);
		line = NULL;
		error_exit("Error\nft_split error\n");
	}
	is_valid(line_elmts[0], scene);
	if (!ft_strncmp(line_elmts[0], "A", 2))
		process_a(line_elmts, scene);
	else if (!ft_strncmp(line_elmts[0], "C", 2))
		process_c(line_elmts, scene);
	else if (!ft_strncmp(line_elmts[0], "L", 2))
		process_l(line_elmts, scene);
	else if (!ft_strncmp(line_elmts[0], "sp", 3))
		process_sp(line_elmts, scene);
	else if (!ft_strncmp(line_elmts[0], "pl", 3))
		process_pl(line_elmts, scene);
	else if (!ft_strncmp(line_elmts[0], "cy", 3))
		process_cy(line_elmts, scene);
	free_array(line_elmts);
}

/* transfers the input of a line starting with 'A' (ambient light) into the ambl struct */
void	process_a(char **array, t_scene *scene)
{
	char **color;
	scene->flag_A = true;
	if (!array[1])
		cleanup_scene_exit(scene, "Error\nAmbient light is missing features", 2);
	scene->ambient.intensity = ft_atod(array[1]);
	if (!array[2])
		cleanup_scene_exit(scene, "Error\nAmbient light is missing colors", 2);
	color = ft_split(array[2], ',');
	if (!color)
	{
		free_array(array);
		cleanup_scene_exit(scene, "Error in splitting ambient light colors\n", 2);
	}
	set_triple_from_array(&scene->ambient.col, color);
}

/* printing function to test input read */
void	print_file_testing(t_scene *scene)
{
	t_sphere	*temp_sp = scene->sphere;
	t_cylinder	*temp_cyl = scene->cyl;
	t_plane	*temp_pl = scene->plane;

	printf("Ambient: ratio %.2f, cols %.2f, %.2f, %.2f\n", 
		scene->ambient.intensity, 
		scene->ambient.col.e[0], scene->ambient.col.e[1], scene->ambient.col.e[2]);
	printf("Camera: view point %.2f, %.2f, %.2f, dir %.2f, %.2f, %.2f, fov %.2f\n", 
		scene->camera.pos.e[0], scene->camera.pos.e[1], scene->camera.pos.e[2], 
		scene->camera.dir.e[0], scene->camera.dir.e[1], scene->camera.dir.e[2], 
		scene->camera.fov);
	printf("Light position %.2f, %.2f, %.2f, intensity %.2f\n",
           scene->light.pos.e[0],
           scene->light.pos.e[1],
           scene->light.pos.e[2],
           scene->light.intensity);
	int i = 0;
	while (temp_sp)
	{
		printf("Sphere %d: center %.2f, %.2f, %.2f, diameter %.2f, color %.2f, %.2f, %.2f\n",
               i,
        	temp_sp->center.e[0],
        	temp_sp->center.e[1],
        	temp_sp->center.e[2],
        	temp_sp->diameter,
        	temp_sp->col.e[0],
        	temp_sp->col.e[1],
        	temp_sp->col.e[2]);
		temp_sp = temp_sp->next;
		i++;
	}
	i = 0;
	while (temp_pl)
	{
		printf("Plane %d: position %.2f, %.2f, %.2f, normal %.2f, %.2f, %.2f, color %.2f, %.2f, %.2f\n",
               i,
               temp_pl->pos.e[0],
               temp_pl->pos.e[1],
		temp_pl->pos.e[2],
               temp_pl->ortho.e[0],
              temp_pl->ortho.e[1],
               temp_pl->ortho.e[2],
               temp_pl->col.e[0],
               temp_pl->col.e[1],
               temp_pl->col.e[2]);
	       temp_pl = temp_pl->next;
	       i++;
	}
	i = 0;
	while (temp_cyl)
	{
		 printf("Cylinder %d: center %.2f, %.2f, %.2f, direction %.2f, %.2f, %.2f, diameter %.2f, height %.2f, color %.2f, %.2f, %.2f\n",
               i,
               temp_cyl->center.e[0],
               temp_cyl->center.e[1],
               temp_cyl->center.e[2],
               temp_cyl->dir.e[0],
               temp_cyl->dir.e[1],
               temp_cyl->dir.e[2],
               temp_cyl->diameter,
               temp_cyl->height,
               temp_cyl->col.e[0],
               temp_cyl->col.e[1],
               temp_cyl->col.e[2]);
	       temp_cyl = temp_cyl->next;
	       i++;
	}
}

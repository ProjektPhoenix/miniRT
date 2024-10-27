/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Henriette <Henriette@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 13:02:42 by hzimmerm          #+#    #+#             */
/*   Updated: 2024/10/27 18:25:46 by Henriette        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/vector_setup.h"
#include "../../includes/miniRT.h"
#include "../libft/libft.h"

int	parse_file(char *file, t_scene *scene)
{
	int	fd;
	char *line;

	init_scene(file, scene);
	fd = open(file, O_RDONLY);
	if (fd == -1)
		return (perror("Error opening file"), 1);
	line = get_next_line_new(fd);
	while (line)
	{
		if (line[0] != '\n')
			process_line(line, scene);
		free(line);
		line = get_next_line_new(fd);
	}
	close(fd);
	if (!scene->flag_A || !scene->flag_C || !scene->flag_L || !scene->flag_sp || !scene->flag_pl || !scene->flag_cy)
		cleanup_exit(scene, "Error\nFile does not contain all the elements\n");
	print_file_testing(scene);
	return (0);
}

void	process_line(char *line, t_scene *scene)
{
	char **line_elmts;

	line_elmts = ft_split(line, ' ');
	if (!line_elmts)
	{
		free(line);
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

void	process_a(char **array, t_scene *scene)
{
	char **color;

	scene->flag_A = true;
	if (!array[1])
		cleanup_exit(scene, "Error\nAmbient light is missing features");
	scene->ambient.intensity = ft_atod(array[1]);
	if (!array[2])
		cleanup_exit(scene, "Error\nAmbient light is missing colors");
	color = ft_split(array[2], ',');
	if (!color)
	{
		free_array(array);
		cleanup_exit(scene, "Error in splitting ambient light colors\n");
	}
	set_triple_from_array(&scene->ambient.col, color);
}

void	print_file_testing(t_scene *scene)
{
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
	int	i = 0;
	while (i < scene->i)
	{
		printf("Sphere %d: center %.2f, %.2f, %.2f, diameter %.2f, color %.2f, %.2f, %.2f\n",
               i,
               scene->sphere[i].center.e[0],
               scene->sphere[i].center.e[1],
               scene->sphere[i].center.e[2],
               scene->sphere[i].diameter,
               scene->sphere[i].col.e[0],
               scene->sphere[i].col.e[1],
               scene->sphere[i].col.e[2]);
		i++;
	}
	int j = 0;
	while (i < scene->j)
	{
		printf("Plane %d: position %.2f, %.2f, %.2f, normal %.2f, %.2f, %.2f, color %.2f, %.2f, %.2f\n",
               j,
               scene->plane[j].pos.e[0],
               scene->plane[j].pos.e[1],
               scene->plane[j].pos.e[2],
               scene->plane[j].dir.e[0],
               scene->plane[j].dir.e[1],
               scene->plane[j].dir.e[2],
               scene->plane[j].col.e[0],
               scene->plane[j].col.e[1],
               scene->plane[j].col.e[2]);
	       j++;
	}
	int k = 0;
	while (k < scene->k)
	{
		 printf("Cylinder %d: center %.2f, %.2f, %.2f, direction %.2f, %.2f, %.2f, diameter %.2f, height %.2f, color %.2f, %.2f, %.2f\n",
               k,
               scene->cyl[k].center.e[0],
               scene->cyl[k].center.e[1],
               scene->cyl[k].center.e[2],
               scene->cyl[k].dir.e[0],
               scene->cyl[k].dir.e[1],
               scene->cyl[k].dir.e[2],
               scene->cyl[k].diameter,
               scene->cyl[k].height,
               scene->cyl[k].col.e[0],
               scene->cyl[k].col.e[1],
               scene->cyl[k].col.e[2]);
	       k++;
	}
}

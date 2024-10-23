/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hzimmerm <hzimmerm@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 13:26:08 by hzimmerm          #+#    #+#             */
/*   Updated: 2024/10/23 14:58:05 by hzimmerm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/vector_setup.h"
#include "../../includes/miniRT.h"
#include "../libft/libft.h"

void	init_scene(char *file, t_scene *scene)
{
	int	count;
	int	i;

	i = 0;
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
	count = count_lines(file);
	scene->plane = malloc(count * sizeof(t_plane));
	scene->cyl = malloc(count * sizeof(t_cylinder));
	scene->sphere = malloc(count * sizeof(t_sphere));
	if (!scene->plane || !scene->cyl || !scene->sphere)
   		error_exit("Failed to allocate memory");
	while (i < count)
	{
		scene->plane[i] = (t_plane){0};
		scene->cyl[i] = (t_cylinder){0};
        	scene->sphere[i] = (t_sphere){0};
		i++;
	}
	scene->i = 0;
	scene->j = 0;
	scene->k = 0;
}

int	count_lines(char *file)
{
	int	count;
	int	fd;
	char	*line;

	count = 0;
	fd = open(file, O_RDONLY);
	if (fd == -1)
		return (perror("Error opening file"), 1);
	line = get_next_line_new(fd);
	while (line)
	{
		if (line[0] != '\n')
			count++;
		free(line);
		line = get_next_line_new(fd);
	}
	close(fd);
	if (count < 6)
		error_exit("Error\nNot enough elements\n");
	return (count - 4);
}

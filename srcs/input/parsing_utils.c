/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hzimmerm <hzimmerm@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 13:26:08 by hzimmerm          #+#    #+#             */
/*   Updated: 2024/10/30 17:47:44 by hzimmerm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//#include "../../includes/vector_setup.h"
#include "../../includes/miniRT.h"
#include "../libft/libft.h"
#include "../../includes/scene.h"

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
}

int	is_valid(char *str, t_scene *scene)
{
	if (ft_strncmp(str, "A", 2) && ft_strncmp(str, "C", 2) && ft_strncmp(str, "L", 2)
		&& ft_strncmp(str, "sp", 3) && ft_strncmp(str, "pl", 3) && ft_strncmp(str, "cy", 3))
		cleanup_exit(scene, "Error\nValid elements only are: A, C, L, pl, sp and cy\n");
	else if ((!ft_strncmp(str, "A", 2) && scene->flag_A == true) || (!ft_strncmp(str, "C", 2) && scene->flag_C == true)
		|| (!ft_strncmp(str, "L", 2) && scene->flag_L == true))
		cleanup_exit(scene, "Error\nA, C and L can only be entered once\n");
	return (1);
}
void	check_alloc(t_scene *scene, char **coord, char **array, char *mssg)
{
	if (!coord)
	{
		free_array(array);
		cleanup_exit(scene, mssg);
	}
}
t_sphere	*add_sphere_node(t_scene *scene)
{
	t_sphere	*new;
	t_sphere	*temp;
	
	new = malloc(sizeof(t_sphere));
	if (!new)
		cleanup_exit(scene, "malloc error\n");
	new->center.e[0] = 0.0;
	new->center.e[1] = 0.0;
	new->center.e[2] = 0.0;
	new->col.e[0] = 0.0;
	new->col.e[1] = 0.0;
	new->col.e[2] = 0.0;
	new->diameter = 0.0;
	new->next = NULL;
	printf("test8\n");
	if (!scene->sphere)
	{
		printf("test9\n");
		scene->sphere = new;
		
	}
	else
	{
		temp = scene->sphere;
		while (temp->next)
			temp = temp->next;
		temp->next = new;
	}
	
	return (new);
}

t_cylinder	*add_cylinder_node(t_scene *scene)
{
	t_cylinder	*new;
	t_cylinder	*temp;
	
	new = malloc(sizeof(t_cylinder));
	if (!new)
		cleanup_exit(scene, "malloc error\n");
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

t_plane	*add_plane_node(t_scene *scene)
{
	t_plane	*new;
	t_plane	*temp;
	
	new = malloc(sizeof(t_plane));
	if (!new)
		cleanup_exit(scene, "malloc error\n");
	new->col.e[0] = 0.0;
	new->col.e[1] = 0.0;
	new->col.e[2] = 0.0;
	new->ortho.e[0] = 0.0;
	new->ortho.e[1] = 0.0;
	new->ortho.e[2] = 0.0;
	new->pos.e[0] = 0.0;
	new->pos.e[1] = 0.0;
	new->pos.e[2] = 0.0;
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

/*void	init_scene(char *file, t_scene *scene)
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
   		cleanup_exit(scene, "Failed to allocate memory");
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
	scene->flag_A = false;
	scene->flag_C = false;
	scene->flag_L = false;
	scene->flag_sp = false;
	scene->flag_pl = false;
	scene->flag_cy = false;
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
}*/

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hzimmerm <hzimmerm@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 13:02:42 by hzimmerm          #+#    #+#             */
/*   Updated: 2025/01/26 13:03:10 by hzimmerm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "libft.h"
#include "scene.h"
#include "error_utils.h"

/*
 * takes as arguments the name of the .rt file and the scene, 
 * prepares file for parsing
 */
int	parse_file(char *file, t_scene *scene)
{
	int				fd;
	char			*line;
	t_parse_flags	check;

	init_scene(scene, &check);
	fd = open(file, O_RDONLY);
	if (fd == -1)
		perror_exit("Error opening file");
	line = get_next_line_new(fd);
	while (line)
	{
		process_line(line, scene, &check);
		line = get_next_line_new(fd);
	}
	close(fd);
	if (make_error_check(scene, &check))
		cleanup_scene_exit(scene, NULL, 1);
	return (0);
}

/*
 * takes as input one line from the .rt file and the scene 
 * checks if starting element is valid
 */
static int	is_valid(char *str, t_scene *scene, t_parse_flags *check)
{
	if (ft_strncmp(str, "A", 2) && ft_strncmp(str, "C", 2) 
		&& ft_strncmp(str, "L", 2) && ft_strncmp(str, "sp", 3) 
		&& ft_strncmp(str, "pl", 3) && ft_strncmp(str, "cy", 3))
		cleanup_scene_exit(scene, "Error\nValid elements only are: \
			A, C, L, pl, sp and cy\n", 2);
	else if ((!ft_strncmp(str, "A", 2) && check->flag_a == true) 
		|| (!ft_strncmp(str, "C", 2) && check->flag_c == true)
		|| (!ft_strncmp(str, "L", 2) && check->flag_l == true))
		cleanup_scene_exit(scene, "Error\nA, C and L can only be \
			entered once\n", 2);
	return (1);
}

/*
 * takes as arguments one line of the .rt file and the scene struct - 
 * checks with the first elements of the line under which category 
 * it should be processed
 */
void	process_line(char *line, t_scene *scene, t_parse_flags *check)
{
	char			**line_elmts;

	if (line[0] == '\n')
		return (free(line));
	line_elmts = ft_split_space(line);
	free(line);
	line = NULL;
	if (!line_elmts)
		error_exit("Error: ft_split fail for line splitting\n");
	is_valid(line_elmts[0], scene, check);
	if (!ft_strncmp(line_elmts[0], "A", 2))
		process_a(line_elmts, scene, check);
	else if (!ft_strncmp(line_elmts[0], "C", 2))
		process_c(line_elmts, scene, check);
	else if (!ft_strncmp(line_elmts[0], "L", 2))
		process_l(line_elmts, scene, check);
	else if (!ft_strncmp(line_elmts[0], "sp", 3))
		process_sp(line_elmts, scene);
	else if (!ft_strncmp(line_elmts[0], "pl", 3))
		process_pl(line_elmts, scene);
	else if (!ft_strncmp(line_elmts[0], "cy", 3))
		process_cy(line_elmts, scene);
	free_array(line_elmts);
}

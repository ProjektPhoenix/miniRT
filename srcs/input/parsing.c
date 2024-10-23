/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hzimmerm <hzimmerm@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 13:02:42 by hzimmerm          #+#    #+#             */
/*   Updated: 2024/10/23 14:44:39 by hzimmerm         ###   ########.fr       */
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
	if (line[0] != '\n')
		process_line(line, scene);
	printf("%f\n", scene->ambient.intensity);
	free(line);
	//if (!line)
		//return (close(fd), 1);
	/*while (line)
	{
		if (line[0] != '\n')
			process_line(line, scene);
		printf("%d\n", scene->ambient->intensity);
		free(line);
		line = get_next_line_new(fd);
	}*/
	close(fd);
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
	scene->ambient.intensity = ft_atod(line_elmts[1]);
}

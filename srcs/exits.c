/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exits.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hzimmerm <hzimmerm@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 17:01:25 by hzimmerm          #+#    #+#             */
/*   Updated: 2024/10/30 17:48:33 by hzimmerm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "./libft/libft.h"
#include "../includes/vector_setup.h"
#include "../includes/scene.h"

int	error_return(char *mssg)
{
	ft_putstr_fd(mssg, 2);
	return (1);
}


int	error_exit(char *mssg)
{
	ft_putstr_fd(mssg, 2);
	exit(1);
}

void cleanup_exit(t_scene *scene, char *mssg, int status)
{
	if (scene->plane)
	{
		free(scene->plane);
		scene->plane = NULL;
	}
	if (scene->cyl)
	{
		free(scene->cyl);
		scene->cyl = NULL;
	}
	if (scene->sphere)
	{
		free(scene->sphere);
		scene->sphere = NULL;
	}
	if (mssg)
		error_exit(mssg);
	else
		exit(status);
}

void	free_array(char **str)
{
	int	i;

	i = 0;
	if (str == NULL)
		return ;
	while (str[i] != NULL)
	{
		free(str[i]);
		i++;
	}
	free(str);
	str = NULL;
}

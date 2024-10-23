/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exits.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hzimmerm <hzimmerm@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 17:01:25 by hzimmerm          #+#    #+#             */
/*   Updated: 2024/10/23 15:38:39 by hzimmerm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "./libft/libft.h"
#include "../includes/vector_setup.h"

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

void cleanup_exit(t_scene *scene, char *mssg)
{
	if (scene->plane)
		free(scene->plane);
	if (scene->cyl)
		free(scene->cyl);
	if (scene->sphere)
		free(scene->sphere);
	if (mssg)
		error_exit(mssg);
	else
		exit(1);
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

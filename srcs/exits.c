/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exits.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hzimmerm <hzimmerm@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 17:01:25 by hzimmerm          #+#    #+#             */
/*   Updated: 2024/10/23 14:58:46 by hzimmerm         ###   ########.fr       */
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

/*void cleanup_exit(t_scene *scene, char *mssg)
{
	if (scene->camera)
		free(scene->camera);
	if (scene->ambient)
		free(scene->ambient);
	
	error_exit(mssg);
}*/

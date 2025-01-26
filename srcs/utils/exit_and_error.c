/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_and_error.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hzimmerm <hzimmerm@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 17:01:25 by hzimmerm          #+#    #+#             */
/*   Updated: 2025/01/26 13:55:03 by hzimmerm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

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

int	perror_exit(char *mssg)
{
	perror(mssg);
	exit(1);
}

int	error_exit_status(char *mssg, int status)
{
	if (mssg)
	{
		ft_putstr_fd("Error\n", 2);
		ft_putstr_fd(mssg, 2);
	}
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

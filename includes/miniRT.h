/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Henriette <Henriette@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 16:39:54 by hzimmerm          #+#    #+#             */
/*   Updated: 2024/10/27 20:00:52 by Henriette        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <errno.h>
//#include <math.h>
#include <stdlib.h>
//#include "vector_setup.h"

typedef struct s_viewp
{
	int	height;
	int	width;
	t_color **pxl;
}	t_viewp;



/* utils */
int	error_return(char *mssg);
int	error_exit(char *mssg);
void	free_array(char **str);

#endif 

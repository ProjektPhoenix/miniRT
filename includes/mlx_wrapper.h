/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_wrapper.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hzimmerm <hzimmerm@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/27 21:11:09 by rpriess           #+#    #+#             */
/*   Updated: 2024/11/18 15:38:50 by hzimmerm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MLX_WRAPPER_H
# define MLX_WRAPPER_H

#include "minirt.h"

typedef struct	s_interface {
	void	*mlx;
	void	*win;
	int		height;
	int		width;
}	t_interface;

typedef struct	s_img {
	void	*ptr;
	void	*content;
	int		height;
	int		width;
	int		bpp;
	int		line;
	int		endian;
}	t_img;

#endif

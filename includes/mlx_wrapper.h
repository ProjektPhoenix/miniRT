/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_wrapper.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpriess <rpriess@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/27 21:11:09 by rpriess           #+#    #+#             */
/*   Updated: 2025/01/26 17:21:19 by rpriess          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MLX_WRAPPER_H
# define MLX_WRAPPER_H

# include "minirt.h"
# include <stdbool.h>

# define WIDTH_RES 1200
# define HEIGHT_RES 800
# define WIDTH_RATIO 0.8
# define HEIGHT_RATIO 0.8
# define RES_MANUAL false

typedef struct s_interface {
	void	*mlx;
	void	*win;
	int		height;
	int		width;
}	t_interface;

typedef struct s_img {
	void	*ptr;
	void	*content;
	int		height;
	int		width;
	int		bpp;
	int		line;
	int		endian;
}	t_img;

#endif

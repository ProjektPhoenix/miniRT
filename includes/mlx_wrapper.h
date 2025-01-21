/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_wrapper.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpriess <rpriess@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/27 21:11:09 by rpriess           #+#    #+#             */
/*   Updated: 2025/01/21 18:25:39 by rpriess          ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#ifndef MLX_WRAPPER_H
# define MLX_WRAPPER_H

# include "minirt.h"

# define WIDTH_RATIO 0.8
# define HEIGHT_RATIO 0.9

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

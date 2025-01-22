/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpriess <rpriess@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 19:31:23 by rpriess           #+#    #+#             */
/*   Updated: 2025/01/21 20:27:11 by rpriess          ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#ifndef MINIRT_H
# define MINIRT_H

# include <unistd.h>
# include <stdio.h>
# include <fcntl.h>
# include <errno.h>
# include <stdlib.h>
# include <stdbool.h>
# include "vector_setup.h"
# include "vector_math.h"
# include "mlx_wrapper.h"
# include "scene.h"

# define WIN_TITLE "miniRT"
# define TITLEBAR_HEIGHT 10;
# ifdef __APPLE__
#  define LINUX_FLAG false
# else
#  define LINUX_FLAG true
# endif

typedef struct s_pxl {
	int		a;
	int		b;
	t_color	color;
}	t_pxl;

typedef struct s_viewp
{
	double	height;
	double	width;
	t_point	upperleft;
	t_vec	uvec_w;
	t_vec	uvec_h;
	t_vec	delta_w;
	t_vec	delta_h;
	t_ray	**ray;
}	t_viewp;

typedef struct s_minirt
{
	t_interface	screen;
	t_scene		scene;
	t_viewp		vp;
	t_img		img;
}	t_minirt;

/* init */
int		ft_key_hook(int keycode, t_minirt *rt);
void	init_helper(t_minirt *rt);
bool	init_img(t_minirt *rt);
int		init_mlx_interface(t_minirt *rt);
void	init_viewport(t_minirt *rt);
void	minirt_init_loop(t_minirt *rt);

/* utils */
void	calculate_rays(t_minirt *rt);
void	draw_image(t_minirt *rt);
bool	draw_pixel(t_img *img, t_pxl *pxl);

/* cleanup, exit, error */
void	cleanup_exit(t_minirt *rt, char *mssg, int status);
void	cleanup_scene(t_scene *scene);
void	cleanup_scene_exit(t_scene *scene, char *mssg, int status);
void	free_array(char **str);
int		loop_cleanup(t_minirt *rt);

#endif 

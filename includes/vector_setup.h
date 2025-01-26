/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_setup.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpriess <rpriess@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 16:08:47 by hzimmerm          #+#    #+#             */
/*   Updated: 2025/01/26 14:52:05 by rpriess          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_SETUP_H
# define VECTOR_SETUP_H

# include "vector_math.h"
# include <stdbool.h>

typedef t_vec	t_point;
typedef t_vec	t_color;

typedef struct s_ray
{
	t_point	orig;
	t_vec	dir;
	double	dist;
}	t_ray;

typedef struct s_ambl
{
	double	intens;
	t_color	col;
}	t_ambl;

typedef struct s_camera
{
	t_point	pos;
	t_vec	dir;
	double	fov;
}	t_cam;

typedef struct s_light
{
	t_point	pos;
	double	intens;
	t_color	col;
}	t_light;

typedef struct s_plane
{
	t_point			pos;
	t_vec			ortho;
	t_color			col;
	int				id;
	struct s_plane	*next;
}	t_plane;

typedef struct s_sphere
{
	t_point			center;
	double			diameter;
	t_color			col;
	int				id;
	struct s_sphere	*next;
}	t_sphere;

typedef struct s_cyl_helper
{
	t_vec	cyl_dir_unit;
	t_point	cyl_base;
	t_point	cyl_top;
	t_point	ray_orig;
	t_vec	orig_to_base;
	t_vec	orig_to_top;
	t_vec	ray_dir_unit;
	t_vec	cross_ray_cyl;
	t_vec	normal_v;
	double	radius;
	double	discriminant;
	bool	cam_inside;
}	t_cyl_helper;

typedef struct s_cylinder
{
	t_point				center;
	t_vec				dir;
	double				diameter;
	double				height;
	t_color				col;
	int					id;
	t_cyl_helper		c;
	struct s_cylinder	*next;
}	t_cylinder;

/* set vector, color, point util */
t_point	create_triple(double x, double y, double z);
t_vec	get_normal_v_sph(t_vec hit_p, t_vec center);

/* find intersection points */
double	find_t_sphere(t_ray *ray, t_sphere *sphere);
double	find_t_cylinder(t_ray *ray, t_cylinder *cylinder);
double	find_t_plane(t_ray *ray, t_plane *plane);

#endif

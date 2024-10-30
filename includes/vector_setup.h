/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_setup.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hzimmerm <hzimmerm@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 17:19:57 by hzimmerm          #+#    #+#             */
/*   Updated: 2024/10/30 17:46:25 by hzimmerm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_SETUP_H
# define VECTOR_SETUP_H

typedef struct vec
{
	double e[3];
}	t_vec;

typedef t_vec t_point;
typedef t_vec t_color;

typedef struct s_ray
{
	t_point	orig;
	t_vec	dir;
}	t_ray;

typedef struct s_ambl
{
	double intensity;
	t_color col;
}	t_ambl;

typedef struct s_camera
{
	t_point	pos;
	t_vec	dir;
	double	fov;
} t_cam;

typedef struct s_light
{
	t_point	pos;
	double intensity;
	t_color col;
} t_light;

typedef struct s_plane
{
	t_point pos;
	t_vec ortho;
	t_color col;
	struct s_plane	*next;
} t_plane;

typedef struct s_sphere
{
	t_point	center;
	double	diameter;
	t_color col;
	struct s_sphere	*next;
}	t_sphere;

typedef struct s_cylinder
{
	t_point center;
	t_vec dir;
	double diameter;
	double height;
	t_color col;
	struct s_cylinder	*next;
} t_cylinder;


/* set vectors and triples */
void	set_triple_from_array(t_vec *triple, char **coord);


#endif

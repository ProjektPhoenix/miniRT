/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_setup.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hzimmerm <hzimmerm@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 17:19:57 by hzimmerm          #+#    #+#             */
/*   Updated: 2024/10/23 14:57:20 by hzimmerm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

typedef struct vec
{
	double e[3];
}	t_vec;

typedef t_vec t_point;
typedef t_vec t_color;

typedef struct ray
{
	t_point	orig;
	t_vec	dir;
}	t_ray;

typedef struct ambl
{
	double intensity;
	t_color col;
}	t_ambl;

typedef struct camera
{
	t_point	pos;
	t_ambl	dir;
	int	fov;
} t_cam;

typedef struct light
{
	t_point	pos;
	double intensity;
} t_light;

typedef struct plane
{
	t_point pos;
	t_vec dir;
	t_color col;
} t_plane;

typedef struct sphere
{
	t_point	center;
	double	radius;
	t_color col;
}	t_sphere;

typedef struct cylinder
{
	t_point base_pos;
	t_vec dir;
	double radius;
	double height;
	t_color col;
} t_cylinder;

typedef struct scene
{
	t_cam	camera;
	t_ambl	ambient;
	t_light	light;
	t_plane	*plane;
	t_cylinder	*cyl;
	t_sphere	*sphere;
	int	i;
	int	j;
	int	k;
	int	num_pl;
	int	num_cyl;
	int	num_sph;
} t_scene;

/* parsing */
int	parse_file(char *file, t_scene *scene);
void	init_scene(char *file, t_scene *scene);
void	process_line(char *line, t_scene *scene);
int	count_lines(char *file);


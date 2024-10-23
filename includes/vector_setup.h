/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_setup.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hzimmerm <hzimmerm@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 17:19:57 by hzimmerm          #+#    #+#             */
/*   Updated: 2024/10/23 17:43:42 by hzimmerm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>

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
	t_vec	dir;
	double	fov;
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
	double	diameter;
	t_color col;
}	t_sphere;

typedef struct cylinder
{
	t_point center;
	t_vec dir;
	double diameter;
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
	bool	flag_A;
	bool	flag_C;
	bool	flag_L;
	bool	flag_sp;
	bool	flag_pl;
	bool	flag_cy;
} t_scene;

/* parsing */
int	parse_file(char *file, t_scene *scene);
void	init_scene(char *file, t_scene *scene);
void	process_line(char *line, t_scene *scene);
int	count_lines(char *file);
int	is_valid(char *str, t_scene *scene);
void	process_a(char **array, t_scene *scene);
void	process_c(char **array, t_scene *scene);
void	process_l(char **array, t_scene *scene);
void	process_sp(char **array, t_scene *scene);
void	process_pl(char **array, t_scene *scene);
void	process_cy(char **array, t_scene *scene);

/* set vectors and triples */
void	set_triple_from_string(t_vec *triple, char **coord);

/* exits */
void cleanup_exit(t_scene *scene, char *mssg);

/* just for testing, delete later */
void	print_file_testing(t_scene *scene);

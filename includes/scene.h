/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hzimmerm <hzimmerm@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 15:43:05 by hzimmerm          #+#    #+#             */
/*   Updated: 2025/01/28 14:22:22 by hzimmerm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SCENE_H
# define SCENE_H

# include "vector_setup.h"
# include <stdbool.h>
# include <math.h>

# define SPHERE 1
# define CYL 2
# define PLANE 3
# define REFLECTIVITY 0.3

typedef struct s_scene
{
	t_cam		camera;
	t_ambl		amb;
	t_light		light;
	t_plane		*plane;
	t_cylinder	*cyl;
	t_sphere	*sphere;
	int			id_count;
	int			fd;
}	t_scene;

typedef struct s_parse_flags
{
	bool		flag_a;
	bool		flag_c;
	bool		flag_l;
}	t_parse_flags;

typedef struct s_closest
{
	double	distance;
	int		id;
	t_color	col;
	t_point	hit_point;
	t_vec	normal_v;
	int		type;
	t_point	center;
}	t_closest;

typedef struct s_col_mix
{
	t_color	final;
	t_color	norm_obj;
	t_color	norm_amb;
	double	diff_intens;
}	t_col_mix;

typedef struct s_spec_l
{
	double	shininess;
	t_vec	reflect_dir;
	t_vec	view_dir;
	double	intens;
}	t_spec_l;

/* parsing */
int			parse_file(char *file, t_scene *scene);
void		init_scene(t_scene *scene, t_parse_flags *check);
void		process_line(char *line, t_scene *scene, t_parse_flags *check);
void		set_triple_from_array(t_vec *triple, char **coord, 
				t_scene *scene, char **array);
char		**split_and_check(t_scene *scene, char *str, char **arr, char *msg);
int			contains_valid(char *str);
void		process_a(char **array, t_scene *scene, t_parse_flags *check);
void		process_c(char **array, t_scene *scene, t_parse_flags *check);
void		process_l(char **array, t_scene *scene, t_parse_flags *check);
void		process_sp(char **array, t_scene *scene);
void		process_pl(char **array, t_scene *scene);
void		process_cy(char **array, t_scene *scene);
t_sphere	*add_sphere_node(t_scene *scene);
t_cylinder	*add_cylinder_node(t_scene *scene);
t_plane		*add_plane_node(t_scene *scene);
int			make_error_check(t_scene *scene, t_parse_flags *check);
int			is_p_on_plane(t_scene *scene);

/* scene rendering */
t_color		get_ray_color(t_ray *ray, t_scene *scene);
t_color		calculate_obj_color(t_scene *scene, t_closest *obj);
void		find_closest(t_ray *ray, t_scene *scene, t_closest *obj);
bool		check_blocking_obj(t_ray *l_ray, t_scene *scene, t_closest *obj);
void		make_light_ray(t_ray *l_ray, t_scene *scene, t_closest *obj);

/* color calculations */
t_color		normalise_color(t_color col);
t_color		multiply_cols(t_color col1, t_color col2);
void		add_light(t_ray *l_ray, t_col_mix *mix, \
			t_scene *scene, t_closest *obj);
t_color		reflection_vector(t_vec *l_ray_dir, t_vec *normal);
t_color		specular_light(t_ray *l_ray, t_scene *scene, t_closest *obj);

#endif

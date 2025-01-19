#ifndef SCENE_H
# define SCENE_H

#include "vector_setup.h"
#include <stdbool.h>
#include <math.h>

#define SPHERE 1
#define CYL 2
#define PLANE 3

typedef struct s_scene
{
	t_cam	camera;
	t_ambl	amb;
	t_light	light;
	t_plane	*plane;
	t_cylinder	*cyl;
	t_sphere	*sphere;
	bool	flag_A;
	bool	flag_C;
	bool	flag_L;
	int	id_count;
} t_scene;

typedef struct s_closest
	{
		double distance;
		int	id;
		t_color	col;
		t_point	hit_point;
		t_vec	normal_v;
		int	type;
		t_point center;
} t_closest;

typedef struct s_col_mix
{
	t_color final;
	t_color norm_obj;
	t_color norm_amb;
	t_color norm_light;
	t_color amb_contr;
	double diff_intens;
	t_color diff_contr;
	double attenuation;
} t_col_mix;

typedef struct s_spec_l
{
	double reflectivity;
	double shininess;
	t_vec reflect_dir;
	t_vec view_dir;
	double 	intens;
} t_spec_l;

/* parsing */
int	parse_file(char *file, t_scene *scene);
void	init_scene(t_scene *scene);
void	process_line(char *line, t_scene *scene);
void	set_triple_from_array(t_vec *triple, char **coord, t_scene *scene);
//int	count_lines(char *file);
int	is_valid(char *str, t_scene *scene);
void	process_a(char **array, t_scene *scene);
void	process_c(char **array, t_scene *scene);
void	process_l(char **array, t_scene *scene);
void	process_sp(char **array, t_scene *scene);
void	process_pl(char **array, t_scene *scene);
void	process_cy(char **array, t_scene *scene);
t_sphere	*add_sphere_node(t_scene *scene);
t_cylinder	*add_cylinder_node(t_scene *scene);
t_plane	*add_plane_node(t_scene *scene);
void	check_alloc(t_scene *scene, char **coord, char **array, char *mssg);
int	make_error_check(t_scene *scene);

/* scene rendering */
t_color	get_ray_color(t_ray *ray, t_scene *scene);
void	find_closest(t_ray *ray, t_scene *scene, t_closest *obj);
t_color	calculate_obj_color(t_scene *scene, t_closest *obj);
//bool	check_blocking_objects(t_ray *l_ray, t_scene *scene, t_closest *obj);
bool	check_blocking_objects(t_ray *l_ray, t_scene *scene);
void	make_light_ray(t_ray *l_ray, t_scene *scene, t_closest *obj);

/* color calculations */
t_color normalise_color(t_color col);
void	add_light(t_ray *l_ray, t_col_mix *mix, t_scene *scene, t_closest *obj);
t_color reflection(t_vec *l_ray_dir, t_vec *normal);
t_color specular_light(t_ray *l_ray, t_scene *scene, t_closest *obj);

/* just for testing, delete later */
void	print_file_testing(t_scene *scene);

#endif

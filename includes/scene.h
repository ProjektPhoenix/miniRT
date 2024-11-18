#ifndef SCENE_H
# define SCENE_H

#include "vector_setup.h"
#include <stdbool.h>
#include <math.h>

typedef struct s_scene
{
	t_cam	camera;
	t_ambl	ambient;
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
		t_point	hit_point;
} t_closest;

/* parsing */
int	parse_file(char *file, t_scene *scene);
void	init_scene(t_scene *scene);
void	process_line(char *line, t_scene *scene);
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

void	find_closest(t_ray *ray, t_scene *scene, t_closest *obj);

/* just for testing, delete later */
void	print_file_testing(t_scene *scene);

#endif

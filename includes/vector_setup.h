#ifndef VECTOR_SETUP_H
# define VECTOR_SETUP_H

#include "vector_math.h"

typedef t_vec t_point;
typedef t_vec t_color;

typedef struct s_ray
{
	t_point	orig;
	t_vec	dir;
}	t_ray;

typedef struct s_ambl
{
	double intens;
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
	double intens;
	t_color col;
} t_light;

typedef struct s_plane
{
	t_point pos;
	t_vec ortho;
	t_color col;
	int	id;
	struct s_plane	*next;
} t_plane;

typedef struct s_sphere
{
	t_point	center;
	double	diameter;
	t_color col;
	int	id;
	struct s_sphere	*next;
}	t_sphere;

typedef struct s_cylinder
{
	t_point center;
	t_vec dir;
	double diameter;
	double height;
	t_color col;
	int	id;
	struct s_cylinder	*next;
}	t_cylinder;

typedef struct s_cyl_helper
{
	t_vec	cyl_dir_unit;
	t_point	cyl_base;
	t_vec	orig_to_base;
	t_vec	ray_dir_unit;
	t_vec	cross_ray_cyl;
	double	radius;
	double	discriminant;
}	t_cyl_helper;

/* set vectors and triples */
void	set_triple_from_array(t_vec *triple, char **coord);
t_point	create_triple(double x, double y, double z);
t_point	get_hit_point(t_ray *ray, double t);

double	find_t_sphere(t_ray *ray, t_sphere *sphere);
double	find_t_cylinder(t_ray *ray, t_cylinder *cylinder);
double	get_discriminant(t_ray *ray, t_sphere *sphere, double *c, double *a);

#endif

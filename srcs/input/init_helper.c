#include "minirt.h"
#include "debug.h"
#include <stdbool.h>

static bool	camera_inside_cylinder(t_cylinder *cyl)
{
	double	dist_along_axis;
	double	dist_along_base;

	dist_along_axis = dot_product(cyl->c.cyl_dir_unit, vec1_minus_vec2(cyl->c.cam_pos, cyl->c.cyl_base));
	dist_along_base = get_magnitude(vec1_minus_vec2(vec1_minus_vec2(cyl->c.cam_pos, cyl->c.cyl_base), scalar_mply_vector(dot_product(vec1_minus_vec2(cyl->c.cam_pos, cyl->c.cyl_base), cyl->c.cyl_dir_unit), cyl->c.cyl_dir_unit)));
	debug("distance of camera along cyl axis: %f", dist_along_axis);
	debug("distance of camera along cyl base: %f", dist_along_base);
	if (dist_along_axis > 0 && dist_along_axis < cyl->height && dist_along_base < cyl->c.radius)
		return (true);
	return (false);
}

static void init_cyl_helper(t_scene *scene)
{
    t_cylinder  *temp_cyl;

    temp_cyl = scene->cyl;
    while (temp_cyl)
    {
        temp_cyl->c.cyl_dir_unit = get_unit_vector(temp_cyl->dir);
        temp_cyl->c.cyl_base = vec1_minus_vec2(temp_cyl->center, scalar_mply_vector(temp_cyl->height / 2, temp_cyl->c.cyl_dir_unit));
        temp_cyl->c.cyl_top = add_vectors(temp_cyl->center, scalar_mply_vector(temp_cyl->height / 2, temp_cyl->c.cyl_dir_unit));
        temp_cyl->c.cam_pos = scene->camera.pos;
        temp_cyl->c.orig_to_base = vec1_minus_vec2(temp_cyl->c.cyl_base, scene->camera.pos);
        temp_cyl->c.orig_to_top = vec1_minus_vec2(temp_cyl->c.cyl_top, scene->camera.pos);
        temp_cyl->c.radius = temp_cyl->diameter / 2;
		temp_cyl->c.cam_inside = camera_inside_cylinder(temp_cyl);
	    debug("Cylinder direction unit vector: (%f,%f,%f)", temp_cyl->c.cyl_dir_unit.e[0], temp_cyl->c.cyl_dir_unit.e[1], temp_cyl->c.cyl_dir_unit.e[2]);
        debug("Cylinder base coordinates: (%f,%f,%f)", temp_cyl->c.cyl_base.e[0], temp_cyl->c.cyl_base.e[1], temp_cyl->c.cyl_base.e[2]);
    	debug("Vector origin to cylinder base: (%f,%f,%f)", temp_cyl->c.orig_to_base.e[0], temp_cyl->c.orig_to_base.e[1], temp_cyl->c.orig_to_base.e[2]);
	    debug("Cylinder radius: %f", temp_cyl->c.radius);
        temp_cyl = temp_cyl->next;
    }
}

void    init_helper(t_minirt *rt)
{
    init_cyl_helper(&(rt->scene));
}
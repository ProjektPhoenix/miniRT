#include "minirt.h"
#include "debug.h"

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

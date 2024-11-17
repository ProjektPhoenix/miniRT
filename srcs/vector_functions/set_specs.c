/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_specs.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hzimmerm <hzimmerm@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 17:35:44 by hzimmerm          #+#    #+#             */
/*   Updated: 2024/11/17 17:10:19 by hzimmerm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//#include "../../includes/vector_setup.h"
#include "../../includes/miniRT.h"
#include "../libft/libft.h"

void	set_triple_from_array(t_vec *triple, char **coord)
{
	triple->e[0] = ft_atod(coord[0]);
	triple->e[1] = ft_atod(coord[1]);
	triple->e[2] = ft_atod(coord[2]);
	free_array(coord);
	coord = NULL;
}

t_point	create_point(double x, double y, double z)
{
	t_point p;

	p.e[0] = x;
	p.e[1] = y;
	p.e[2] = z;
	return p;
}

/* The position of the hit point, P(t), is calculated using the ray equation: P(t)=O+t⋅D
O: Origin of the ray, ray.orig (a 3D vector).
D: Direction of the ray, ray.dir (a normalized 3D vector).
t: Scalar value representing the distance along the ray to the hit point. */
t_point	get_hit_point(t_ray ray, double t)
{
	t_vec	scaled_dir;
	t_point	hit_point;

	scaled_dir = scalar_mply_vector(t, ray.dir);
	hit_point = add_vectors(ray.orig, scaled_dir);
	return (hit_point);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpriess <rpriess@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 16:30:37 by rpriess           #+#    #+#             */
/*   Updated: 2024/12/09 16:30:46 by rpriess          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "vector_setup.h"
#include <math.h>


static double	get_t_cyl_curve(t_ray *ray, t_cylinder *cylinder)
{
	
}

/* takes as input a ray and a cylinder, 
 *	- returns -1 if no intersection has been found
 *	- returns 0 if camera is inside object or exactly on the surface 
 *	- otherwise returns t for closest hitpoint.
 */
double	find_t_cylinder(t_ray *ray, t_cylinder *cylinder)
{
	double	t;
	double	temp;

	t = -1;
	temp = -1;
	//get closest intersection from curved cylinder surface and save in temp
	//save temp to t
	//get intersection from bottom lid and save in temp
	//save temp to t if smaller than t and > 0
	//get intersection from top lid and save in temp
	//save temp to t if smaller than t and > 0

	return (t);
}

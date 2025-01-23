/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hitpoint_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpriess <rpriess@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 18:45:31 by rpriess           #+#    #+#             */
/*   Updated: 2025/01/23 22:38:10 by rpriess          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector_math.h"

t_vec	get_normal_v_sph(t_vec hit_p, t_vec center)
{
	t_vec	normal;

	normal = vec1_minus_vec2(hit_p, center);
	return (get_unit_vector(normal));
}

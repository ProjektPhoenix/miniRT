/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_math.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpriess <rpriess@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/17 15:13:45 by rpriess           #+#    #+#             */
/*   Updated: 2025/01/23 22:37:32 by rpriess          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector_math.h"
#include <stdarg.h>

/*
 * Returns the difference vector of two vectors / points.
 * Geometrically "vec_1 - vec_2" results in a vector going from
 * the tip of vector 2 to the tip of vector 1.
 * When subtracting points "P1 - P2", the resulting vector describes
 * a vector that would connect P2 with P1, i.e. P2 + new vector = P1
 */
t_vec	vec1_minus_vec2(t_vec vec_1, t_vec vec_2)
{
	t_vec	new_vec;

	new_vec.e[0] = vec_1.e[0] - vec_2.e[0];
	new_vec.e[1] = vec_1.e[1] - vec_2.e[1];
	new_vec.e[2] = vec_1.e[2] - vec_2.e[2];
	return (new_vec);
}

/*
 * Returns the sum of two vectors.
 */
t_vec	add_vectors(t_vec vec_1, t_vec vec_2)
{
	t_vec	new_vec;

	new_vec.e[0] = vec_1.e[0] + vec_2.e[0];
	new_vec.e[1] = vec_1.e[1] + vec_2.e[1];
	new_vec.e[2] = vec_1.e[2] + vec_2.e[2];
	return (new_vec);
}

/*
 * Returns the sum of multiple vectors.
 * Number of vectors to add is specified in the first parameter.
 * Vectors are given as further parameters with format t_vec.
 */
t_vec	add_multiple_vectors(int num_vectors, ...)
{
	va_list	args;
	t_vec	new_vec;
	t_vec	temp_vec;

	new_vec.e[0] = 0.0;
	new_vec.e[1] = 0.0;
	new_vec.e[2] = 0.0;
	va_start(args, num_vectors);
	while (num_vectors > 0)
	{
		temp_vec = va_arg(args, t_vec);
		new_vec.e[0] = new_vec.e[0] + temp_vec.e[0];
		new_vec.e[1] = new_vec.e[1] + temp_vec.e[1];
		new_vec.e[2] = new_vec.e[2] + temp_vec.e[2];
		num_vectors--;
	}
	va_end(args);
	return (new_vec);
}

/*
 * Returns new vector from multiplying a number / scalar with a vector.
 * scalars > 1 increase the length, scalars < 1 and > 0 decrease the length.
 * scalars < -1 increase length and change direction.
 * scalars < 0 and > -1 decrease length and change direction.
 */
t_vec	scalar_mply_vector(double scalar, t_vec vec)
{
	t_vec	new_vec;

	new_vec.e[0] = vec.e[0] * scalar;
	new_vec.e[1] = vec.e[1] * scalar;
	new_vec.e[2] = vec.e[2] * scalar;
	return (new_vec);
}

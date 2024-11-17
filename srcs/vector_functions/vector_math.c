/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_math.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hzimmerm <hzimmerm@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/17 15:13:45 by rpriess           #+#    #+#             */
/*   Updated: 2024/11/17 17:57:11 by hzimmerm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector_math.h"
#include <math.h>

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
 * Returns new vector from multiplying a number / scalar with a vector.
 * The resulting vector has the same or opposite direction with scaled length.
 * scalars > 1 increase the length, scalars < 1 and > 0 decrease the length.
 * scalars < -1 increase length and change direction.
 *scalars < 0 and > -1 decrease length and change direction.
 */
t_vec	scalar_mply_vector(double scalar, t_vec vec)
{
	t_vec	new_vec;

	new_vec.e[0] = vec.e[0] * scalar;
	new_vec.e[1] = vec.e[1] * scalar;
	new_vec.e[2] = vec.e[2] * scalar;
	return (new_vec);
}

/*
 * Returns the length / magnitude of a vector.
 */
double	get_magnitude(t_vec vec)
{
	double	magnitude;

	magnitude = sqrt(pow(vec.e[0], 2) + pow(vec.e[1], 2) + pow(vec.e[2], 2));
	return (magnitude);
}

/*
 * Returns a vector with the same direction as the input vector and length 1.
 */
t_vec	get_unit_vector(t_vec vec)
{
	double	magnitude;

	magnitude = get_magnitude(vec);

	return (scalar_mply_vector(1/magnitude, vec));
}

/*
 * Returns the dot product of a two vectors.
 * Geometrically the dot product describes the relation of lengths
 * and angle of two vectors. A dot product of 0 implies that the two
 * vectors are perpendicular to each other.
 */
double	dot_product(t_vec vec_1, t_vec vec_2)
{
	return (vec_1.e[0] * vec_2.e[0] + vec_1.e[1] * vec_2.e[1] + vec_1.e[2] * vec_2.e[2]);
}

/*
 * Returns the cross product "vec_1 x vec_2" of two vectors.
 * Geometrically the cross product is a vector that is perpendicular
 * to the two vectors, e.g. to calculate vector perpendicular to a
 * plane that is described through two vectors.
 * (vec_1 x vec_2) = -(vec_2 x vec_1), i.e. the order matters!
 */
t_vec	cross_product(t_vec vec_1, t_vec vec_2)
{
	t_vec	new_vec;

	new_vec.e[0] = vec_1.e[1] * vec_2.e[2] - vec_1.e[2] * vec_2.e[1];
	new_vec.e[1] = vec_1.e[0] * vec_2.e[2] - vec_1.e[2] * vec_2.e[0];
	new_vec.e[2] = vec_1.e[0] * vec_2.e[1] - vec_1.e[1] * vec_2.e[0];
	return (new_vec);
}

/*
// TEST_MAIN
#include <stdio.h>

int	main(void)
{
	t_vec	test_vec;
	t_vec	test_vec2;
	t_vec	test_vec3;
	t_vec	result_vec;
	double	scalar;
	double	result;

	scalar = 2.0;
	test_vec.e[0] = 1;
	test_vec.e[1] = 2;
	test_vec.e[2] = 3;
	test_vec2.e[0] = 3;
	test_vec2.e[1] = 2;
	test_vec2.e[2] = 1;
	test_vec3.e[0] = 0;
	test_vec3.e[1] = 7;
	test_vec3.e[2] = 0;
	printf("Input vector 1: <%f,%f,%f>\n", test_vec.e[0], test_vec.e[1], test_vec.e[2]);
	printf("Input vector 2: <%f,%f,%f>\n", test_vec2.e[0], test_vec2.e[1], test_vec2.e[2]);
	printf("Input vector 3: <%f,%f,%f>\n", test_vec3.e[0], test_vec3.e[1], test_vec3.e[2]);
	result = get_magnitude(test_vec);
	printf("Magnitude of input vector 1: %f\n", result);
	result_vec = scalar_mply_vector(scalar, test_vec);
	printf("Output vector after multiplying input vector 1 with %f: <%f,%f,%f>\n", scalar, result_vec.e[0], result_vec.e[1], result_vec.e[2]);
	result_vec = get_unit_vector(test_vec);
	printf("Unit vector of input vector 1: <%f,%f,%f>\n", result_vec.e[0], result_vec.e[1], result_vec.e[2]);
	result_vec = get_unit_vector(test_vec3);
	printf("Unit vector of input vector 3: <%f,%f,%f>\n", result_vec.e[0], result_vec.e[1], result_vec.e[2]);
	result = dot_product(test_vec, test_vec2);
	printf("Dot product of input vector 1 and input vector 2: %f\n", result);
	result_vec = add_vectors(test_vec, test_vec2);
	printf("Sum of input vectors: <%f,%f,%f>\n", result_vec.e[0], result_vec.e[1], result_vec.e[2]);
	result_vec = vec1_minus_vec2(test_vec, test_vec2);
	printf("Difference of input vectors (vector 1 minus vector 2): <%f,%f,%f>\n", result_vec.e[0], result_vec.e[1], result_vec.e[2]);
	result_vec = cross_product(test_vec, test_vec2);
	printf("Cross product of input vectors: <%f,%f,%f>\n", result_vec.e[0], result_vec.e[1], result_vec.e[2]);
	return (0);
}
*/

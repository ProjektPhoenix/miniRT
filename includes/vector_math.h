/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_math.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpriess <rpriess@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/17 15:02:09 by rpriess           #+#    #+#             */
/*   Updated: 2024/11/17 16:35:49 by rpriess          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_MATH_H
# define VECTOR_MATH_H

typedef struct	s_vec {
	double e[3];
}	t_vec;

t_vec	add_vectors(t_vec vec_1, t_vec vec_2);
t_vec	cross_product(t_vec vec_1, t_vec vec_2);
double	dot_product(t_vec vec_1, t_vec vec_2);
double	get_magnitude(t_vec vec);
t_vec	get_unit_vector(t_vec vec);
t_vec	scalar_mply_vector(double scalar, t_vec vec);
t_vec	vec1_minus_vec2(t_vec vec_1, t_vec vec_2);

#endif
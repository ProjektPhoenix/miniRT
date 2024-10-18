/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_setup.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hzimmerm <hzimmerm@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 17:19:57 by hzimmerm          #+#    #+#             */
/*   Updated: 2024/10/16 17:46:29 by hzimmerm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

typedef struct vec
{
	double e[3];
}	t_vec;

typedef t_vec point;
typedef t_vec color;

typedef struct ray
{
	point	orig;
	t_vec	dir;
}	t_ray;

typedef struct sphere
{
	point	center;
	double	radius;
}	t_sphere;


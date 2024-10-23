/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_specs.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hzimmerm <hzimmerm@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 17:35:44 by hzimmerm          #+#    #+#             */
/*   Updated: 2024/10/23 17:48:02 by hzimmerm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/vector_setup.h"
#include "../../includes/miniRT.h"
#include "../libft/libft.h"

void	set_triple_from_string(t_vec *triple, char **coord)
{
	triple->e[0] = ft_atod(coord[0]);
	triple->e[1] = ft_atod(coord[1]);
	triple->e[2] = ft_atod(coord[2]);
	free_array(coord);
}

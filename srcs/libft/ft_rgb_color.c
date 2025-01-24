/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_rgb_color.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpriess <rpriess@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 14:42:38 by Henriette         #+#    #+#             */
/*   Updated: 2025/01/24 18:10:46 by rpriess          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

unsigned int	ft_rgb_color(unsigned char red, unsigned char green, \
								unsigned char blue)
{
	return ((red << 16) | (green << 8) | blue);
}

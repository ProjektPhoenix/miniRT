/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_argb_color.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpriess <rpriess@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 10:31:10 by rpriess           #+#    #+#             */
/*   Updated: 2024/04/30 14:43:00 by rpriess          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
 * Returns unsigned int representation of individual rgb values and an alpha
 * channel given as individual arguments.
 */

unsigned int	ft_argb_color(unsigned char alpha, unsigned char red, \
					unsigned char green, unsigned char blue)
{
	unsigned int	rgb;

	rgb = (alpha << 24) | (red << 16) | (green << 8) | blue;
	return (rgb);
}

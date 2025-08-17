/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atod.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hzimmerm <hzimmerm@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 14:13:25 by hzimmerm          #+#    #+#             */
/*   Updated: 2025/01/26 19:49:33 by hzimmerm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

static double	add_decimal_places(const char *str, int i)
{
	double	decimal_place;
	double	decimal_component;

	decimal_place = 1.0;
	decimal_component = 0.0;
	while (str[i] >= '0' && str[i] <= '9')
	{
		decimal_place *= 0.1;
		decimal_component += (str[i] - '0') * decimal_place;
		i++;
	}
	return (decimal_component);
}

static int	is_space(char c)
{
	if (c == ' ' || c == '\t' || c == '\v' 
		|| c == '\f' || c == '\r')
		return (1);
	return (0);
}

double	ft_atod(const char *str)
{
	int		i;
	double	result;
	double	sign;

	i = 0;
	result = 0.0;
	sign = 1.0;
	while (is_space(str[i]))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = -1.0;
		i++;
	}
	while (str[i] != 0 && (str[i] >= '0' && str[i] <= '9'))
	{
		result = (result * 10.0) + str[i] - '0';
		i++;
	}
	if (str[i] == '.')
		result += add_decimal_places(str, i + 1);
	return (result * sign);
}

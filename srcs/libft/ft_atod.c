/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atod.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hzimmerm <hzimmerm@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 14:13:25 by hzimmerm          #+#    #+#             */
/*   Updated: 2024/10/23 14:20:43 by hzimmerm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

double	ft_atod(const char *str)
{
	int	i;
	double	result;
	double	sign;
	double decimal_place = 1.0;

	i = 0;
	result = 0.0;
	sign = 1.0;
	decimal_place = 1.0;
	while (str[i] == ' ' || str[i] == '\t' || str[i] == '\n' 
		|| str[i] == '\v' || str[i] == '\f' || str[i] == '\r')
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
	{
		
		i++;
		while (str[i] >= '0' && str[i] <= '9')
		{
			decimal_place *= 0.1;
			result += (str[i] - '0') * decimal_place;
			i++;
		}
	}
	return (result * sign);
}

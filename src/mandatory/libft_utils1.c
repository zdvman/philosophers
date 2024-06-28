/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_utils1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzuiev <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 17:04:59 by dzuiev            #+#    #+#             */
/*   Updated: 2024/06/27 18:49:24 by dzuiev           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philo.h"

static int	ft_convert_digits(const char *str, int i, int sign)
{
	int	result;

	result = 0;
	while (str[i] >= '0' && str[i] <= '9')
	{
		if (result > INT_MAX / 10
			|| (result == INT_MAX / 10 && (str[i] - '0') > INT_MAX % 10))
		{
			if (sign == 1)
				return (INT_MAX);
			else
				return (INT_MIN);
		}
		result = result * 10 + (str[i] - '0');
		i++;
	}
	return (result * sign);
}

int	ft_atoi(const char *str)
{
	int	result;
	int	sign;
	int	i;

	result = 0;
	sign = 1;
	i = 0;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == ' ')
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	result = ft_convert_digits(str, i, sign);
	return (result);
}

static uint64_t	ft_convert_digits_uint(const char *str, int i)
{
	uint64_t	result;
	int			digit;

	result = 0;
	while (str[i] >= '0' && str[i] <= '9')
	{
		digit = str[i] - '0';
		if (result > UINT64_MAX / 10
			|| (result == UINT64_MAX / 10 && (uint64_t)digit
				> UINT64_MAX % 10))
		{
			return (UINT64_MAX);
		}
		result = result * 10 + (str[i] - '0');
		i++;
	}
	return (result);
}

uint64_t	ft_atoull(const char *str)
{
	uint64_t	result;
	int			i;

	result = 0;
	i = 0;
	while (ft_isspace(str[i]))
		i++;
	if (str[i] == '+')
		i++;
	if (str[i] == '-')
		return (0);
	result = ft_convert_digits_uint(str, i);
	return (result);
}

int	ft_strcmp(const char *s1, const char *s2)
{
	while (*s1 && *s1 == *s2)
	{
		s1++;
		s2++;
	}
	return ((unsigned char)*s1 - (unsigned char)*s2);
}

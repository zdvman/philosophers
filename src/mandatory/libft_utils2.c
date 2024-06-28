/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzuiev <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 16:58:56 by dzuiev            #+#    #+#             */
/*   Updated: 2024/06/27 17:06:34 by dzuiev           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philo.h"

size_t	ft_strlen(const char *str)
{
	size_t	i;

	i = 0;
	if (str)
	{
		while (str[i] != '\0')
			i++;
	}
	return (i);
}

int	ft_isdigit(int character)
{
	return (character >= '0' && character <= '9');
}

int	ft_isspace(char c)
{
	if (c == '\n'
		|| c == '\t'
		|| c == '\v'
		|| c == '\f'
		|| c == '\r'
		|| c == ' ')
		return (1);
	return (0);
}

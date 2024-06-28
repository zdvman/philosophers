/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzuiev <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 13:33:07 by dzuiev            #+#    #+#             */
/*   Updated: 2024/06/27 17:07:18 by dzuiev           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philo.h"

int	nbr_is_not_int(char *str)
{
	int	nbr;
	int	i;

	if (!str)
		return (1);
	nbr = 0;
	i = 0;
	if (str[i] == '\0')
		return (1);
	while (ft_isdigit(str[i]) && str[i] != '\0')
	{
		if (nbr > INT_MAX / 10
			|| (nbr == INT_MAX / 10 && (str[i] - '0') > INT_MAX % 10))
		{
			return (1);
		}
		nbr = nbr * 10 + (str[i] - '0');
		i++;
	}
	if (str[i] != '\0')
		return (1);
	return (0);
}

// A helper function to handle the write call and check its return value
ssize_t	safe_write(int fd, const void *buf, size_t count)
{
	ssize_t	result;

	result = write(fd, buf, count);
	if (result == -1)
	{
		perror("write");
	}
	return (result);
}

int	usage_msg(char *prog_name)
{
	if (safe_write(STDERR_FILENO, RED_BOLD, ft_strlen(RED_BOLD)) == -1)
		return (1);
	write(STDERR_FILENO, "\nInvalid number of arguments!\n\n", 31);
	if (safe_write(STDERR_FILENO, CYAN_BOLD, ft_strlen(CYAN_BOLD)) == -1)
		return (1);
	write(STDERR_FILENO, "Usage: ./", 9);
	write(STDERR_FILENO, prog_name, ft_strlen(prog_name));
	write(STDERR_FILENO, " <number_of_philosophers>", 25);
	write(STDERR_FILENO, " <time_to_die>", 14);
	write(STDERR_FILENO, " <time_to_eat>", 14);
	write(STDERR_FILENO, " <time_to_sleep>", 16);
	if (safe_write(STDERR_FILENO, GREEN_BOLD, ft_strlen(GREEN_BOLD)) == -1)
		return (1);
	write(STDERR_FILENO, " (optional)[number_of_times_each", 32);
	write(STDERR_FILENO, "_philosopher_must_eat]\n\n", 24);
	if (safe_write(STDERR_FILENO, YELLOW_BOLD, ft_strlen(YELLOW_BOLD)) == -1)
		return (1);
	write(STDERR_FILENO, "Example: ./philo 5 800 200 200\n\n", 32);
	if (safe_write(STDERR_FILENO, RED_BOLD, ft_strlen(RED_BOLD)) == -1)
		return (1);
	write(STDERR_FILENO, "Simulation failed!\n\n", 20);
	if (safe_write(STDERR_FILENO, RESET, ft_strlen(RESET)) == -1)
		return (1);
	return (0);
}

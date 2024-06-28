/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation_arguments.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzuiev <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 15:36:35 by dzuiev            #+#    #+#             */
/*   Updated: 2024/06/20 15:36:35 by dzuiev           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philo.h"

static int	input_is_not_valid(char *argv)
{
	char	*str;

	if (!argv)
		return (1);
	str = argv;
	while (ft_isspace(*str))
		str++;
	if (*str == '-')
		return (1);
	if (*str == '+')
		str++;
	if (nbr_is_not_int(str))
		return (1);
	return (0);
}

static int	validate_philosophers(int argc, char **argv)
{
	if (ft_atoi(argv[argc]) <= 0 || input_is_not_valid(argv[argc]))
	{
		if (safe_write(STDERR_FILENO, RED_BOLD, ft_strlen(RED_BOLD)) == -1)
			return (1);
		write(STDERR_FILENO, "\nInvalid number of philosophers!\n\n", 34);
		if (safe_write(STDERR_FILENO, RESET, ft_strlen(RESET)) == -1)
			return (1);
		return (1);
	}
	return (0);
}

static int	validate_time(int argc, char **argv)
{
	if (ft_atoi(argv[argc]) <= 0 || input_is_not_valid(argv[argc]))
	{
		if (safe_write(STDERR_FILENO, RED_BOLD, ft_strlen(RED_BOLD)) == -1)
			return (1);
		write(STDERR_FILENO, "\nInvalid time", 13);
		if (argc == 2)
			write(STDERR_FILENO, " to die!\n\n", 10);
		else if (argc == 3)
			write(STDERR_FILENO, " to sleep!\n\n", 12);
		else if (argc == 4)
			write(STDERR_FILENO, " to eat!\n\n", 10);
		if (safe_write(STDERR_FILENO, RESET, ft_strlen(RESET)) == -1)
			return (1);
		return (1);
	}
	return (0);
}

static int	validate_number_of_meals(int argc, char **argv)
{
	if (ft_atoi(argv[argc]) < 0 || input_is_not_valid(argv[argc]))
	{
		if (safe_write(STDERR_FILENO, RED_BOLD, ft_strlen(RED_BOLD)) == -1)
			return (1);
		write(STDERR_FILENO, "\nInvalid number of meals!\n\n", 27);
		if (safe_write(STDERR_FILENO, RESET, ft_strlen(RESET)) == -1)
			return (1);
		return (1);
	}
	return (0);
}

int	agruments_is_not_valid(int argc, char **argv)
{
	int	check;

	check = 0;
	if (argc == 5)
	{
		check += validate_philosophers(1, argv);
		check += validate_time(2, argv);
		check += validate_time(3, argv);
		check += validate_time(4, argv);
		return (check);
	}
	else if (argc == 6)
	{
		check += validate_philosophers(1, argv);
		check += validate_time(2, argv);
		check += validate_time(3, argv);
		check += validate_time(4, argv);
		check += validate_number_of_meals(5, argv);
		return (check);
	}
	else
		usage_msg(argv[0]);
	return (1);
}

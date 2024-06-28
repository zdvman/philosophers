/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzuiev <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 09:15:48 by dzuiev            #+#    #+#             */
/*   Updated: 2024/03/19 09:15:48 by dzuiev           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philo.h"

uint64_t	get_current_time(void)
{
	struct timeval	tv;

	if (gettimeofday(&tv, NULL) == -1)
		write(2, "gettimeofday() error\n", 21);
	return ((uint64_t)tv.tv_sec * 1000 + (uint64_t)tv.tv_usec / 1000);
}

int	ft_usleep(size_t milliseconds)
{
	uint64_t	start;

	start = get_current_time();
	while ((get_current_time() - start) < milliseconds)
		usleep(100);
	return (0);
}

void	cleanup(t_params *params, t_philosopher *philosophers,
			int exit_status)
{
	int	i;

	i = -1;
	while (++i < params->number_of_philosophers)
		pthread_mutex_destroy(&params->forks[i].mutex);
	pthread_mutex_destroy(&params->print_lock);
	pthread_mutex_destroy(&params->simulation_lock);
	if (params->forks)
		free(params->forks);
	if (philosophers)
		free(philosophers);
	exit(exit_status);
}

int	wait_for_simulation_end(t_philosopher *philosopher, t_params *params)
{
	if (philosopher->finished_eating)
	{
		philosopher->last_meal_time = get_current_time();
		pthread_mutex_unlock(&params->simulation_lock);
		ft_usleep(100);
		return (1);
	}
	return (0);
}

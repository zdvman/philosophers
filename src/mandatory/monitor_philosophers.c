/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor_philosophers.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzuiev <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 17:10:06 by dzuiev            #+#    #+#             */
/*   Updated: 2024/06/28 15:27:07 by dzuiev           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philo.h"

void	*monitor_wrapper(void *arg)
{
	t_monitor_params	*monitor_params;

	monitor_params = (t_monitor_params *)arg;
	monitor_philosophers(monitor_params->philosophers, monitor_params->params);
	free(monitor_params);
	return (NULL);
}

static int	monitor_loop(t_philosopher *philosophers, t_params *params,
			int i, int *all_finished)
{
	uint64_t	current_time;

	current_time = get_current_time();
	pthread_mutex_lock(&params->simulation_lock);
	if (current_time - philosophers[i].last_meal_time
		> params->time_to_die)
	{
		pthread_mutex_unlock(&params->simulation_lock);
		print_action(&philosophers[i], "died");
		pthread_mutex_lock(&params->simulation_lock);
		params->simulation_running = 0;
		pthread_mutex_unlock(&params->simulation_lock);
		return (1);
	}
	if (params->number_of_times_each_philosopher_must_eat
		> 0 && !philosophers[i].finished_eating)
		*all_finished = 0;
	pthread_mutex_unlock(&params->simulation_lock);
	return (0);
}

void	monitor_philosophers(t_philosopher *philosophers, t_params *params)
{
	int	all_finished;
	int	i;

	while (params->simulation_running)
	{
		all_finished = 1;
		i = -1;
		while (++i < params->number_of_philosophers)
		{
			if (monitor_loop(philosophers, params, i, &all_finished))
				return ;
		}
		if (params->number_of_times_each_philosopher_must_eat
			> 0 && all_finished)
		{
			pthread_mutex_lock(&params->simulation_lock);
			params->simulation_running = 0;
			pthread_mutex_unlock(&params->simulation_lock);
			return ;
		}
		ft_usleep(1);
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzuiev <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 15:42:57 by dzuiev            #+#    #+#             */
/*   Updated: 2024/06/28 14:38:01 by dzuiev           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philo.h"

void	*philosopher_life(void *arg)
{
	t_philosopher	*philosopher;
	t_params		*params;

	philosopher = (t_philosopher *)arg;
	params = philosopher->params;
	if (philosopher->id % 2 == 0)
		ft_usleep(1);
	while (1)
	{
		pthread_mutex_lock(&params->simulation_lock);
		if (!params->simulation_running)
		{
			pthread_mutex_unlock(&params->simulation_lock);
			return (NULL);
		}
		if (wait_for_simulation_end(philosopher, params))
			continue ;
		pthread_mutex_unlock(&params->simulation_lock);
		think_philosopher(philosopher);
		eat(philosopher);
		sleep_philosopher(philosopher);
	}
	return (NULL);
}

void	create_philosopher_threads(t_philosopher *philosophers,
			t_params *params)
{
	int	i;

	i = -1;
	while (++i < params->number_of_philosophers)
		pthread_create(&philosophers[i].thread, NULL,
			philosopher_life, &philosophers[i]);
}

void	end_simulation(t_philosopher *philosophers, t_params *params)
{
	int	i;

	i = -1;
	while (++i < params->number_of_philosophers)
		pthread_join(philosophers[i].thread, NULL);
}

static void	one_philo_case(t_params *params)
{
	t_philosopher	philosopher;

	philosopher.id = 1;
	philosopher.last_meal_time = params->start_time;
	printf(WHITE_BOLD "%" PRIu64 "\t%d\t%s\n" RESET,
		get_current_time() - philosopher.last_meal_time,
		philosopher.id, "is thinking");
	printf(CYAN_BOLD "%" PRIu64 "\t%d\t%s\n" RESET,
		get_current_time() - philosopher.last_meal_time,
		philosopher.id, "has taken a fork");
	ft_usleep(params->time_to_die);
	printf(RED_BOLD "%" PRIu64 "\t%d\t%s\n" RESET,
		get_current_time() - philosopher.last_meal_time,
		philosopher.id, "died");
}

void	start_simulation(t_params *params)
{
	t_philosopher		*philosophers;
	t_monitor_params	*monitor_params;
	pthread_t			monitor_thread;

	if (params->number_of_philosophers == 1)
	{
		one_philo_case(params);
		cleanup(params, NULL, 0);
	}
	philosophers = init_philosophers(params);
	create_philosopher_threads(philosophers, params);
	monitor_params = malloc(sizeof(t_monitor_params));
	monitor_params->philosophers = philosophers;
	monitor_params->params = params;
	pthread_create(&monitor_thread, NULL, monitor_wrapper, monitor_params);
	end_simulation(philosophers, params);
	pthread_join(monitor_thread, NULL);
	cleanup(params, philosophers, 0);
}

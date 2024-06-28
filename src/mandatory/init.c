/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzuiev <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 16:27:41 by dzuiev            #+#    #+#             */
/*   Updated: 2024/06/05 16:27:41 by dzuiev           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philo.h"

void	init_params(t_params *params, int argc, char **argv)
{
	int	i;

	params->number_of_philosophers = atoi(argv[1]);
	params->time_to_die = ft_atoull(argv[2]);
	params->time_to_eat = ft_atoull(argv[3]);
	params->time_to_sleep = ft_atoull(argv[4]);
	if (argc == 6)
		params->number_of_times_each_philosopher_must_eat = atoi(argv[5]);
	else
		params->number_of_times_each_philosopher_must_eat = -1;
	params->simulation_running = 1;
	params->forks = malloc(sizeof(t_fork) * params->number_of_philosophers);
	if (!params->forks)
		cleanup(params, NULL, 1);
	i = -1;
	while (++i < params->number_of_philosophers)
		pthread_mutex_init(&params->forks[i].mutex, NULL);
	pthread_mutex_init(&params->print_lock, NULL);
	pthread_mutex_init(&params->simulation_lock, NULL);
	params->start_time = get_current_time();
}

t_philosopher	*init_philosophers(t_params *params)
{
	t_philosopher	*philosophers;
	int				i;

	philosophers = malloc(sizeof(t_philosopher)
			* params->number_of_philosophers);
	if (!philosophers)
		cleanup(params, philosophers, 1);
	i = -1;
	while (++i < params->number_of_philosophers)
	{
		philosophers[i].id = i + 1;
		philosophers[i].last_meal_time = get_current_time();
		philosophers[i].meals_eaten = 0;
		philosophers[i].params = params;
		philosophers[i].finished_eating = 0;
	}
	return (philosophers);
}

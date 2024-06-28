/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_actions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzuiev <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 14:10:33 by dzuiev            #+#    #+#             */
/*   Updated: 2024/06/24 14:10:33 by dzuiev           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philo.h"

static void	take_forks(t_philosopher *philosopher, t_params *params,
					int left_index, int right_index)
{
	if (left_index < right_index)
	{
		pthread_mutex_lock(&params->forks[left_index].mutex);
		print_action(philosopher, "has taken a fork");
		pthread_mutex_lock(&params->forks[right_index].mutex);
		print_action(philosopher, "has taken a fork");
	}
	else
	{
		pthread_mutex_lock(&params->forks[right_index].mutex);
		print_action(philosopher, "has taken a fork");
		pthread_mutex_lock(&params->forks[left_index].mutex);
		print_action(philosopher, "has taken a fork");
	}
}

void	eat(t_philosopher *philosopher)
{
	t_params	*params;
	int			left_index;
	int			right_index;

	params = philosopher->params;
	left_index = philosopher->id - 1;
	right_index = philosopher->id % params->number_of_philosophers;
	take_forks(philosopher, params, left_index, right_index);
	pthread_mutex_lock(&params->simulation_lock);
	philosopher->last_meal_time = get_current_time();
	pthread_mutex_unlock(&params->simulation_lock);
	print_action(philosopher, "is eating");
	ft_usleep(params->time_to_eat);
	pthread_mutex_lock(&params->simulation_lock);
	philosopher->meals_eaten++;
	if (params->number_of_times_each_philosopher_must_eat > 0
		&& philosopher->meals_eaten
		>= params->number_of_times_each_philosopher_must_eat)
		philosopher->finished_eating = 1;
	pthread_mutex_unlock(&params->simulation_lock);
	pthread_mutex_unlock(&params->forks[left_index].mutex);
	pthread_mutex_unlock(&params->forks[right_index].mutex);
}

void	sleep_philosopher(t_philosopher *philosopher)
{
	t_params	*params;

	params = philosopher->params;
	pthread_mutex_lock(&params->simulation_lock);
	if (!params->simulation_running
		|| philosopher->finished_eating == 1)
	{
		pthread_mutex_unlock(&params->simulation_lock);
		return ;
	}
	pthread_mutex_unlock(&params->simulation_lock);
	print_action(philosopher, "is sleeping");
	ft_usleep(params->time_to_sleep);
}

void	think_philosopher(t_philosopher *philosopher)
{
	t_params	*params;

	params = philosopher->params;
	pthread_mutex_lock(&params->simulation_lock);
	if (!params->simulation_running
		|| philosopher->finished_eating == 1)
	{
		pthread_mutex_unlock(&params->simulation_lock);
		return ;
	}
	pthread_mutex_unlock(&params->simulation_lock);
	print_action(philosopher, "is thinking");
}

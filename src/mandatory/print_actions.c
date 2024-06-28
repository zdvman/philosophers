/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_actions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzuiev <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 12:06:47 by dzuiev            #+#    #+#             */
/*   Updated: 2024/06/28 12:07:30 by dzuiev           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philo.h"

static void	print_current_action(char *action, t_philosopher *philosopher,
				t_params *params, uint64_t timestamp)
{
	pthread_mutex_lock(&params->print_lock);
	if (ft_strcmp(action, "died") == 0)
		printf(RED_BOLD "%" PRIu64 "\t%d\t%s\n" RESET,
			timestamp, philosopher->id, action);
	else if (ft_strcmp(action, "has taken a fork") == 0)
		printf(GREEN_BOLD "%" PRIu64 "\t%d\t%s\n" RESET,
			timestamp, philosopher->id, action);
	else if (ft_strcmp(action, "is eating") == 0)
		printf(CYAN_BOLD "%" PRIu64 "\t%d\t%s\n" RESET,
			timestamp, philosopher->id, action);
	else if (ft_strcmp(action, "is sleeping") == 0)
		printf(MAGENTA_BOLD "%" PRIu64 "\t%d\t%s\n" RESET,
			timestamp, philosopher->id, action);
	else if (ft_strcmp(action, "is thinking") == 0)
		printf(WHITE_BOLD "%" PRIu64 "\t%d\t%s\n" RESET,
			timestamp, philosopher->id, action);
	pthread_mutex_unlock(&params->print_lock);
}

void	print_action(t_philosopher *philosopher, char *action)
{
	uint64_t	timestamp;
	t_params	*params;

	params = philosopher->params;
	timestamp = get_current_time() - params->start_time;
	pthread_mutex_lock(&params->simulation_lock);
	if (params->simulation_running)
	{
		pthread_mutex_unlock(&params->simulation_lock);
		print_current_action(action, philosopher, params, timestamp);
	}
	else
		pthread_mutex_unlock(&params->simulation_lock);
}

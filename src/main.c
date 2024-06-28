/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzuiev <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 15:38:54 by dzuiev            #+#    #+#             */
/*   Updated: 2024/06/24 14:17:33 by dzuiev           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	main(int argc, char **argv)
{
	t_params	params;

	if (agruments_is_not_valid(argc, argv))
		exit(EXIT_FAILURE);
	init_params(&params, argc, argv);
	start_simulation(&params);
	return (0);
}

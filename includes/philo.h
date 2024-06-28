/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzuiev <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 15:42:12 by dzuiev            #+#    #+#             */
/*   Updated: 2024/06/05 15:42:12 by dzuiev           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <sys/time.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <stdbool.h>
# include <limits.h>
# include <errno.h>
# include <stdint.h>
# include <inttypes.h>
# include <stdatomic.h>

/* ************************************************************************** */
/*                                                                            */
/*                                                                            */
/*                                                                            */
/*                                                                            */
/* ************************************************************************** */

# define RESET		"\033[0m"
# define BOLD		"\033[1m"
# define BLACK		"\033[30m"
# define RED		"\033[31m"
# define GREEN		"\033[32m"
# define YELLOW		"\033[33m"
# define BLUE		"\033[34m"
# define MAGENTA	"\033[35m"
# define CYAN		"\033[36m"
# define WHITE		"\033[37m"
# define CYAN_BOLD "\033[36m\033[1m"
# define YELLOW_BOLD "\033[33m\033[1m"
# define RED_BOLD "\033[31m\033[1m"
# define GREEN_BOLD "\033[32m\033[1m"
# define WHITE_BOLD "\033[37m\033[1m"
# define MAGENTA_BOLD "\033[35m\033[1m"

typedef struct s_fork
{
	pthread_mutex_t		mutex;
	int					is_taken;
}			t_fork;

typedef struct s_params
{
	int				number_of_philosophers;
	uint64_t		time_to_die;
	uint64_t		time_to_eat;
	uint64_t		time_to_sleep;
	int				number_of_times_each_philosopher_must_eat;
	t_fork			*forks;
	pthread_mutex_t	print_lock;
	pthread_mutex_t	simulation_lock;
	int				simulation_running;
	uint64_t		start_time;
}			t_params;

typedef struct s_philosopher
{
	int				id;
	pthread_t		thread;
	uint64_t		last_meal_time;
	int				meals_eaten;
	t_params		*params;
	int				finished_eating;
}			t_philosopher;

typedef struct s_monitor_params
{
	t_philosopher	*philosophers;
	t_params		*params;
}			t_monitor_params;

// libft_utils1.c
uint64_t		ft_atoull(const char *str);
int				ft_strcmp(const char *s1, const char *s2);
int				ft_atoi(const char *str);

// libft_utils2.c
size_t			ft_strlen(const char *str);
int				ft_isdigit(int character);
int				ft_isspace(char c);

// utils.c
int				ft_usleep(size_t milliseconds);
void			cleanup(t_params *params, t_philosopher *philosophers,
					int exit_status);
uint64_t		get_current_time(void);
int				wait_for_simulation_end(t_philosopher *philosopher,
					t_params *params);

// validation_arguments.c
int				agruments_is_not_valid(int argc, char **argv);

// validation_util.c 
ssize_t			safe_write(int fd, const void *buf, size_t count);
int				usage_msg(char *prog_name);
int				nbr_is_not_int(char *str);
int				ft_isspace(char c);
int				ft_isdigit(int c);

// init.c
t_philosopher	*init_philosophers(t_params *params);
void			init_params(t_params *params, int argc, char **argv);

// simulation.c
void			start_simulation(t_params *params);
void			end_simulation(t_philosopher *philosophers,
					t_params *params);
void			create_philosopher_threads(t_philosopher *philosophers,
					t_params *params);
void			*philosopher_life(void *arg);
void			monitor_philosophers(t_philosopher *philosophers,
					t_params *params);

// print_actions.c
void			print_action(t_philosopher *philosopher, char *action);

// philo_actions.c
void			eat(t_philosopher *philosopher);
void			sleep_philosopher(t_philosopher *philosopher);
void			think_philosopher(t_philosopher *philosopher);

// monitor_philosophers.c
void			*monitor_wrapper(void *arg);
void			monitor_philosophers(t_philosopher *philosophers,
					t_params *params);

#endif

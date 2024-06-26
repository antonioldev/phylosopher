/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alimotta <alimotta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 14:31:46 by alimotta          #+#    #+#             */
/*   Updated: 2024/04/03 09:10:40 by alimotta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <stdint.h>
# include <sys/wait.h>
# include <unistd.h>
# include <stdbool.h>
# include <errno.h>
# include <string.h>
# include <pthread.h>
# include <sys/time.h>
# include <limits.h>

typedef struct s_arg	t_arg;

typedef struct s_fork
{
	int				fork_id;
	pthread_mutex_t	fork;
}			t_fork;

typedef struct s_philo
{
	int				id;
	int				meal_consumed;
	bool			is_full;
	long			last_meal;
	t_fork			*first_fork;
	t_fork			*second_fork;
	t_arg			*arg;
	pthread_mutex_t	philo_mutex;
	pthread_t		thread_id;
}				t_philo;

typedef struct s_arg
{
	long			num_philo;
	long			time_to_die;
	long			time_to_eat;
	long			time_to_sleep;
	long			time_to_think;
	long			time_to_wait;
	long			times_dinner;
	long			start;
	bool			end;
	bool			all_thread_ready;
	t_fork			*forks;
	t_philo			*philos;
	pthread_t		waiter;
	pthread_mutex_t	arg_mutex;
	pthread_mutex_t	write_mutex;
}				t_arg;

int		ft_initiate(t_arg *arg);
void	ft_simulation(t_arg *arg);
void	ft_clean(t_arg *arg);
void	ft_eat(t_philo *philo);
void	ft_sleep(t_philo *philo);
void	ft_think(t_philo *philo);
void	set_end_dinner(t_arg *arg);
void	ft_write_state(t_philo *philo, const char *str, long time);
void	ft_thread_suspension(long action);
void	set_all_threads_ready(t_arg *arg);
bool	all_threads_ready(t_arg *arg);
bool	end_dinner(t_arg *arg);
long	ft_get_time(void);
size_t	ft_strcmp(const char *s1, const char *s2);
#endif
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alimotta <alimotta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 07:59:57 by alimotta          #+#    #+#             */
/*   Updated: 2024/03/30 11:21:29 by alimotta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

/*This function suspend the calling action*/
void	ft_thread_suspension(t_philo *philo, long action)
{
	long long	time;
	long long	time_elapsed;

	time = ft_get_time();
	time_elapsed = ft_get_time();
	while (time_elapsed - time <= action)
	{
		usleep(1000);
		is_philo_dead(philo);
		time_elapsed = ft_get_time();
	}
}

/*This function write each status and terminate the program if a philo dies*/
void	ft_write_state(t_philo *philo, const char *str, long long time)
{
	sem_wait(philo->print);
	printf("%lli %3i %s\n", time, philo->id, str);
	sem_post(philo->print);
}

/*This function lock the forks for the philo before start eating.
Once the philo get access to the forks, it checks if time elapsed from 
last meal is greater than time to die*/
void	ft_eat(t_philo *philo)
{
	long long	time;

	sem_wait(philo->fork);
	ft_write_state(philo, "has taken a fork", ft_get_time());
	sem_wait(philo->fork);
	ft_write_state(philo, "has taken a fork", ft_get_time());
	time = ft_get_time();
	philo->last_meal = time;
	ft_write_state(philo, "is eating", time);
	ft_thread_suspension(philo, philo->time_to_eat);
	sem_post(philo->fork);
	sem_post(philo->fork);
	if (++philo->meal_consumed >= philo->times_dinner
		&& philo->times_dinner > -1)
		philo->is_full = true;
}

/*This function manage the sleeping time of each philo*/
void	ft_sleep(t_philo *philo)
{
	ft_write_state(philo, "is sleeping", ft_get_time());
	ft_thread_suspension(philo, philo->time_to_sleep);
}

/*This function manage the thinking time of each philo*/
void	ft_think(t_philo *philo)
{
	ft_write_state(philo, "is thinking", ft_get_time());
	if (philo->meal_consumed != 0 && philo->time_to_think > 0)
		ft_thread_suspension(philo, philo->time_to_think);
}

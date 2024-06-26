/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alimotta <alimotta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 07:59:57 by alimotta          #+#    #+#             */
/*   Updated: 2024/04/02 14:55:59 by alimotta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*This function write each status and terminate the program if a philo dies*/
void	ft_write_state(t_philo *philo, const char *str, long time)
{
	bool	end;

	end = end_dinner(philo->arg);
	if (!end)
	{
		pthread_mutex_lock(&philo->arg->write_mutex);
		printf("%li %3i %s\n", time, philo->id, str);
		pthread_mutex_unlock(&philo->arg->write_mutex);
	}
}

/*This function lock the forks for the philo before start eating.
Once the philo get access to the forks, it checks if time elapsed from 
last meal is greater than time to die*/
void	ft_eat(t_philo *philo)
{
	long	time;
	bool	end;

	end = end_dinner(philo->arg);
	if (!end)
	{
		pthread_mutex_lock(&philo->first_fork->fork);
		ft_write_state(philo, "has taken a fork", ft_get_time());
		pthread_mutex_lock(&philo->second_fork->fork);
		ft_write_state(philo, "has taken a fork", ft_get_time());
		time = ft_get_time();
		pthread_mutex_lock(&philo->philo_mutex);
		philo->last_meal = time;
		pthread_mutex_unlock(&philo->philo_mutex);
		philo->meal_consumed++;
		ft_write_state(philo, "is eating", philo->last_meal);
		ft_thread_suspension(philo->arg->time_to_eat);
		if (philo->meal_consumed == philo->arg->times_dinner)
			philo->is_full = true;
		pthread_mutex_unlock(&philo->first_fork->fork);
		pthread_mutex_unlock(&philo->second_fork->fork);
	}
}

/*This function manage the sleeping time of each philo*/
void	ft_sleep(t_philo *philo)
{
	long	time;
	bool	end;

	end = end_dinner(philo->arg);
	if (!end)
	{
		time = ft_get_time();
		ft_write_state(philo, "is sleeping", time);
		ft_thread_suspension(philo->arg->time_to_sleep);
	}
}

/*This function manage the thinking time of each philo*/
void	ft_think(t_philo *philo)
{
	long	time;
	bool	end;

	end = end_dinner(philo->arg);
	if (!end)
	{
		time = ft_get_time();
		ft_write_state(philo, "is thinking", time);
		ft_thread_suspension(philo->arg->time_to_think);
	}
}

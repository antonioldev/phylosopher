/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dinner.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alimotta <alimotta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 12:28:52 by alimotta          #+#    #+#             */
/*   Updated: 2024/03/30 11:21:26 by alimotta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static void	dinner_alone(t_philo *philo)
{
	philo->last_meal = ft_get_time();
	sem_wait(philo->fork);
	ft_write_state(philo, "has taken a fork", ft_get_time());
	while (1)
		is_philo_dead(philo);
}

/*This function creates the threads and lunch the simulation*/
void	ft_simulation(t_philo *philo)
{
	philo->last_meal = philo->start;
	if (philo->id % 2 == 0)
		usleep (800);
	if (philo->num_philo > 1)
	{
		while (1)
		{
			ft_think(philo);
			ft_eat(philo);
			ft_sleep(philo);
			if (philo->is_full)
				return ;
		}
	}
	else
	{
		dinner_alone(philo);
	}
}

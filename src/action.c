/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szhong <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 18:21:08 by szhong            #+#    #+#             */
/*   Updated: 2024/11/21 11:54:37 by szhong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "philo.h"

void	philo_sleep(t_philo *philo, long ms)
{
	long	start;

	start = get_time();
	while (get_time() - start < ms)
	{
		if (dead_loop(philo->table))
			return ;
		usleep(500);
	}
}

int	eat(t_philo *philo)
{
	if (dead_loop(philo->table))
		return (1);
	fork_distrib(philo, LOCK);
	if (dead_loop(philo->table))
	{
		release_forks(philo);
		return (1);
	}
	print_status(philo->table, philo->philo_id, "has taken a fork");
	print_status(philo->table, philo->philo_id, "has taken a fork");
	update_meal_status(philo);
	print_status(philo->table, philo->philo_id, "is eating");
	philo_sleep(philo, philo->table->time_to_eat);
	fork_distrib(philo, UNLOCK);
	return (0);
}

int	dream(t_philo *philo)
{
	if (dead_loop(philo->table))
		return (1);
	print_status(philo->table, philo->philo_id, "is sleeping");
	philo_sleep(philo, philo->table->time_to_sleep);
	return (0);
}

int	think(t_philo *philo)
{
	if (dead_loop(philo->table))
		return (1);
	print_status(philo->table, philo->philo_id, "is thinking");
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szhong <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 18:21:08 by szhong            #+#    #+#             */
/*   Updated: 2024/11/19 18:21:13 by szhong           ###   ########.fr       */
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
	if (philo->philo_id % 2 == 0)
	{
		mutex_helper(&philo->second_fork->fork, LOCK);
		mutex_helper(&philo->first_fork->fork, LOCK);
	}
	else
	{
		mutex_helper(&philo->first_fork->fork, LOCK);
		mutex_helper(&philo->second_fork->fork, LOCK);
	}
	if (dead_loop(philo->table))
	{
		mutex_helper(&philo->first_fork->fork, UNLOCK);
		mutex_helper(&philo->second_fork->fork, UNLOCK);
		return (1);
	}
	print_status(philo->table, philo->philo_id, "has taken a fork");
	print_status(philo->table, philo->philo_id, "has taken a fork");
	mutex_helper(&philo->table->end_dinning_mutex, LOCK);
	philo->last_meal_time = get_time();
	philo->meals_counter++;
	mutex_helper(&philo->table->end_dinning_mutex, UNLOCK);
	print_status(philo->table, philo->philo_id, "is eating");
	philo_sleep(philo, philo->table->time_to_eat);
	if (philo->philo_id % 2 == 0)
	{
		mutex_helper(&philo->first_fork->fork, UNLOCK);
		mutex_helper(&philo->second_fork->fork, UNLOCK);
	}
	else
	{
		mutex_helper(&philo->second_fork->fork, UNLOCK);
		mutex_helper(&philo->first_fork->fork, UNLOCK);
	}
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

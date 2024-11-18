/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_actions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szhong <szhong@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 21:20:31 by szhong            #+#    #+#             */
/*   Updated: 2024/11/16 21:22:11 by szhong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "philo.h"

static int	eat(t_philo *philo)
{
	if (dead_loop(philo->table))
		return (1);
	mutex_helper(&philo->first_fork->fork, LOCK);
	print_status(philo, get_time() - philo->table->start_dinning, \
			  philo->philo_id, "has taken a fork\n");
	mutex_helper(&philo->second_fork->fork, LOCK);
	print_status(philo, get_time() - philo->table->start_dinning, \
			  philo->philo_id, "has taken a fork\n");
	mutex_helper(&philo->table->meal_time_mutex, LOCK);
	philo->last_meal_time = get_time();
	mutex_helper(&philo->table->meal_time_mutex, UNLOCK);
	print_status(philo, get_time() - philo->table->start_dinning, \
			  philo->philo_id, "is eating\n");
	philo_sleep(philo, philo->table->time_to_eat);
	mutex_helper(&philo->table->meals_mutex, LOCK);
	philo->meals_counter++;
	mutex_helper(&philo->table->meals_mutex, UNLOCK);
	mutex_helper(&philo->second_fork->fork, UNLOCK);
	mutex_helper(&philo->first_fork->fork, UNLOCK);
	return (0);
}

static int	dream(t_philo *philo)
{
	if (dead_loop(philo->table))
		return (1);
	print_status(philo, get_time() - philo->table->start_dinning, \
			  philo->philo_id, " is sleeping\n");
	philo_sleep(philo, philo->table->time_to_sleep);
	return (0);
}

static int	think(t_philo *philo)
{
	if (dead_loop(philo->table))
		return (1);
	print_status(philo, get_time() - philo->table->start_dinning, \
			  philo->philo_id, " is thinking\n");
	return (0);
}

void	*philo_routine(void *pointer)
{
	t_philo	*philo;

	philo = (t_philo *)pointer;
	if (philo->philo_id % 2)
		usleep(500);
	while (!dead_loop(philo->table))
	{
		if (eat(philo))
			break ;
		if (dream(philo))
			break ;
		if (think(philo))
			break ;
		usleep(100);
	}
	return (NULL);
}

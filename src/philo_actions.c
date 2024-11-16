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
	printf("%ld %d has taken a fork\n", \
		get_time() - philo->table->start_dinning, philo->philo_id);
	mutex_helper(&philo->second_fork->fork, LOCK);
	printf("%ld %d has taken a fork\n", \
		get_time() - philo->table->start_dinning, philo->philo_id);
	mutex_helper(&philo->table->meal_time_mutex, LOCK);
	philo->last_meal_time = get_time();
	mutex_helper(&philo->table->meal_time_mutex, UNLOCK);
	printf("%ld %d is eating\n", \
		get_time() - philo->table->start_dinning, philo->philo_id);
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
	printf("%ld %d is sleeping\n", \
		get_time() - philo->table->start_dinning, philo->philo_id);
	philo_sleep(philo, philo->table->time_to_sleep);
	return (0);
}

static int	think(t_philo *philo)
{
	if (dead_loop(philo->table))
		return (1);
	printf("%ld %d is thinking\n", \
		get_time() - philo->table->start_dinning, philo->philo_id);
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

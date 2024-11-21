/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dinning.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szhong <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 12:35:05 by szhong            #+#    #+#             */
/*   Updated: 2024/09/13 17:02:51 by szhong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "philo.h"

int	dead_loop(t_table *table)
{
	int	result;

	mutex_helper(&table->end_dinning_mutex, LOCK);
	result = table->end_dinning;
	mutex_helper(&table->end_dinning_mutex, UNLOCK);
	return (result);
}

void	*philo_routine(void *pointer)
{
	t_philo	*philo;

	philo = (t_philo *)pointer;
	if (philo->philo_id % 2 == 0)
		usleep(1000);
	while (!dead_loop(philo->table))
	{
		if (eat(philo))
			break ;
		if (dream(philo))
			break ;
		if (think(philo))
			break ;
		usleep(500);
	}
	return (pointer);
}

void	dinning_start(t_table *table)
{
	pthread_t	observer;
	int			i;

	table->start_dinning = get_time();
	i = -1;
	while (++i < table->philo_nbr)
	{
		table->philos[i].last_meal_time = table->start_dinning;
		if (pthread_create(&table->philos[i].thread_id, NULL, &philo_routine,
				&table->philos[i]) != 0)
			destroy_all("Thread creation error", table);
	}
	usleep(100);
	if (pthread_create(&observer, NULL, &monitor, table) != 0)
		destroy_all("Thread creation error", table);
	i = -1;
	while (++i < table->philo_nbr)
		pthread_join(table->philos[i].thread_id, NULL);
	pthread_join(observer, NULL);
	return ;
}

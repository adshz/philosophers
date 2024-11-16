/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_monitor.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szhong <szhong@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 21:24:13 by szhong            #+#    #+#             */
/*   Updated: 2024/11/16 21:40:31 by szhong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "philo.h"

void	cleanup_threads(t_table *table, pthread_t observer, \
							int created_threads)
{
	int		i;

	mutex_helper(&table->end_dinning_mutex, LOCK);
	table->end_dinning = true;
	mutex_helper(&table->end_dinning_mutex, UNLOCK);
	usleep(1000);
	i = 0;
	while (i < created_threads)
	{
		pthread_join(table->philos[i].thread_id, NULL);
		i++;
	}
	if (observer)
		pthread_join(observer, NULL);
}

static int	check_philosopher_death(t_table *table, int i)
{
	long	current_time;
	long	last_meal;

	mutex_helper(&table->meal_time_mutex, LOCK);
	last_meal = table->philos[i].last_meal_time;
	mutex_helper(&table->meal_time_mutex, UNLOCK);
	current_time = get_time();
	if (current_time - last_meal > table->time_to_die)
	{
		mutex_helper(&table->end_dinning_mutex, LOCK);
		if (!table->end_dinning)
		{
			table->end_dinning = true;
			printf("%ld %d died\n", current_time - table->start_dinning, \
		table->philos[i].philo_id);
		}
		mutex_helper(&table->end_dinning_mutex, UNLOCK);
		return (1);
	}
	return (0);
}

static int	check_all_philosophers_full(t_table *table)
{
	int	i;

	if (table->num_meals_per_philo == -1)
		return (0);
	i = 0;
	while (i < table->philo_nbr)
	{
		mutex_helper(&table->meals_mutex, LOCK);
		if (table->philos[i].meals_counter < table->num_meals_per_philo)
		{
			mutex_helper(&table->meals_mutex, UNLOCK);
			return (0);
		}
		mutex_helper(&table->meals_mutex, UNLOCK);
		i++;
	}
	return (1);
}

int	dead_loop(t_table *table)
{
	int	result;

	mutex_helper(&table->end_dinning_mutex, LOCK);
	result = table->end_dinning;
	mutex_helper(&table->end_dinning_mutex, UNLOCK);
	return (result);
}

void	*monitor(void *arg)
{
	int		i;
	t_table	*table;

	table = (t_table *)arg;
	while (!dead_loop(table))
	{
		i = 0;
		while (i < table->philo_nbr)
		{
			if (check_philosopher_death(table, i))
				return (NULL);
			i++;
		}
		if (check_all_philosophers_full(table))
		{
			mutex_helper(&table->end_dinning_mutex, LOCK);
			table->end_dinning = true;
			printf("All philosophers have eaten enough. Simulation ending.\n");
			mutex_helper(&table->end_dinning_mutex, UNLOCK);
			return (NULL);
		}
		usleep(500);
	}
	return (NULL);
}

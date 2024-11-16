/* ************************************************************************** */
/*																			  */
/*														  :::	   ::::::::   */
/*	 dinning.c											:+:		 :+:	:+:   */
/*													  +:+ +:+		  +:+	  */
/*	 By: szhong <marvin@42.fr>						+#+  +:+	   +#+		  */
/*												  +#+#+#+#+#+	+#+			  */
/*	 Created: 2024/09/12 12:35:05 by szhong			   #+#	  #+#			  */
/*	 Updated: 2024/11/16 20:37:57 by szhong			  ###	########.fr		  */
/*																			  */
/* ************************************************************************** */
#include "philo.h"

void	philo_sleep(t_philo *philo, long ms)
{
	long	start;
	long	elapsed;

	start = get_time();
	while (!dead_loop(philo->table))
	{
		elapsed = get_time() - start;
		if (elapsed >= ms)
			return ;
		usleep(500);
	}
}

static int	create_monitor(t_table *table, pthread_t *observer)
{
	if (pthread_create(observer, NULL, &monitor, table) != 0)
	{
		destroy_all("Monitor thread creation failed", table);
		return (1);
	}
	return (0);
}

static int	init_philosopher(t_table *table, int i)
{
	table->philos[i].last_meal_time = table->start_dinning;
	if (pthread_create(&table->philos[i].thread_id, NULL, \
				&philo_routine, &table->philos[i]) != 0)
		return (1);
	return (0);
}

static int	create_philosophers(t_table *table, int *created)
{
	int	i;

	i = 0;
	while (i < table->philo_nbr)
	{
		if (init_philosopher(table, i))
			return (1);
		(*created)++;
		i++;
	}
	return (0);
}

void	dinning_start(t_table *table)
{
	pthread_t	observer;
	int			created_threads;

	table->start_dinning = get_time();
	created_threads = 0;
	if (create_philosophers(table, &created_threads))
	{
		cleanup_threads(table, 0, created_threads);
		destroy_all("Thread creation failed", table);
		return ;
	}
	if (create_monitor(table, &observer))
	{
		cleanup_threads(table, 0, created_threads);
		return ;
	}
	cleanup_threads(table, observer, created_threads);
}

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

static int	dead_loop(t_table *table)
{
	int	result;

	mutex_helper(&table->end_dinning_mutex, LOCK);
	result = table->end_dinning;
	mutex_helper(&table->end_dinning_mutex, UNLOCK);
	return (result);
}

static void	philo_sleep(t_philo *philo, long ms)
{
	long	start;

	start = get_time();
	while (get_time() - start < ms)
	{
		if (dead_loop(philo->table))
			return;
		usleep(500);
	}
}

static int	eat(t_philo *philo)
{
	printf("Philosopher %d trying to eat at %ld\n", philo->philo_id, get_time() - philo->table->start_dinning);
	if (dead_loop(philo->table))
		return (1);
	mutex_helper(&philo->first_fork->fork, LOCK);
	if (dead_loop(philo->table))
	{
		mutex_helper(&philo->first_fork->fork, UNLOCK);
		return (1);
	}
	printf("%ld %d has taken a fork\n", get_time() - philo->table->start_dinning, philo->philo_id);
	mutex_helper(&philo->second_fork->fork, LOCK);
	if (dead_loop(philo->table))
	{
		mutex_helper(&philo->first_fork->fork, UNLOCK);
		mutex_helper(&philo->second_fork->fork, UNLOCK);
		return (1);
	}
	printf("%ld %d has taken a fork\n", get_time() - philo->table->start_dinning, philo->philo_id);
	philo->last_meal_time = get_time();
	printf("%ld %d is eating\n", philo->last_meal_time - philo->table->start_dinning, philo->philo_id);
	philo_sleep(philo, philo->table->time_to_eat);
	philo->meals_counter++;
	mutex_helper(&philo->first_fork->fork, UNLOCK);
	mutex_helper(&philo->second_fork->fork, UNLOCK);
	return (0);
}

static int	dream(t_philo *philo)
{
	if (dead_loop(philo->table))
		return (1);
	printf("%ld %d is sleeping\n", get_time() - philo->table->start_dinning, philo->philo_id);
	philo_sleep(philo, philo->table->time_to_sleep);
	return (0);
}

static int	think(t_philo *philo)
{
	if (dead_loop(philo->table))
		return (1);
	printf("%ld %d is thinking\n", get_time() - philo->table->start_dinning, philo->philo_id);
	return (0);
}

void	*philo_routine(void *pointer)
{
	t_philo	*philo;

	philo = (t_philo *)pointer;
	printf("Philosopher %d starting at %ld\n", philo->philo_id, get_time() - philo->table->start_dinning);
	if (philo->philo_id % 2 == 0)
		usleep(15000);
	while (!dead_loop(philo->table))
	{
		if(eat(philo))
			break ;
		if (dream(philo))
			break ;
		usleep(philo->philo_id * 1000);
		if (think(philo))
			break ;
	}
	return (pointer);
}

static int	check_philosopher_death(t_table *table, int i)
{
	long	current_time;

	current_time = get_time();
	if (current_time - table->philos[i].last_meal_time > table->time_to_die)
	{
		mutex_helper(&table->end_dinning_mutex, LOCK);
		if (!table->end_dinning)
		{
			table->end_dinning = true;
			printf("%ld %d died\n", current_time - table->start_dinning, table->philos[i].philo_id);
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
		if (table->philos[i].meals_counter < table->num_meals_per_philo)
			return (0);
		i++;
	}
	return (1);
}

void	*monitor(void *arg)
{
	int		i;
	t_table *table;

	table = (t_table *)arg;
	printf("Monitor starting at %ld\n", get_time() - table->start_dinning);
	while (1)
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
			printf(M"All philosophers have eaten enough. Simulation ending.\n"DF);
			mutex_helper(&table->end_dinning_mutex, UNLOCK);
			return (NULL);
		}
		usleep(1000);
	}
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
	usleep(10000);
	if (pthread_create(&observer, NULL, &monitor, table) != 0)
		destroy_all("Thread creation error", table);
	i = -1;
	while (++i < table->philo_nbr)
		pthread_join(table->philos[i].thread_id, NULL);
	pthread_join(observer, NULL);
	return ;
}
//
//static void	*philosopher_routine(void *arg)
//{
//	t_philo	*philo;
//	bool	should_continue;
//
//	philo = (t_philo *)arg;
//	should_continue = true;
//	while (should_continue)
//	{
//		mutex_helper(&philo->table->end_dinning_mutex, LOCK);
//		should_continue = !philo->table->end_dinning;
//		mutex_helper(&philo->table->end_dinning_mutex, UNLOCK);
//		if (!should_continue)
//			break ;
//		//taking forks
//		mutex_helper(&philo->first_fork->fork, LOCK);
//		printf("%ld %d has taken a fork\n", \
//				get_time() - philo->table->start_dinning, philo->philo_id);
//		mutex_helper(&philo->second_fork->fork, LOCK);
//		printf("%ld %d has taken a fork\n", \
//				get_time() - philo->table->start_dinning, philo->philo_id);
//		// eat
//		mutex_helper(&philo->table->end_dinning_mutex, LOCK);
//		if (!philo->table->end_dinning)
//		{
//			philo->last_meal_time = get_time();
//			printf("%ld %d is eating\n", \
//					philo->last_meal_time - philo->table->start_dinning, \
//					philo->philo_id);
//			philo_sleep(philo, philo->table->time_to_eat);
//			philo->meals_counter++;
//		}
//		else
//			mutex_helper(&philo->table->end_dinning_mutex, UNLOCK);
//		// put down the fork
//		mutex_helper(&philo->first_fork->fork, UNLOCK);
//		mutex_helper(&philo->second_fork->fork, UNLOCK);
//		mutex_helper(&philo->table->end_dinning_mutex, LOCK);
//		should_continue = !philo->table->end_dinning;
//		mutex_helper(&philo->table->end_dinning_mutex, UNLOCK);
//		if (!should_continue)
//			break ;
//		printf("%ld %d is sleeping\n", get_time() - philo->table->start_dinning, \
//				philo->philo_id);
//		philo_sleep(philo, philo->table->time_to_sleep);
//		printf("%ld %d is thinking\n", get_time() - philo->table->start_dinning, \
//				philo->philo_id);
//	}
//	return (NULL);
//}
//
//static void	*monitor_routine(void *arg)
//{
//	int		i;
//	t_table *table;
//	long	current_time;
//	bool	all_full;
//
//	table = (t_table *)arg;
//	while (1)
//	{
//		i = -1;
//		all_full = (table->num_meals_per_philo != -1);
//		while (++i < table->philo_nbr)
//		{
//			current_time = get_time();
//			if (current_time - table->philos[i].last_meal_time > table->time_to_die)
//			{
//				mutex_helper(&table->end_dinning_mutex, LOCK);
//				table->end_dinning = true;
//				mutex_helper(&table->end_dinning_mutex, UNLOCK);
//				printf("%ld %d died\n", current_time, table->philos[i].philo_id);
//				return (NULL);
//			}
//			if (table->num_meals_per_philo != -1)
//			{
//				if (table->philos[i].meals_counter < table->num_meals_per_philo)
//					all_full = false;
//			}
//			if (all_full)
//			{
//				mutex_helper(&table->end_dinning_mutex, LOCK);
//				table->end_dinning = true;
//				mutex_helper(&table->end_dinning_mutex, UNLOCK);
//				printf("All philosophers have eaten enough. Simulation ending.\n");
//				return (NULL);
//			}
//			usleep(1000);
//		}
//	}
//	return (NULL);
//}
//
//void	dinning_start(t_table *table)
//{
//	int			i;
//	pthread_t	monitor;
//
//	table->start_dinning = get_time();
//	i = -1;
//	while (++i < table->philo_nbr)
//	{
//		table->philos[i].last_meal_time = table->start_dinning;
//		if (pthread_create(&table->philos[i].thread_id, NULL, \
//					philosopher_routine, &table->philos[i]) != 0)
//			error_handler("ERROR: Philosophers Thread Creation Failure");
//	}
//	if (pthread_create(&monitor, NULL, monitor_routine, table) != 0)
//		error_handler("ERROR: Monitor Thread Creation Failure");
//	i = -1;
//	while (++i < table->philo_nbr)
//		if (pthread_join(table->philos[i].thread_id, NULL) != 0)
//			error_handler("ERROR: Joining Philosophers Thread Failure");
//	if (pthread_join(monitor, NULL) != 0)
//		error_handler("ERROR: Joining Monitor thread Failure");
//}

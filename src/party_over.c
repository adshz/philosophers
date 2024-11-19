/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   party_over.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szhong <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 15:30:05 by szhong            #+#    #+#             */
/*   Updated: 2024/09/12 21:10:57 by szhong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "philo.h"

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
			print_status(table, table->philos[i].philo_id, "died");
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
	t_table	*table;

	table = (t_table *)arg;
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
			printf(M"All philosophers have eaten enough.\n"DF);
			mutex_helper(&table->end_dinning_mutex, UNLOCK);
			return (NULL);
		}
		usleep(1000);
	}
}

void	destroy_all(const char *str, t_table *table)
{
	int	i;

	i = -1;
	if (str)
		printf("%s\n", str);
	mutex_helper(&table->end_dinning_mutex, DESTORY);
	while (++i < table->philo_nbr)
		mutex_helper(&table->forks[i].fork, DESTORY);
	free(table->philos);
	free(table->forks);
	free(table);
	exit(EXIT_FAILURE);
}

void	dinning_end(t_table *table)
{
	int	i;

	i = -1;
	while (++i < table->philo_nbr)
		mutex_helper(&table->forks[i].fork, DESTORY);
	mutex_helper(&table->end_dinning_mutex, DESTORY);
	free(table->philos);
	free(table->forks);
	free(table);
	printf(G"Party is over.\n"DF);
}

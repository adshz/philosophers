/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szhong <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 20:45:41 by szhong            #+#    #+#             */
/*   Updated: 2024/09/13 14:41:12 by szhong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "philo.h"

static void	assign_forks(t_philo *philo, t_fork *forks, int philo_pos)
{
	int	philo_nbr;

	philo_nbr = philo->table->philo_nbr;
	philo->first_fork = &forks[(philo_pos + 1) % philo_nbr];
	philo->second_fork = &forks[philo_pos];
	if (philo->philo_id % 2)
	{
		philo->first_fork = &forks[philo_pos];
		philo->second_fork = &forks[(philo_pos + 1) % philo_nbr];
	}
	return ;
}

static void	philo_init(t_table *table)
{
	int		i;
	t_philo	*philo;

	i = -1;
	while (++i < table->philo_nbr)
	{
		philo = table->philos + i;
		philo->philo_id = i + 1;
		philo->all_full = false;
		philo->meals_counter = 0;
		philo->table = table;
		assign_forks(philo, table->forks, i);
	}
	return ;
}

void	init_data(t_table *table)
{
	int	i;

	i = -1;
	table->end_dinning = false;
	table->philos = malloc_helper(sizeof(t_table) * table->philo_nbr);
	table->forks = malloc_helper(sizeof(t_fork) * table->philo_nbr);
	mutex_helper(&table->end_dinning_mutex, INIT);
	mutex_helper(&table->print_mutex, INIT);
	mutex_helper(&table->meal_mutex, INIT);
	while (++i < table->philo_nbr)
	{
		mutex_helper(&table->forks[i].fork, INIT);
		table->forks[i].id_fork = i;
	}
	philo_init(table);
	return ;
}

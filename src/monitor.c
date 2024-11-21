/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szhong <szhong@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 14:24:04 by szhong            #+#    #+#             */
/*   Updated: 2024/11/21 14:24:51 by szhong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "philo.h"

int	announce_death(t_table *table, int philo_nbr)
{
	if (check_philosopher_death(table, philo_nbr))
	{
		mutex_helper(&table->end_dinning_mutex, LOCK);
		table->end_dinning = true;
		mutex_helper(&table->end_dinning_mutex, UNLOCK);
		print_status(table, philo_nbr + 1, "died");
		return (1);
	}
	return (0);
}

int	full_exit(t_table *table)
{
	if (check_all_philosophers_full(table))
	{
		mutex_helper(&table->end_dinning_mutex, LOCK);
		table->end_dinning = true;
		printf(M"All philosophers have eaten enough.\n"DF);
		mutex_helper(&table->end_dinning_mutex, UNLOCK);
		return (1);
	}
	return (0);
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
			if (announce_death(table, i) == 1)
				return (NULL);
			i++;
		}
		if (full_exit(table) == 1)
			return (NULL);
		usleep(100);
	}
}

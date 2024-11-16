/* ************************************************************************** */
/*																			  */
/*														  :::	   ::::::::   */
/*	 party_over.c										:+:		 :+:	:+:   */
/*													  +:+ +:+		  +:+	  */
/*	 By: szhong <marvin@42.fr>						+#+  +:+	   +#+		  */
/*												  +#+#+#+#+#+	+#+			  */
/*	 Created: 2024/09/12 15:30:05 by szhong			   #+#	  #+#			  */
/*	 Updated: 2024/09/12 21:10:57 by szhong			  ###	########.fr		  */
/*																			  */
/* ************************************************************************** */
#include "philo.h"

void	destroy_all(const char *str, t_table *table)
{
	int	i;

	if (str)
		printf("%s\n", str);
	if (!table)
		exit(EXIT_FAILURE);
	i = -1;
	if (table->forks)
	{
		while (++i < table->philo_nbr)
			mutex_helper(&table->forks[i].fork, DESTORY);
	}
	mutex_helper(&table->end_dinning_mutex, DESTORY);
	mutex_helper(&table->meal_time_mutex, DESTORY);
	mutex_helper(&table->meals_mutex, DESTORY);
	if (table->philos)
		free(table->philos);
	if (table->forks)
		free(table->forks);
	free(table);
	exit(EXIT_FAILURE);
}

void	dinning_end(t_table *table)
{
	int	i;

	if (!table)
		return ;
	mutex_helper(&table->end_dinning_mutex, LOCK);
	table->end_dinning = true;
	mutex_helper(&table->end_dinning_mutex, UNLOCK);
	i = -1;
	if (table->forks)
	{
		while (++i < table->philo_nbr)
			mutex_helper(&table->forks[i].fork, DESTORY);
	}
	mutex_helper(&table->end_dinning_mutex, DESTORY);
	mutex_helper(&table->meal_time_mutex, DESTORY);
	mutex_helper(&table->meals_mutex, DESTORY);
	if (table->philos)
		free(table->philos);
	if (table->forks)
		free(table->forks);
	free(table);
	printf(G"Party is over.\n"DF);
}

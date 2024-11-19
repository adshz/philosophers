/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szhong <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 17:17:15 by szhong            #+#    #+#             */
/*   Updated: 2024/09/12 21:21:10 by szhong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "philo.h"

void	print_status(t_table *table, int philo_id, char *status)
{
	long	current_time;

	current_time = 0;
	mutex_helper(&table->print_mutex, LOCK);
	if (!table->end_dinning)
	{
		current_time = get_time() - table->start_dinning;
		printf("%ld %d %s\n", current_time, philo_id, status);
	}
	mutex_helper(&table->print_mutex, UNLOCK);
}

void	handle_single_philosopher(t_table *table)
{
	printf("%ld 1 has taken a fork\n", 0L);
	usleep(table->time_to_die * 1000);
	printf("%ld 1 died\n", table->time_to_die);
}

int	main(int argc, char *argv[])
{
	t_table	*table;

	if (argc == 5 || argc == 6)
	{
		table = malloc_helper(sizeof(t_table));
		parse_data(table, argv);
		init_data(table);
		if (table->philo_nbr == 1)
			handle_single_philosopher(table);
		else
			dinning_start(table);
		dinning_end(table);
	}
	else
		error_handler("ERROR:Wrong Command Line Inputs\n"\
				Y"Usage:\t./philo [num_of_phliosophers] "\
				"[time_to_die] [time_to_eat] [time_to_sleep] "\
				"[OPTIONAL - num of meals per philosophers]"DF);
	return (0);
}

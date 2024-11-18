/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szhong <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 17:17:15 by szhong            #+#    #+#             */
/*   Updated: 2024/11/16 19:39:41 by szhong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "philo.h"

void	print_status(t_philo *philo, long time_diff, int id, const char *msg)
{
	mutex_helper(&philo->table->write_mutex, LOCK);
	if (!dead_loop(philo->table))
		printf("%ld %d %s\n", time_diff, id, msg);
	mutex_helper(&philo->table->write_mutex, UNLOCK);
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
		error_handler(R"ERROR:Wrong Command Line Inputs\n"\
				Y"Usage:\t./philo [num_of_phliosophers] "\
				"[time_to_die] [time_to_eat] [time_to_sleep] "\
				"[OPTIONAL - num of meals per philosophers]"DF);
	return (0);
}

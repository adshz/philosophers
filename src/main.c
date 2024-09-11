/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szhong <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 17:17:15 by szhong            #+#    #+#             */
/*   Updated: 2024/09/11 19:44:40 by szhong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "philo.h"

int	main(int argc, char *argv[])
{
	t_table	*table;

	if ( argc == 5 || argc == 6)
	{
		// 1. parse values
		table = malloc(sizeof(t_table));
		if (table == NULL)
			return (-1);
		parse_data(table, argv);
		// 2. initialisation
	//	init_data();
		// 3. dinner
	//	dinner_start();
		// 4. clean up // when a philosopher dies or all philosophers are full
	//	dinner_end();
	}
	else
		error_handler("ERROR:Wrong Command Line Inputs\n"\
				Y"Usage:\t./philo [num_of_phliosophers] "\
				"[time_to_die] [time_to_eat] [time_to_sleep] "\
				"[OPTIONAL - num of meals per philosophers]"DF);
}

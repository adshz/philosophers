/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szhong <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 18:57:36 by szhong            #+#    #+#             */
/*   Updated: 2024/09/11 19:43:47 by szhong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "philo.h"

static long	ft_atol(const char *str)
{
	long	num;
	int		sign;
	int		num_sign;

	num = 0;
	sign = 1;
	num_sign = 0;
	while ((*str > 8 && *str < 14) || (*str == 32))
		str++;
	while (*str == '-' || *str == '+')
	{
		if (*str == '-' || *str == '+')
			sign *= -1;
		str++;
		num_sign++;
	}
	if (num_sign > 1)
		return (0);
	while (*str >= '0' && *str <= '9')
	{
		num = (num * 10) + (*str - '0');
		str++;
	}
	return (num * sign);
}

void	parse_data(t_table *table, char *argv[])
{
	table->philo_nbr = ft_atol(argv[1]);
	table->time_to_die = ft_atol(argv[2]) * 1e3;
	table->time_to_eat = ft_atol(argv[3]) * 1e3;
	table->time_to_sleep = ft_atol(argv[4]) * 1e3;
	if (table->time_to_die < 6e4 ||\
			table->time_to_eat < 6e4 || table->time_to_eat < 6e4)
		error_handler("Time is longer than 60ms");
	// how do you deal with if there isn't anything in argv[5]?
	// my question is that there aren't any pointers to the argv[5]
	// so if we access `argv[5]` it will be memory segmentation fault
	// the reason why we need argv[5] is `num_meals_per_philos`
	//
	// after I watched the video, I can do if (argv[5]), if it has value
	// I forgot about this
	if (argv[5])
		table->num_meals_per_philo = ft_atol(argv[5]);
	else
		table->num_meals_per_philo	= -1;
}

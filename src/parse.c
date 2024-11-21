/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szhong <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 18:57:36 by szhong            #+#    #+#             */
/*   Updated: 2024/11/21 17:09:46 by szhong           ###   ########.fr       */
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
	table->time_to_die = ft_atol(argv[2]);
	table->time_to_eat = ft_atol(argv[3]);
	table->time_to_sleep = ft_atol(argv[4]);
	if (table->philo_nbr <= 0 || table->philo_nbr > 200)
	{
		free(table);
		error_handler("Invalid number of philosophers"\
				Y"\nRange of philosophers: 0 < x < 200\n"DF);
	}
	if (table->time_to_die < 60 || \
			table->time_to_eat < 60 || table->time_to_eat < 60)
	{
		free(table);
		error_handler("Time is longer than 60ms");
	}
	if (argv[5])
	{
		table->num_meals_per_philo = ft_atol(argv[5]);
		if (table->num_meals_per_philo <= 0)
			error_handler("Invalid number of meals"\
					Y"\nInput positive numbers\n"DF);
	}
	else
		table->num_meals_per_philo = -1;
}

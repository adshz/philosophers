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

void    destroy_all(const char *str, t_table *table)
{
    int i;

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

void dinning_end(t_table *table)
{
    int i;

    i = -1;
    while (++i < table->philo_nbr)
        mutex_helper(&table->forks[i].fork, DESTORY);
    mutex_helper(&table->end_dinning_mutex, DESTORY);
    free(table->philos);
    free(table->forks);
    free(table);
    printf(G"Party is over.\n"DF);
}


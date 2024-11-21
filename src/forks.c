/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szhong <szhong@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 11:51:37 by szhong            #+#    #+#             */
/*   Updated: 2024/11/21 11:52:58 by szhong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "philo.h"

void	pick_forks(t_philo *philo)
{
	if (philo->philo_id % 2 == 0)
	{
		mutex_helper(&philo->second_fork->fork, LOCK);
		mutex_helper(&philo->first_fork->fork, LOCK);
	}
	else
	{
		mutex_helper(&philo->first_fork->fork, LOCK);
		mutex_helper(&philo->second_fork->fork, LOCK);
	}
	return ;
}

// see ./init.c assign_forks
// when it is a even number, first fork is right fork
// when it is an odd number, first fork is left fork (their own forks)
void	release_forks(t_philo *philo)
{
	if (philo->philo_id % 2 == 0)
	{
		mutex_helper(&philo->first_fork->fork, UNLOCK);
		mutex_helper(&philo->second_fork->fork, UNLOCK);
	}
	else
	{
		mutex_helper(&philo->second_fork->fork, UNLOCK);
		mutex_helper(&philo->first_fork->fork, UNLOCK);
	}
	return ;	
}

void	fork_distrib(t_philo *philo, t_mutex_code code )
{
	if (code == LOCK)
		pick_forks(philo);
	else if (code == UNLOCK)
		release_forks(philo);
	return ;	
}

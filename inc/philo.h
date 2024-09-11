/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szhong <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 12:19:27 by szhong            #+#    #+#             */
/*   Updated: 2024/09/11 21:00:48 by szhong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef PHILO_H
# define PHILO_H
# include <pthread.h>
# include <stdio.h>
# include <sys/time.h>
# include <stdlib.h>
# include <stdbool.h>
# include <error.h>

# define DF "\033[0m" // Default colour
# define R  "\033[1;31m" // Bold red
# define G  "\033[1;32m" // Bold green
# define Y  "\033[1;33m" // Bold yellow
# define B  "\033[1;34m" // Bold blue
# define M  "\033[1;35m" // Bold magenta
# define C  "\033[1;36m" // Bold cyan
# define W  "\033[1;37m" // Bold white

typedef pthread_mutex_t	t_mutex;
typedef struct s_table	t_table;

typedef struct s_fork
{
	t_mutex	fork;
	int		id_fork;
}	t_fork;

typedef enum mutex_code
{
	LOCK,
	UNLOCK,
	INIT,
	DESTORY,
	CREATE,
	JOIN,
	DETACH
}	t_mutex_code;

typedef struct s_philo
{
	int			philo_id;
	pthread_t	thread_id;
	bool		all_full;
	long		last_meal_time;
	t_fork		*first_fork;
	t_fork		*second_fork;
	t_table		*table;
}	t_philo;

struct s_table
{
	long	philo_nbr;
	long	time_to_die;
	long	time_to_eat;
	long	time_to_sleep;
	long	start_dinning;
	bool	end_dinning;
	long	num_meals_per_philo;
	t_philo	*philos;
	t_fork	*forks;
};

// utils.c
void	error_handler(const char *error_msg);
void	parse_data(t_table *t, char *argv[]);
void	mutex_helper(t_mutex *mutex, t_mutex_code code);

#endif

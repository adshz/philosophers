/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szhong <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 12:19:27 by szhong            #+#    #+#             */
/*   Updated: 2024/11/21 14:26:06 by szhong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef PHILO_H
# define PHILO_H
# include <pthread.h>
# include <stdio.h>
# include <sys/time.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdbool.h>
# include <errno.h>

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
	int			meals_counter;
	int			philo_id;
	pthread_t	thread_id;
	bool		all_full;
	bool		is_eating;
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
	t_mutex	end_dinning_mutex;
	t_mutex	print_mutex;
	t_mutex	meal_mutex;
	t_philo	*philos;
	t_fork	*forks;
};

void	error_handler(const char *error_msg);
void	print_status(t_table *table, int philo_id, char *status);
int		dead_loop(t_table *table);
void	*monitor(void *arg);
void	init_data(t_table *table);
void	parse_data(t_table *t, char *argv[]);
void	*malloc_helper(size_t bytes);
void	mutex_helper(t_mutex *mutex, t_mutex_code code);
void	dinning_start(t_table *table);
void	update_meal_status(t_philo *philo, long start_eating_time);
void	fork_distrib(t_philo *philo, t_mutex_code code );
void	release_forks(t_philo *philo);
void	pick_forks(t_philo *philo);
long	get_time(void);
int		check_philosopher_death(t_table *table, int i);
int		check_all_philosophers_full(t_table *table);
int		announce_death(t_table *table, int philo_nbr);
int		full_exit(t_table *table);
int		think(t_philo *philo);
int		dream(t_philo *philo);
int		eat(t_philo *philo);
void	philo_sleep(t_philo *philo, long ms);
void	dinning_end(t_table *table);
void	destroy_all(const char *str, t_table *table);
#endif

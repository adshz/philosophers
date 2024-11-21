/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szhong <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 18:32:17 by szhong            #+#    #+#             */
/*   Updated: 2024/09/12 16:04:33 by szhong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "philo.h"

long	get_time(void)
{
	struct timeval	time_value;

	if (gettimeofday(&time_value, NULL) == -1)
		error_handler("ERROR: gettimeofday()");
	return (time_value.tv_sec * 1e3 + time_value.tv_usec / 1e3);
}

void	*malloc_helper(size_t bytes)
{
	void	*ptr;

	ptr = malloc(bytes);
	if (ptr == NULL)
		error_handler("ERROR: malloc failure");
	return (ptr);
}

static void	mutex_error_handler(int status, t_mutex_code code, t_mutex *mutex)
{
	if (status == 0)
		return ;
	if (status == EINVAL)
	{
		if (code == INIT)
		{
			pthread_mutex_destroy(mutex);
			error_handler("The value specified by attr is invalid");
		}
		else if (code == LOCK || code == UNLOCK)
			error_handler("Mutex lock/unlock failure");
		else
			error_handler("Invalid mutex operation");
	}
	else if (status == EDEADLK)
		error_handler("A deadlock would exit if the thread blocked for mutex");
	else if (status == EPERM)
		error_handler("The current thread does not hold a lock on mutex");
	else if (status == ENOMEM)
		error_handler("Lack of memory for creating another mutex");
	else if (status == EBUSY)
		error_handler("Mutex is locked");
	else
		error_handler("Unknown mutex error");
}

void	mutex_helper(t_mutex *mutex, t_mutex_code code)
{
	if (code == LOCK)
		mutex_error_handler(pthread_mutex_lock(mutex), code, mutex);
	else if (code == UNLOCK)
		mutex_error_handler(pthread_mutex_unlock(mutex), code, mutex);
	else if (code == INIT)
		mutex_error_handler(pthread_mutex_init(mutex, NULL), code, mutex);
	else if (code == DESTORY)
		mutex_error_handler(pthread_mutex_destroy(mutex), code, mutex);
	else
		error_handler("ERROR: Wrong code for mutex"\
			Y"Use CREATE or JOIN or DETACT"DF);
}

void	error_handler(const char *error_msg)
{
	printf(R"%s\n"DF, error_msg);
	exit(EXIT_FAILURE);
}

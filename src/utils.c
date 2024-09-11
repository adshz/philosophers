/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szhong <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 18:32:17 by szhong            #+#    #+#             */
/*   Updated: 2024/09/11 20:57:40 by szhong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "philo.h"

void	*malloc_helper(size_t bytes)
{
	void	*ptr;

	ptr = malloc(bytes);
	if (ptr == NULL)
		error_handler("ERROR: malloc failure");
	return (ptr);
}

static void	mutex_error_handler(int status, t_mutex_code code)
{
	if (status == 0)
		return ;
	if (status == EINVAL && (code == LOCK || code == UNLOCK))
	{
		pthread_mutex_destory(mutex);
		error_handler("mutex lock/unlcok failure");
	}
	else if (status == EINVAL && (code == INIT))
		error_handler("The value specified by attr is invalid");
	else if (status == EDEADLK)
		error_handler("A deadlock would exit if the thread blocked for mutex");
	else if (status == EPERM)
		error_handler("The current thread does not hold a lock on mutex");
	else if (status == ENOMEM)
		error_handler("Lack of memory for creating another mutex");
	else if (status == EBUSY)
		error_handler("Mutex is locked");
}

void	mutex_helper(t_mutex *mutex, t_mutex_code code)
{
	if (code == LOCK)
		mutex_error_handler(pthread_mutex_lock(mutex), code);
	else if (code == UNLOCK)
		mutex_error_handler(pthread_mutex_unlock(mutex), code);
	else if (code == INIT)
		mutex_error_handler(pthread_mutex_init(mutex, NULL), code);
	else if (code == DESTORY)
		mutex_error_handler((pthread_mutex_destory(mutex), code);
	else
		exit_handler("ERROR: Wrong code for mutex"\
			Y"Use CREATE or JOIN or DETACT"DF);
}

void	error_handler(const char *error_msg)
{
	printf(R"%s\n"DF, error_msg);
	exit(EXIT_FAILURE);
}

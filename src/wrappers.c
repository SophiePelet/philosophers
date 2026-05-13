/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wrappers.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sopelet <sopelet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/25 18:51:32 by sophie            #+#    #+#             */
/*   Updated: 2026/04/03 12:03:57 by sopelet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

int	create_mutex(pthread_mutex_t *mutex)
{
	if (pthread_mutex_init(mutex, NULL) != 0)
		return (0);
	return (1);
}

int	lock_mutex(pthread_mutex_t *mutex)
{
	if (pthread_mutex_lock(mutex) != 0)
		return (0);
	return (1);
}

int	unlock_mutex(pthread_mutex_t *mutex)
{
	if (pthread_mutex_unlock(mutex) != 0)
		return (0);
	return (1);
}

int	create_thread(pthread_t *thread, void *(*routine)(void *), void *arg)
{
	if (pthread_create(thread, NULL, routine, arg) != 0)
		return (0);
	return (1);
}

int	join_thread(pthread_t *thread)
{
	if (pthread_join(*thread, NULL) != 0)
		return (0);
	return (1);
}

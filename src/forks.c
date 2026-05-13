/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sopelet <sopelet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/27 14:02:58 by sophie            #+#    #+#             */
/*   Updated: 2026/04/06 16:17:29 by sopelet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

void	drop_single(t_philo *philo, int *has_forks)
{
	unlock_mutex(philo->left_f);
	*has_forks = 0;
}

void	drop_forks(t_philo *philo)
{
	if (philo->id % 2 == 0)
	{
		unlock_mutex(philo->left_f);
		unlock_mutex(philo->right_f);
		return ;
	}
	else
	{
		unlock_mutex(philo->right_f);
		unlock_mutex(philo->left_f);
		return ;
	}
}

int	pick_even(t_philo *philo)
{
	if (!lock_mutex(philo->right_f))
		return (-1);
	if (print_messages(philo, FORK) == -1)
	{
		unlock_mutex(philo->right_f);
		return (-1);
	}
	if (!lock_mutex(philo->left_f))
	{
		unlock_mutex(philo->right_f);
		return (-1);
	}
	if (print_messages(philo, FORK) == -1)
	{
		drop_forks(philo);
		return (-1);
	}
	return (0);
}

int	pick_odd(t_philo *philo)
{
	if (!lock_mutex(philo->left_f))
		return (-1);
	if (print_messages(philo, FORK) == -1)
	{
		unlock_mutex(philo->left_f);
		return (-1);
	}
	if (!lock_mutex(philo->right_f))
	{
		unlock_mutex(philo->left_f);
		return (-1);
	}
	if (print_messages(philo, FORK) == -1)
	{
		drop_forks(philo);
		return (-1);
	}
	return (0);
}

int	take_forks(t_philo *philo)
{
	int	res;

	if (philo->global->nb_philo == 1)
	{
		if (!lock_mutex(philo->right_f))
			return (-1);
		if (print_messages(philo, FORK) == -1)
		{
			unlock_mutex(philo->right_f);
			return (-1);
		}
		return (0);
	}
	if (!lock_mutex(&philo->global->meal))
		return (-1);
	if (philo->id % 2 == 0)
		res = pick_even(philo);
	else
		res = pick_odd(philo);
	if (!unlock_mutex(&philo->global->meal))
		return (-1);
	if (res == -1)
		return (-1);
	return (0);
}

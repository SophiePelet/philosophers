/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sopelet <sopelet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/30 22:53:47 by sophie            #+#    #+#             */
/*   Updated: 2026/04/06 17:07:09 by sopelet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

static int	check_philo_full(t_global *global)
{
	int		j;
	int		full;

	j = 0;
	full = 0;
	if (global->max_meal > 0)
	{
		while (j < global->nb_philo)
		{
			if (!lock_mutex(&global->philo[j]->meal_lock))
				return (-1);
			if (global->philo[j]->is_full == 1)
				full++;
			unlock_mutex(&global->philo[j]->meal_lock);
			j++;
		}
	}
	if (full == global->nb_philo)
		return (1);
	return (0);
}

static int	check_philo_dead(t_global *global)
{
	int		i;
	size_t	time;

	i = 0;
	while (i < global->nb_philo)
	{
		time = get_time_in_ms();
		if (!lock_mutex(&global->philo[i]->meal_lock))
			return (-1);
		if (time - global->philo[i]->last_meal >= global->time_to_die)
		{
			if (set_stop(global) == -1)
				return (unlock_mutex(&global->philo[i]->meal_lock), -1);
			if (print_messages(global->philo[i], DEAD) == -1)
				return (unlock_mutex(&global->philo[i]->meal_lock), -1);
			unlock_mutex(&global->philo[i]->meal_lock);
			return (1);
		}
		unlock_mutex(&global->philo[i]->meal_lock);
		i++;
	}
	return (0);
}

int	meal_monito(t_global *global)
{
	int	check;

	while (1)
	{
		check = check_philo_dead(global);
		if (check == -1)
			return (-1);
		if (check == 1)
			break ;
		if (global->max_meal > 0)
		{
			check = check_philo_full(global);
			if (check == -1)
				return (-1);
			if (check == 1)
			{
				if (set_stop(global) == -1)
					return (-1);
				break ;
			}
		}
		usleep(500);
	}
	return (0);
}

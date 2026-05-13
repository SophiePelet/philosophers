/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sopelet <sopelet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/31 23:12:05 by sophie            #+#    #+#             */
/*   Updated: 2026/04/06 16:18:06 by sopelet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

static void	single_philo(t_philo *philo, int *has_forks)
{
	if (!lock_mutex(&philo->meal_lock))
	{
		set_stop(philo->global);
		drop_single(philo, has_forks);
		return ;
	}
	philo->last_meal = get_time_in_ms();
	if (!unlock_mutex(&philo->meal_lock))
	{
		set_stop(philo->global);
		drop_single(philo, has_forks);
		return ;
	}
	if (interrupt_sleep(philo->global, philo->global->time_to_die) == -1)
	{
		set_stop(philo->global);
		drop_single(philo, has_forks);
		return ;
	}
	drop_single(philo, has_forks);
	*has_forks = 0;
	return ;
}

static int	philo_steps(t_philo *philo, int *has_forks)
{
	if (!philo_eat(philo))
		return (0);
	if (!increment_meals(philo, has_forks))
		return (0);
	if (!philo_sleep_think(philo))
		return (0);
	return (1);
}

void	*routine(void *arg)
{
	t_philo	*philo;
	int		has_forks;

	philo = (t_philo *)arg;
	if (!philo || !philo->global)
		return (NULL);
	has_forks = 0;
	if (philo->id % 2 == 0)
		interrupt_sleep(philo->global, philo->global->time_to_eat / 2);
	while (1)
	{
		if (!check_and_forks(philo, &has_forks))
			break ;
		if (philo->global->nb_philo == 1)
		{
			single_philo(philo, &has_forks);
			break ;
		}
		if (!philo_steps(philo, &has_forks))
			break ;
	}
	if (has_forks)
		drop_forks(philo);
	return (NULL);
}

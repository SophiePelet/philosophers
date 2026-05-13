/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sopelet <sopelet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/25 19:38:03 by sophie            #+#    #+#             */
/*   Updated: 2026/04/09 17:28:15 by sopelet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

void	clean_philo(t_philo **philo, int nb)
{
	while (nb >= 0)
	{
		if (philo[nb])
		{
			pthread_mutex_destroy(&philo[nb]->meal_lock);
			free(philo[nb]);
		}
		philo[nb] = NULL;
		nb--;
	}
	free(philo);
}

void	free_global(t_global *global)
{
	int	i;

	if (!global)
		return ;
	if (global->philo)
		clean_philo(global->philo, global->nb_philo - 1);
	if (global->forks)
	{
		i = 0;
		while (i < global->nb_philo)
		{
			pthread_mutex_destroy(&global->forks[i]);
			i++;
		}
		free(global->forks);
	}
	pthread_mutex_destroy(&global->meal);
	pthread_mutex_destroy(&global->message);
	pthread_mutex_destroy(&global->death);
	free(global);
}

void	join_created_threads(t_global *global, int nb)
{
	set_stop(global);
	while (nb >= 0)
	{
		join_thread(&global->philo[nb]->philo_thread);
		nb--;
	}
	ft_putstr_fd("Error\n", 2);
}

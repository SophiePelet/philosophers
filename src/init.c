/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sopelet <sopelet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/25 18:43:32 by sophie            #+#    #+#             */
/*   Updated: 2026/04/03 13:12:57 by sopelet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

static pthread_mutex_t	*forks_mutex(t_global *global)
{
	pthread_mutex_t	*fork;
	int				i;

	i = 0;
	fork = malloc(sizeof(pthread_mutex_t) * global->nb_philo);
	if (!fork)
		return (NULL);
	while (i < global->nb_philo)
	{
		if (!create_mutex(&fork[i]))
		{
			while (--i >= 0)
				pthread_mutex_destroy(&fork[i]);
			return (free(fork), NULL);
		}
		i++;
	}
	return (fork);
}

static int	global_mutex(t_global *global)
{
	global->forks = forks_mutex(global);
	if (!global->forks)
		return (0);
	if (!create_mutex(&global->meal))
		return (free(global->forks), global->forks = NULL, 0);
	if (!create_mutex(&global->message))
		return (pthread_mutex_destroy(&global->meal), free(global->forks),
			global->forks = NULL, 0);
	if (!create_mutex(&global->death))
		return (pthread_mutex_destroy(&global->message),
			pthread_mutex_destroy(&global->meal), free(global->forks),
			global->forks = NULL, 0);
	return (1);
}

static t_philo	**init_philo(t_global *global)
{
	t_philo	**philo;
	int		i;

	i = 0;
	philo = ft_calloc(global->nb_philo, sizeof(t_philo *));
	if (!philo)
		return (NULL);
	while (i < global->nb_philo)
	{
		philo[i] = malloc(sizeof(t_philo));
		if (!philo[i])
			return (clean_philo(philo, i - 1), NULL);
		philo[i]->id = i + 1;
		philo[i]->nb_meals = 0;
		philo[i]->is_full = 0;
		philo[i]->last_meal = global->start;
		philo[i]->global = global;
		philo[i]->left_f = &global->forks[i];
		philo[i]->right_f = &global->forks[(i + 1) % global->nb_philo];
		if (!create_mutex(&philo[i]->meal_lock))
			return (free(philo[i]), clean_philo(philo, i - 1), NULL);
		i++;
	}
	return (philo);
}

t_global	*init_global(int ac, char **av)
{
	t_global	*global;

	global = malloc(sizeof(t_global));
	if (!global)
		return (NULL);
	global->forks = NULL;
	global->philo = NULL;
	global->nb_philo = ft_atol(av[1]);
	global->time_to_die = ft_atol(av[2]);
	global->time_to_eat = ft_atol(av[3]);
	global->time_to_sleep = ft_atol(av[4]);
	global->max_meal = -1;
	if (ac == 6)
		global->max_meal = ft_atol(av[5]);
	global->start = get_time_in_ms();
	if (!global_mutex(global))
		return (free(global), NULL);
	global->philo = init_philo(global);
	if (!global->philo)
		return (free_global(global), NULL);
	global->stop_routine = 0;
	return (global);
}

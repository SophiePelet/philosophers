/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sopelet <sopelet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/25 14:47:38 by sophie            #+#    #+#             */
/*   Updated: 2026/04/03 13:05:51 by sopelet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

static int	start_thread(t_global *global)
{
	int	i;

	i = 0;
	global->start = get_time_in_ms();
	while (i < global->nb_philo)
	{
		if (!lock_mutex(&global->philo[i]->meal_lock))
			return (join_created_threads(global, i - 1), -1);
		global->philo[i]->last_meal = global->start;
		if (!unlock_mutex(&global->philo[i]->meal_lock))
			return (join_created_threads(global, i - 1), -1);
		if (!create_thread(&global->philo[i]->philo_thread, routine,
				global->philo[i]))
			return (join_created_threads(global, i - 1), -1);
		i++;
	}
	return (0);
}

int	main(int ac, char **av)
{
	t_global	*global;
	int			i;

	i = 0;
	if (!check_args(ac, av))
		return (1);
	global = init_global(ac, av);
	if (!global)
		return (1);
	if (start_thread(global) == -1)
		return (free_global(global), -1);
	if (meal_monito(global) == -1)
		return (join_created_threads(global, global->nb_philo - 1),
			free_global(global), -1);
	while (i < global->nb_philo)
	{
		join_thread(&global->philo[i]->philo_thread);
		i++;
	}
	free_global(global);
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   messages.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sopelet <sopelet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/25 15:32:22 by sophie            #+#    #+#             */
/*   Updated: 2026/04/03 13:12:18 by sopelet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

void	ft_putstr_fd(char *s, int fd)
{
	size_t	len;

	len = 0;
	if (!s)
		return ;
	while (s[len] != '\0')
		len++;
	write(fd, s, len);
}

static int	is_printable(t_philo *philo, char *print)
{
	int	printable;

	printable = 0;
	if (philo->global->stop_routine == 0 || ft_strcmp(print, DEAD) == 0)
		printable = 1;
	return (printable);
}

int	print_messages(t_philo *philo, char *print)
{
	size_t	time;
	int		printable;

	if (!lock_mutex(&philo->global->death))
		return (-1);
	printable = is_printable(philo, print);
	if (!lock_mutex(&philo->global->message))
	{
		unlock_mutex(&philo->global->death);
		return (-1);
	}
	if (printable)
	{
		time = get_time_in_ms() - philo->global->start;
		printf("%zu %d %s\n", time, philo->id, print);
	}
	if (!unlock_mutex(&philo->global->message))
	{
		unlock_mutex(&philo->global->death);
		return (-1);
	}
	if (!unlock_mutex(&philo->global->death))
		return (-1);
	return (0);
}

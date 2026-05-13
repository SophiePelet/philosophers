/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sopelet <sopelet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/25 14:47:46 by sophie            #+#    #+#             */
/*   Updated: 2026/04/03 12:04:13 by sopelet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

static int	nb_size(long long int nb)
{
	if (nb < INT_MIN)
		return (0);
	if (nb > INT_MAX)
		return (0);
	return (1);
}

static long long	exec_atol(char *nptr, int sign, int pos)
{
	int			i;
	long long	res;
	int			digit;

	i = pos;
	res = 0;
	while (nptr[i] != '\0' && ft_isdigit(nptr[i]))
	{
		digit = nptr[i] - '0';
		if (sign == 1)
		{
			if (res > (LLONG_MAX - digit) / 10)
				return (LLONG_MAX);
			res = res * 10 + digit;
		}
		else
		{
			if (res < (LLONG_MIN + digit) / 10)
				return (LLONG_MIN);
			res = res * 10 - digit;
		}
		i++;
	}
	return (res);
}

long long	ft_atol(char *n)
{
	int			i;
	long long	result;
	int			sign;

	i = 0;
	sign = 1;
	while (n[i] == 32 || (n[i] >= 9 && n[i] <= 13))
		i++;
	if (n[i] == '-' || n[i] == '+')
	{
		if (n[i] == '-')
			sign = -sign;
		i++;
	}
	if (n[i] == '-' || n[i] == '+')
		return (0);
	result = exec_atol(n, sign, i);
	return (result);
}

int	check_args(int ac, char **av)
{
	int				i;
	long long int	arg;

	i = 1;
	if (ac > 6 || ac < 5)
		return (ft_putstr_fd("Error\nWrong number of arguments\n", 2), 0);
	while (i < ac)
	{
		if (!is_number(av[i]))
			return (ft_putstr_fd("Error\nNot a number\n", 2), 0);
		arg = ft_atol(av[i]);
		if (!nb_size(arg))
			return (ft_putstr_fd("Error\nNumber is out of limits\n", 2), 0);
		if (i == 1)
		{
			if (arg > 200)
				return (ft_putstr_fd("Error\nToo many philosophers\n", 2), 0);
		}
		if (arg <= 0)
			return (ft_putstr_fd("Error\nInvalid input\n", 2), 0);
		i++;
	}
	return (1);
}

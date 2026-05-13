/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sopelet <sopelet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/25 14:43:16 by sophie            #+#    #+#             */
/*   Updated: 2026/04/06 16:17:32 by sopelet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>
# include <string.h>
# include <limits.h>

/* ------------------------------- MESSAGES --------------------------------- */

# define FORK "has taken a fork"
# define EAT "is eating"
# define SLEEP "is sleeping"
# define THINK "is thinking"
# define DEAD "died"

/* ------------------------------ STRUCTURES -------------------------------- */

typedef struct s_global	t_global;

typedef struct s_philo
{
	pthread_t		philo_thread;
	int				id;
	int				nb_meals;
	int				is_full;
	size_t			last_meal;
	pthread_mutex_t	meal_lock;
	pthread_mutex_t	*right_f;
	pthread_mutex_t	*left_f;
	t_global		*global;
}					t_philo;

typedef struct s_global
{
	int				stop_routine;
	size_t			start;
	size_t			time_to_eat;
	size_t			time_to_sleep;
	size_t			time_to_die;
	int				nb_philo;
	int				max_meal;
	pthread_mutex_t	*forks;
	pthread_mutex_t	meal;
	pthread_mutex_t	message;
	pthread_mutex_t	death;
	t_philo			**philo;
}					t_global;

/* -------------------------------- UTILS --------------------------------- */

void		ft_putstr_fd(char *s, int fd);
long long	ft_atol(char *n);
int			ft_isdigit(char c);
int			is_number(char *str);
int			ft_strcmp(char *s1, char *s2);
void		*ft_calloc(size_t nmemb, size_t size);

/* ------------------------------- PARSING -------------------------------- */

int			check_args(int ac, char **av);

/* -------------------------------- HELPERS ------------------------------- */

size_t		get_time_in_ms(void);
int			check_stop(t_global *global);
int			set_stop(t_global *global);

/* ------------------------------- WRAPPERS ------------------------------- */

int			create_mutex(pthread_mutex_t *mutex);
int			lock_mutex(pthread_mutex_t *mutex);
int			unlock_mutex(pthread_mutex_t *mutex);
int			create_thread(pthread_t *thread, void *(*routine)(void *),
				void *arg);
int			join_thread(pthread_t *thread);

/* --------------------------------- INIT --------------------------------- */

t_global	*init_global(int ac, char **av);

/* --------------------------------- CLEAN -------------------------------- */

void		free_global(t_global *global);
void		clean_philo(t_philo **philo, int nb);
void		join_created_threads(t_global *global, int nb);

/* -------------------------------- ROUTINE ------------------------------- */

int			interrupt_sleep(t_global *global, size_t wait);
int			print_messages(t_philo *philo, char *print);
void		*routine(void *arg);
int			meal_monito(t_global *global);
int			check_and_forks(t_philo *philo, int *has_forks);
int			philo_eat(t_philo *philo);
int			philo_sleep_think(t_philo *philo);
int			increment_meals(t_philo *philo, int *has_forks);

/* --------------------------------- FORKS -------------------------------- */

int			take_forks(t_philo *philo);
void		drop_forks(t_philo *philo);
void		drop_single(t_philo *philo, int *has_forks);

#endif
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svan-hoo <svan-hoo@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 21:59:12 by svan-hoo          #+#    #+#             */
/*   Updated: 2024/10/06 22:24:48 by svan-hoo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include <stdio.h>
# include <errno.h>
# include <string.h>
# include <stdarg.h>
# define _XOPEN_SOURCE 500
# include <unistd.h>
# include <stdlib.h>
# include <stdbool.h>
# include <pthread.h>
# include <sys/time.h>

# define NO_ACTIONS	3

typedef enum e_state
{
	thinking = 0,
	eating,
	sleeping,
	satisfied
}	t_state;

// struct	s_table;

typedef struct s_philosopher
{
	struct s_table	*r_table;
	pthread_t		tid;
	unsigned int	id;
	unsigned int	state;
	unsigned int	meal_count;
	unsigned long	deadline;
	pthread_mutex_t	structlock;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
}	t_philo;

typedef struct s_table
{
	t_philo			*philosophers;
	pthread_mutex_t	*forks;
	unsigned long	start_time;
	unsigned int	n_philo;
	unsigned int	time_to_die;
	unsigned int	time_to_eat;
	unsigned int	time_to_sleep;
	bool			active_meal_goal;
	unsigned int	meal_goal;
	unsigned int	satisfaction;
	bool			game_over;
	pthread_mutex_t	structlock;
	pthread_mutex_t	write_stdout;
}	t_table;

typedef void	(*t_action)(t_philo *);

// file: error_exit.c
void			clean_table(t_table *table);
void			error_exit(const int custom_errno, const char *msg);

// file: init_table.c
int				init_table(t_table *table, const int argc, const char **argv);

// file: parse.c
int				parse(int argc, const char **argv);
unsigned int	ft_atoui(const char *str);

// file: safe_read.c
bool			safe_bool(pthread_mutex_t *lock, const bool *read);
unsigned int	safe_uint(pthread_mutex_t *lock, const unsigned int *read);
unsigned long	safe_ulong(pthread_mutex_t *lock, const unsigned long *read);

// file: state_log.c
unsigned long	get_time(void);
void			log_change(t_philo *philo, const char *state_msg);
void			do_think(t_philo *philo);
void			do_eat(t_philo *philo);
void			do_sleep(t_philo *philo);

#endif
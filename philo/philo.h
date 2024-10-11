/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svan-hoo <svan-hoo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 21:59:12 by svan-hoo          #+#    #+#             */
/*   Updated: 2024/10/11 17:11:56 by svan-hoo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include <stdio.h>
# include <errno.h>
# include <string.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdbool.h>
# include <pthread.h>
# include <sys/time.h>

# define NO_PHILO_ACTIONS	3
# define PC_INERTIA			10

typedef enum e_state
{
	thinking,
	forking,
	eating,
	sleeping,
	done_or_dead
}	t_state;

typedef struct s_protected_mutex
{
	pthread_mutex_t	mutex;
	bool			is_initialised;
}	t_prot_mutex;

typedef struct s_philosopher
{
	t_prot_mutex	structlock;
	struct s_table	*r_table;
	pthread_t		tid;
	unsigned int	id;
	unsigned int	meal_count;
	unsigned long	deadline;
	t_state			state;
	t_prot_mutex	is_live;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
}	t_philo;

typedef struct s_table
{
	t_prot_mutex	structlock;
	t_philo			*philosophers;
	t_prot_mutex	*forks;
	unsigned long	start_time;
	unsigned int	n_philo;
	unsigned int	time_to_die;
	unsigned int	time_to_eat;
	unsigned int	time_to_sleep;
	bool			active_meal_goal;
	unsigned int	meal_goal;
	unsigned int	satisfaction;
	bool			simulation_running;
	t_prot_mutex	write_stdout;
}	t_table;

typedef void	(*t_action)(t_philo *);

// file: error_exit.c
void			clean_table(t_table *table);
void			error_exit(const int custom_errno, const char *msg);

// file: init_table.c
void			set_table(t_table *table, const int argc, const char **argv);
int				init_table(t_table *table);

// file: parse.c
int				parse(int argc, const char **argv);
unsigned int	ft_atoui(const char *str);

// file: safe_read.c
void			try_mutex(pthread_mutex_t *lock);
bool			safe_bool(pthread_mutex_t *lock, const bool *read);
unsigned int	safe_uint(pthread_mutex_t *lock, const unsigned int *read);
unsigned long	safe_ulong(pthread_mutex_t *lock, const unsigned long *read);

// file: state_log.c
unsigned long	get_time(void);
void			log_change(t_philo *philo, const t_state state);
void			do_think(t_philo *philo);
void			do_eat(t_philo *philo);
void			do_sleep(t_philo *philo);

#endif
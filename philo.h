/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svan-hoo <svan-hoo@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 21:59:12 by svan-hoo          #+#    #+#             */
/*   Updated: 2024/09/19 20:33:02 by svan-hoo         ###   ########.fr       */
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


typedef enum e_state
{
	thinking = 0,
	eating,
	sleeping,
	satisfied
}	t_state;

struct	s_table;

typedef struct s_philosopher
{
	struct s_table	*table;
	unsigned int	id;
	unsigned int	state;
	unsigned int	meal_count;
	unsigned int	deadline;
	pthread_mutex_t	lock;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
}	t_philo;

typedef struct s_table
{
	t_philo			*philosophers;
	pthread_mutex_t	*forks;
	unsigned int	start_time;
	unsigned int	n_philo;
	unsigned int	time_to_die;
	unsigned int	time_to_eat;
	unsigned int	time_to_sleep;
	unsigned int	meal_goal;
	unsigned int	satisfaction;
	bool			death;
	pthread_mutex_t	lock;
	pthread_mutex_t	write_stdout;
	pthread_mutex_t	write_stderr;
}	t_table;

// file: error_exit.c
void			clean_table(t_table *table);
void			error_exit(int custom_errno, t_table *table, char *msg);

// file: init_table.c
int				init_table(t_table *table, int argc, char **argv);

// file: parse.c
int				parse(t_table *table, int argc, char **argv);
short			ft_aisui(const char *str);
unsigned int	ft_atoui(const char *str);

// file: state_log.c
unsigned int	get_time(void);
void			log_change(t_philo *philo, char *state_msg);
void			do_eat_sleep_think(t_philo *philo);

#endif
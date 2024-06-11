/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: simon <simon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 21:59:12 by svan-hoo          #+#    #+#             */
/*   Updated: 2024/06/12 00:05:29 by simon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include <wait.h>
# include <stdio.h>
# include <errno.h>
# include <string.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdbool.h>
# include <pthread.h>

typedef enum e_state
{
	dead = 0,
	eating = 1,
	sleeping = 2,
	thinking = 3
}	t_state;

typedef struct s_philosopher
{
	pthread_t		tid;
	int				id;
	int				state;
	int				n_meals;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
}	t_philosopher;

typedef struct s_simdata
{
	t_philosopher	*philosophers;
	pthread_mutex_t	*forks;
	int				n_philo;
	unsigned int	time_to_die;
	unsigned int	time_to_eat;
	unsigned int	time_to_sleep;
	int				n_meals;
	pthread_mutex_t	read_stdin;
	pthread_mutex_t	write_stdout;
}	t_simdata;

// file: init.c
int				init(t_simdata *simdata, int argc, char **argv);

// file: parse.c
int				parse(t_simdata *simdata, int argc, char **argv);

// file: utils.c
int				ft_isdigit(char c);
unsigned int	ft_atoui(const char *str);
int				ft_atoi(const char *str);

#endif
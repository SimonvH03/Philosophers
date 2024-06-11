/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svan-hoo <svan-hoo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 21:59:12 by svan-hoo          #+#    #+#             */
/*   Updated: 2024/06/11 21:23:29 by svan-hoo         ###   ########.fr       */
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

typedef enum e_return
{
	e_true = 1,
	e_false = 0,
	e_error = -1,
	e_succes = 0,
	e_failure = 1
}	t_return;

typedef enum e_state
{
	dead = 0,
	eating = 1,
	sleeping = 2,
	thinking = 3
}	t_state;

typedef struct s_simdata
{
	t_philosopher	*philosophers;
	pthread_mutex_t	*forks;
	int				n_philo;
	unsigned int	time_to_die;
	unsigned int	time_to_eat;
	unsigned int	time_to_sleep;
	int				n_meals;
	bool			meal_limit;
}	t_simdata;

typedef struct s_philosopher
{
	pthread_t		tid;
	int				id;
	int				state;
	int				n_meals;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
}	t_philosopher;

// file: init.c
int			init(t_simdata *simdata, int argc, char **argv);

// file: parse.c
int			parse(t_simdata *simdata, int argc, char **argv);

#endif
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_table.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: simon <simon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 20:54:19 by svan-hoo          #+#    #+#             */
/*   Updated: 2024/08/20 00:30:24 by simon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

static int
	init_philosophers(
		t_table *table)
{
	int		i;
	t_philo	philo;

	i = 0;
	while (i < table->n_philo)
		if (pthread_mutex_init(&table->forks[i++], NULL))
			return (errno);
	while (i-- > 0)
	{
		philo = table->philosophers[i];
		philo.table = table;
		philo.id = i;
		philo.state = thinking;
		philo.meal_count = 0;
		philo.deadline = table->time_to_die;
		philo.left_fork = &table->forks[i];
		philo.right_fork = &table->forks[(i + 1) % table->n_philo];
	}
	return (EXIT_SUCCESS);
}

typedef struct s_philosopher
{
	struct s_table	*table;
	pthread_mutex_t	lock;
	unsigned int	id;
	unsigned int	state;
	unsigned int	meal_count;
	unsigned int	deadline;
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
	pthread_mutex_t	lock;
	pthread_mutex_t	death;
	pthread_mutex_t	write_stdout;
	pthread_mutex_t	write_stderr;
}	t_table;

int
	init_table(
		t_table *table,
		int argc,
		char **argv)
{
	table->n_philo = ft_atoui(argv[1]);
	table->time_to_die = ft_atoui(argv[2]);
	table->time_to_eat = ft_atoui(argv[3]);
	table->time_to_sleep = ft_atoui(argv[4]);
	table->meal_goal = -1;
	if (argc == 6)
		table->meal_goal = ft_atoui(argv[5]);
	table->satisfaction = 0;
	table->philosophers = malloc(sizeof(t_philo) * table->n_philo);
	if (table->philosophers == NULL)
		return (errno);
	table->forks = malloc(sizeof(pthread_mutex_t) * table->n_philo);
	if (table->forks == NULL)
		return (errno);
	if (pthread_mutex_init(&table->death, NULL)
		|| pthread_mutex_init(&table->lock, NULL)
		|| pthread_mutex_init(&table->write_stderr, NULL)
		|| pthread_mutex_init(&table->write_stderr, NULL))
		return (errno);
	if (init_philosophers(table))
		return (errno);
	table->start_time = get_time();
	return (EXIT_SUCCESS);
}

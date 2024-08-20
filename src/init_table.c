/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_table.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svan-hoo <svan-hoo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 20:54:19 by svan-hoo          #+#    #+#             */
/*   Updated: 2024/08/20 20:40:40 by svan-hoo         ###   ########.fr       */
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
	i = 0;
	while (i < table->n_philo)
	{
		if (pthread_mutex_init(&philo.lock, NULL))
			return (errno);
		philo.id = (unsigned int)i + 1;
		philo.table = table;
		philo.state = thinking;
		philo.meal_count = 0;
		philo.left_fork = &table->forks[i];
		philo.right_fork = &table->forks[(i + 1) % table->n_philo];
		table->philosophers[i] = philo;
		++i;
	}
	return (EXIT_SUCCESS);
}

int
	init_table(
		t_table *table,
		int argc,
		char **argv)
{
	table->n_philo = ft_atoui(argv[1]);
	table->philosophers = malloc(sizeof(t_philo) * table->n_philo);
	if (table->philosophers == NULL)
		return (errno);
	table->phid = malloc(sizeof(pthread_t) * table->n_philo);
	if (table->phid== NULL)
		return (errno);
	table->forks = malloc(sizeof(pthread_mutex_t) * table->n_philo);
	if (table->forks == NULL)
		return (errno);
	table->time_to_die = ft_atoui(argv[2]);
	table->time_to_eat = ft_atoui(argv[3]);
	table->time_to_sleep = ft_atoui(argv[4]);
	table->meal_goal = -1;
	if (argc == 6)
		table->meal_goal = ft_atoui(argv[5]);
	table->satisfaction = 0;
	table->game_over = false;
	if (pthread_mutex_init(&table->lock, NULL)
		|| pthread_mutex_init(&table->trigger, NULL)
		|| pthread_mutex_init(&table->write_stdout, NULL))
		return (errno);
	// pthread_mutex_lock(&table->trigger);
	if (init_philosophers(table))
		return (errno);
	return (EXIT_SUCCESS);
}

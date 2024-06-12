/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svan-hoo <svan-hoo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 20:54:19 by svan-hoo          #+#    #+#             */
/*   Updated: 2024/06/12 19:30:42 by svan-hoo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

static int
	init_philosophers(
		t_simdata *table)
{
	int				i;
	t_philosopher	philo;

	i = 0;
	while (i++ < table->n_philo)
		if (pthread_mutex_init(&table->forks[i], NULL))
			return (errno);
	while (i-- > 0)
	{
		philo = table->philosophers[i];
		philo.id = i;
		philo.state = thinking;
		philo.n_meals = 0;
		philo.left_fork = &table->forks[i];
		philo.right_fork = &table->forks[(i + 1) % table->n_philo];
	}
	return (EXIT_SUCCESS);
}

int
	init(
		t_simdata *table,
		int argc,
		char **argv)
{
	table->n_philo = ft_atoi(argv[1]);
	table->time_to_die = ft_atoui(argv[2]);
	table->time_to_eat = ft_atoui(argv[3]);
	table->time_to_sleep = ft_atoui(argv[4]);
	table->n_meals = -1;
	if (argc == 6)
		table->n_meals = ft_atoi(argv[5]);
	table->philosophers = malloc(sizeof(t_philosopher) * table->n_philo);
	if (table->philosophers == NULL)
		return (errno);
	table->forks = malloc(sizeof(pthread_mutex_t) * table->n_philo);
	if (table->forks == NULL)
		return (errno);
	if (pthread_mutex_init(&table->write_stdout, NULL)
		|| pthread_mutex_init(&table->read_stdin, NULL))
		return (errno);
	if (init_philosophers(table))
		return (errno);
	return (EXIT_SUCCESS);
}

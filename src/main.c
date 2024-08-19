/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svan-hoo <svan-hoo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 21:48:59 by svan-hoo          #+#    #+#             */
/*   Updated: 2024/08/19 18:18:19 by svan-hoo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void*
	sentient_spaghetti_bowl_routine(
		void *arg)
{
	t_philo	*philo;

	philo = arg;
	return (NULL);
}

void*
	philo_routine(
		void *arg)
{
	t_philo	*philo;

	philo = arg;
	return (NULL);
}

static void
	create_threads(
		t_table *table)
{
	int	i;

	i = 0;
	if (pthread_create(&table->philosophers[i].tid, NULL,
			&sentient_spaghetti_bowl_routine, &table))
		error_exit(table, "create_threads -> pthread_create");
	while (i < table->n_philo)
	{
		if (pthread_create(&table->philosophers[i].tid, NULL,
				&philo_routine, &table))
			error_exit(table, "create_threads -> pthread_create");
		++i;
	}
}

int
	main(
		int argc,
		char **argv)
{
	t_table	table;

	if (argc < 5 || argc > 6 || parse(&table, argc, argv) == EXIT_FAILURE)
		return (EINVAL);
	if (init_table(&table, argc, argv))
		return (errno);
	create_threads(&table);
	return (EXIT_SUCCESS);
}

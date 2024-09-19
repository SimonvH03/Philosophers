/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svan-hoo <svan-hoo@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 21:48:59 by svan-hoo          #+#    #+#             */
/*   Updated: 2024/09/19 20:44:16 by svan-hoo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

static void*
	sentient_spaghetti_routine(
		void *arg)
{
	t_table	*table;

	table = arg;
	while (table->satisfaction < table->n_philo)
		;
	pthread_mutex_lock(&table->lock);
	table->death = true;
	pthread_mutex_unlock(&table->lock);
	return (NULL);
}

static void*
	philo_telekinesis_routine(
		void *arg)
{
	t_philo	*philo;

	philo = arg;
	while (philo->table->death == false)
	{
		pthread_mutex_lock(&philo->lock);
		if (philo->state != eating && get_time() > philo->deadline)
		{
			log_change(philo, "died");
			pthread_mutex_lock(&philo->table->lock);
			philo->table->death = true;
			pthread_mutex_unlock(&philo->table->lock);
			return (NULL);
		}
		if (philo->meal_count == philo->table->meal_goal)
		{
			pthread_mutex_lock(&philo->table->lock);
			++philo->table->satisfaction;
			pthread_mutex_unlock(&philo->table->lock);
		}
		pthread_mutex_unlock(&philo->lock);
		usleep(5000);
	}
	return (NULL);
}

static void*
	philo_eat_sleep_think_routine(
		void *arg)
{
	t_philo		*philo;
	pthread_t	tid;

	philo = arg;
	if (pthread_create(&tid, NULL, philo_telekinesis_routine, philo))
		return ((void *)1);
	while (philo->table->death == false)
		do_eat_sleep_think(philo);
	pthread_join(tid, NULL);
	return (NULL);
}

static short
	create_threads(
		t_table *table)
{
	pthread_t	philo_tids[table->n_philo];
	pthread_t	spaghetti_tid;
	t_philo		philo;
	int			i;

	if (table->meal_goal >= 0)
		if (pthread_create(&spaghetti_tid, NULL,
			&sentient_spaghetti_routine, &table))
			return (EXIT_FAILURE);
	i = 0;
	while (i < table->n_philo)
	{
		philo = table->philosophers[i];
		if (pthread_create(&philo_tids[i], NULL,
			&philo_eat_sleep_think_routine, &philo))
			return (EXIT_FAILURE);
		++i;
	}
	while (i-- > 0)
	{
		if (pthread_join(philo_tids[i], NULL))
			return (EXIT_FAILURE);
	}
	if (pthread_join(spaghetti_tid, NULL))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int
	main(
		int argc,
		char **argv,
		char **envp)
{
	t_table	table;

	if (argc < 5 || argc > 6 || parse(&table, argc, argv) == EXIT_FAILURE)
		error_exit(EINVAL, &table, NULL);
	if (init_table(&table, argc, argv) == EXIT_FAILURE)
		error_exit(0, &table, "init_table()");
	// if (create_threads(&table) == EXIT_FAILURE)
	// {
	// 	error_exit(0, &table, "create_threads()");
	// 	clean_table(&table);
	// }
	pthread_mutex_lock(table.philosophers[0].left_fork);
	pthread_mutex_unlock(table.philosophers[0].left_fork);
	pthread_mutex_lock(table.philosophers[0].right_fork);
	pthread_mutex_unlock(table.philosophers[0].right_fork);
	printf("\e[31mpass\e[0m\n");
	clean_table(&table);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: simon <simon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 21:48:59 by svan-hoo          #+#    #+#             */
/*   Updated: 2024/08/19 23:50:05 by simon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

static void*
	sentient_spaghetti_routine(
		void *arg)
{
	t_table	*table;

	table = arg;
	while (1)
	{
		if (table->satisfaction == table->meal_goal)
			pthread_mutex_lock(&table->death);
		usleep(500);
	}
	return (NULL);
}

static void*
	philo_telekinesis_routine(
		void *arg)
{
	t_philo	*philo;

	philo = arg;
	while (1)
	{
		pthread_mutex_lock(&philo->lock);
		pthread_mutex_lock(&philo->table->lock);
		if (philo->state != eating && get_time() > philo->deadline)
		{
			log_change(philo, "died");
			// pthread_mutex_unlock(&philo->lock);
			pthread_mutex_lock(&philo->table->death);
			// pthread_mutex_unlock(&philo->table->lock);
			return (NULL);
		}
		if (philo->meal_count == philo->table->meal_goal)
			++philo->table->satisfaction;
		pthread_mutex_unlock(&philo->table->lock);
		pthread_mutex_unlock(&philo->lock);
		usleep(500);
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
	pthread_detach(tid);
	while (1)
		do_eat_sleep_think(philo);
	return (NULL);
}

static short
	create_threads(
		t_table *table)
{
	t_philo		philo;
	pthread_t	tid;
	int			i;

	if (table->meal_goal >= 0)
		if (pthread_create(&tid, NULL, &sentient_spaghetti_routine, &table))
			return (EXIT_FAILURE);
	i = 0;
	while (i < table->n_philo)
	{
		philo = table->philosophers[i];
		if (pthread_create(&tid, NULL, &philo_eat_sleep_think_routine, &philo))
			return (EXIT_FAILURE);
		pthread_detach(tid);
		++i;
	}
	// while... join instead of detach (tids must be stored)
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
		return (EINVAL);
	if (init_table(&table, argc, argv))
		return (errno);
	if (create_threads(&table) == EXIT_FAILURE)
		error_exit(&table, "create_threads()");
	error_exit(&table, NULL);
}

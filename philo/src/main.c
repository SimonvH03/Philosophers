/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svan-hoo <svan-hoo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 21:48:59 by svan-hoo          #+#    #+#             */
/*   Updated: 2024/10/01 20:24:49 by svan-hoo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

static void*
	sentient_spaghetti_routine(
		void *arg)
{
	t_table	*table;

	table = arg;
	if (table->meal_goal == -1)
		return (NULL);
	while (table->satisfaction < table->n_philo && table->game_over == false)
		continue ;
	if (table->game_over == false)
	{
		pthread_mutex_lock(&table->lock);
		table->game_over = true;
		pthread_mutex_unlock(&table->lock);
	}
	return (NULL);
}

static void*
	philo_telekinesis_routine(
		void *arg)
{
	t_philo	*philo;

	philo = arg;
	while (philo->r_table->game_over == false)
	{
		if (philo->state != eating && get_time() > philo->deadline)
		{
			log_change(philo, "died");
			pthread_mutex_lock(&philo->r_table->lock);
			philo->r_table->game_over = true;
			pthread_mutex_unlock(&philo->r_table->lock);
			break ;
		}
		if ((int)philo->meal_count == philo->r_table->meal_goal)
		{
			log_change(philo, "is satisfied");
			pthread_mutex_lock(&philo->r_table->lock);
			++philo->r_table->satisfaction;
			pthread_mutex_unlock(&philo->r_table->lock);
			break ;
		}
		usleep(50);
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
	philo->deadline = get_time() + philo->r_table->time_to_die;
	if (pthread_create(&tid, NULL, philo_telekinesis_routine, philo))
		return ((void *)1);
	while (philo->r_table->game_over == false && philo->state == thinking)
	{
		do_eat_sleep_think(philo);
	}
	return (NULL);
}

static short
	create_threads(
		t_table *table)
{
	pthread_t	spaghetti_tid;
	t_philo		*philo;
	size_t		i;

	table->start_time = get_time();
	if (pthread_create(&spaghetti_tid, NULL,
			&sentient_spaghetti_routine, table))
		return (EXIT_FAILURE);
	i = 0;
	while (i < table->n_philo)
	{
		philo = &table->philosophers[i];
		if (pthread_create(&philo->tid, NULL,
				&philo_eat_sleep_think_routine, philo))
			return (EXIT_FAILURE);
		++i;
		usleep(1000);// this mf is the least reliable way to prevent deadlocks
	}
	if (pthread_join(spaghetti_tid, NULL))
		return (EXIT_FAILURE);
	while (i-- > 0)
		if (pthread_join(table->philosophers[i].tid, NULL))
			return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int
	main(
		int argc,
		char **argv)
{
	t_table	table;

	if (argc < 5 || argc > 6 || parse(argc, argv) == EXIT_FAILURE)
		error_exit(EINVAL, NULL);
	if (init_table(&table, argc, argv) == EXIT_FAILURE)
		error_exit(0, "init_table()");
	if (create_threads(&table) == EXIT_FAILURE)
	{
		error_exit(0, "create_threads()");
		clean_table(&table);
	}
	clean_table(&table);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svan-hoo <svan-hoo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 21:48:59 by svan-hoo          #+#    #+#             */
/*   Updated: 2024/08/20 20:42:01 by svan-hoo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

static void*
	philo_telekinesis_routine(
		void *arg)
{
	t_philo	*philo;

	philo = arg;
	while (1)
	{
		if (philo->state == satisfied)
		{
			pthread_mutex_lock(&philo->table->lock);
			++philo->table->satisfaction;
			pthread_mutex_unlock(&philo->table->lock);
		}
		if (philo->state != eating && philo->state != satisfied
			&& get_time() - philo->table->start_time > philo->deadline - philo->table->start_time)
		{
			printf("\e[31m[%d] died: %lu, %lu\e[0m\n", philo->id, get_time() - philo->table->start_time, philo->deadline - philo->table->start_time);
			log_change(philo, "died");
			pthread_mutex_lock(&philo->table->lock);
			philo->table->game_over = true;
			pthread_mutex_unlock(&philo->table->lock);
			pthread_mutex_unlock(&philo->table->trigger);
			return (NULL);
		}
		usleep(10000);
	}
	return (NULL);
}

static void*
	philo_eat_sleep_think_routine(
		void *arg)
{
	t_philo		*philo;

	philo = arg;
	log_change(philo, "\e[32mspawned\e[0m");
	philo->deadline = get_time() + philo->table->time_to_die;
	if (pthread_create(&philo->telekinesid, NULL, philo_telekinesis_routine, philo))
		return ((void *)1);
	while (philo->table->game_over == false && philo->state != satisfied)
	{
		log_change(philo, "\e[34mattempting to eat\e[0m");
		do_eat_sleep_think(philo);
		if (philo->meal_count == philo->table->meal_goal)
		{
			philo->state = satisfied;
			log_change(philo, "is satisfied");
		}
		usleep(2000);
	}
	if (pthread_join(philo->telekinesid, NULL))
		return ((void *)1);
	log_change(philo, "\e[32mtele joined -\e[33mphilo terminated\e[0m\n");
	return (NULL);
}

static void*
	sentient_spaghetti_routine(
		void *arg)
{
	t_table	*table;

	table = arg;
	pthread_mutex_lock(&table->write_stdout);
	printf("\e[33mBOWL spawned\e[0m\n");
	pthread_mutex_unlock(&table->write_stdout);
	while (table->satisfaction < table->n_philo)
	{
		printf("\e[32m%lu X table satisfaction check...\e[0m\n", get_time() - table->start_time);
		usleep(10000);
	}
	// pthread_mutex_unlock(&table->trigger);
	return (NULL);
}

static short
	create_threads(
		t_table *table)
{
	t_philo		philo;
	int			i;

	i = 0;
	table->start_time = get_time();
	if (table->meal_goal >= 0)
		if (pthread_create(&table->spaghettid, NULL, &sentient_spaghetti_routine, &table))
			return (EXIT_FAILURE);
	while (i < table->n_philo)
	{
		philo = table->philosophers[i];
		if (pthread_create(&table->phid[i], NULL, &philo_eat_sleep_think_routine, &philo))
			return (EXIT_FAILURE);
		++i;
		usleep(400000);
	}
	if (pthread_join(table->spaghettid, NULL))
		return (EXIT_FAILURE);
	i = 0;
	while (i < table->n_philo)
	{
		printf("\e[31mattempting to join philo %d\e[0m\n", i + 1);
		if (pthread_join(table->phid[i], NULL))
			return (EXIT_FAILURE);
		printf("\e[32mphilo %d joined\e[0m\n", i + 1);
		++i;
	}
	// pthread_mutex_lock(&table->trigger);
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
	error_exit(&table, "main");
}

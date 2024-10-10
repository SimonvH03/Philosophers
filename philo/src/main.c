/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svan-hoo <svan-hoo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 21:48:59 by svan-hoo          #+#    #+#             */
/*   Updated: 2024/10/10 19:27:04 by svan-hoo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

static void	philo_hunger_check(t_philo *philo)
{
	if (philo->r_table->active_meal_goal == true
		&& safe_uint(&philo->structlock.mutex,
			&philo->meal_count) == philo->r_table->meal_goal)
	{
		pthread_mutex_lock(&philo->structlock.mutex);
		philo->state = satisfied;
		pthread_mutex_unlock(&philo->structlock.mutex);
		pthread_mutex_lock(&philo->r_table->structlock.mutex);
		++philo->r_table->satisfaction;
		pthread_mutex_unlock(&philo->r_table->structlock.mutex);
	}
	if (safe_ulong(&philo->structlock.mutex,
			&philo->deadline) < get_time())
	{
		log_change(philo, "died");
		pthread_mutex_lock(&philo->r_table->structlock.mutex);
		philo->r_table->game_over = true;
		pthread_mutex_unlock(&philo->r_table->structlock.mutex);
	}
}

static void	spaghetti_satisfaction(t_table *table)
{
	size_t	i;

	while (true)
	{
		i = 0;
		while (i < table->n_philo)
		{
			philo_hunger_check(&table->philosophers[i]);
			i++;
		}
		if (table->active_meal_goal == true)
		{
			pthread_mutex_lock(&table->structlock.mutex);
			if (table->satisfaction >= table->n_philo)
				table->game_over = true;
			pthread_mutex_unlock(&table->structlock.mutex);
		}
		if (table->game_over == true)
			break ;
		// print logs
		usleep(420);
	}
	pthread_mutex_unlock(&table->structlock.mutex);
}

static void	*philo_eat_sleep_think_routine(void *arg)
{
	const t_action	routine[NO_PHILO_ACTIONS] = {do_think, do_eat, do_sleep};
	size_t			action;
	t_philo			*philo;

	philo = arg;
	philo->deadline = get_time() + philo->r_table->time_to_die;
	action = 0;
	while (safe_bool(&philo->r_table->structlock.mutex,
			&philo->r_table->game_over) == false
		&& (t_state)safe_uint(&philo->structlock.mutex,
			&philo->state) != satisfied)
	{
		routine[action](philo);
		action = (action + 1) % NO_PHILO_ACTIONS;
		usleep(1);
	}
	return (NULL);
}

static short	create_threads(t_table *table)
{
	t_philo		*philo;
	size_t		i;

	table->start_time = get_time();
	i = 0;
	while (i < table->n_philo)
	{
		philo = &table->philosophers[i++];
		if (pthread_create(&philo->tid, NULL,
				&philo_eat_sleep_think_routine, philo))
			return (EXIT_FAILURE);
		usleep(42);
	}
	spaghetti_satisfaction(table);
	while (i--)
		if (pthread_join(table->philosophers[i].tid, NULL))
			return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int	main(const int argc, const char **argv)
{
	t_table	table;

	if (argc < 5 || argc > 6 || parse(argc, argv) == EXIT_FAILURE)
		error_exit(EINVAL, NULL);
	set_table(&table, argc, argv);
	if (init_table(&table) == EXIT_FAILURE)
	{
		clean_table(&table);
		error_exit(0, "init_table()");
	}
	if (create_threads(&table) == EXIT_FAILURE)
	{
		clean_table(&table);
		error_exit(0, "create_threads()");
	}
	clean_table(&table);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svan-hoo <svan-hoo@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 21:48:59 by svan-hoo          #+#    #+#             */
/*   Updated: 2024/10/07 00:37:51 by svan-hoo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

static void	*sentient_spaghetti_routine(void *arg)
{
	t_table	*table;

	table = arg;
	if (table->active_meal_goal == false)
		return (NULL);
	while (true)
	{
		pthread_mutex_lock(&table->structlock);
		if (table->satisfaction >= table->n_philo)
			table->game_over = true;
		if (table->game_over == true)
			break ;
		pthread_mutex_unlock(&table->structlock);
		usleep(42);
	}
	pthread_mutex_unlock(&table->structlock);
	return (NULL);
}

static void	*philo_hunger_routine(void *arg)
{
	t_philo	*philo;
	t_table	*table;

	philo = arg;
	table = philo->r_table;
	while (safe_bool(&table->structlock, &table->game_over) == false)
	{
		if (!usleep(42) && table->active_meal_goal == true && table->meal_goal
			== safe_uint(&philo->structlock, &philo->meal_count))
		{
			pthread_mutex_lock(&table->structlock);
			philo->state = satisfied;
			++table->satisfaction;
			pthread_mutex_unlock(&table->structlock);
			break ;
		}
		if (get_time() > safe_ulong(&philo->structlock, &philo->deadline))
		{
			log_change(philo, "died");
			pthread_mutex_lock(&table->structlock);
			table->game_over = true;
			pthread_mutex_unlock(&table->structlock);
		}
	}
	return (NULL);
}

static void	*philo_eat_sleep_think_routine(void *arg)
{
	const t_action	routine[NO_ACTIONS] = {do_think, do_eat, do_sleep};
	size_t			action;
	t_philo			*philo;
	t_table			*table;
	pthread_t		tid;

	philo = arg;
	table = philo->r_table;
	philo->deadline = get_time() + table->time_to_die;
	if (pthread_create(&tid, NULL, philo_hunger_routine, philo))
		return ((void *)EXIT_FAILURE);
	action = 0;
	while (safe_bool(&table->structlock, &table->game_over) == false
		&& (t_state)safe_uint(&philo->structlock, &philo->state) != satisfied)
	{
		routine[action](philo);
		action = (action + 1) % NO_ACTIONS;
		usleep(1);
	}
	if (pthread_join(tid, NULL))
		return ((void *)EXIT_FAILURE);
	return (NULL);
}

static short	create_threads(t_table *table)
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
		philo = &table->philosophers[i++];
		if (pthread_create(&philo->tid, NULL,
				&philo_eat_sleep_think_routine, philo))
			return (EXIT_FAILURE);
		usleep(42);
	}
	if (pthread_join(spaghetti_tid, NULL))
		return (EXIT_FAILURE);
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
	if (init_table(&table, argc, argv) == EXIT_FAILURE)
		error_exit(0, "init_table()");
	if (create_threads(&table) == EXIT_FAILURE)
	{
		error_exit(0, "create_threads()");
		clean_table(&table);
	}
	clean_table(&table);
}

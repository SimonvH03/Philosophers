/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svan-hoo <svan-hoo@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 21:48:59 by svan-hoo          #+#    #+#             */
/*   Updated: 2024/11/08 17:57:24 by svan-hoo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

static void	philo_hunger_check(t_philo *philo)
{
	pthread_mutex_lock(&philo->structlock.mutex);
	if (philo->state != satisfied
		&& get_time() > philo->deadline)
	{
		pthread_mutex_lock(&philo->r_table->structlock.mutex);
		philo->r_table->simulation_running = false;
		pthread_mutex_unlock(&philo->r_table->structlock.mutex);
		log_change(philo, dead);
	}
	pthread_mutex_unlock(&philo->structlock.mutex);
	return ;
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
				table->simulation_running = false;
			pthread_mutex_unlock(&table->structlock.mutex);
		}
		if (table->simulation_running == false)
			break ;
		usleep(42 * PC_INERTIA);
	}
}

static void	*philo_eat_sleep_think_routine(void *arg)
{
	const t_action	routine[NO_PHILO_ACTIONS] = {do_think, do_eat, do_sleep};
	size_t			action;
	t_philo			*philo;

	philo = arg;
	pthread_mutex_lock(&philo->r_table->structlock.mutex);
	pthread_mutex_unlock(&philo->r_table->structlock.mutex);
	action = 0;
	routine[action++](philo);
	if (philo->id % 2 == 0)
		ft_sleep(philo, (philo->r_table->time_to_eat) * 0.9);
	while (philo->state != dead
		&& safe_bool(&philo->r_table->structlock.mutex,
			&philo->r_table->simulation_running) == true)
	{
		routine[action](philo);
		action = (action + 1) % NO_PHILO_ACTIONS;
		usleep(1);
	}
	return (NULL);
}

static short	create_threads(t_table *table)
{
	t_philo			*philo;
	unsigned int	i;

	pthread_mutex_lock(&table->structlock.mutex);
	i = 0;
	while (i < table->n_philo)
	{
		philo = &table->philosophers[i++];
		if (pthread_create(&philo->tid, NULL,
				&philo_eat_sleep_think_routine, philo))
			return (EXIT_FAILURE);
		usleep(1);
	}
	table->start_time = get_time();
	while (i)
	{
		philo = &table->philosophers[--i];
		philo->deadline = table->start_time + table->time_to_die;
	}
	pthread_mutex_unlock(&table->structlock.mutex);
	spaghetti_satisfaction(table);
	while (i < table->n_philo)
		if (pthread_join(table->philosophers[i++].tid, NULL))
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

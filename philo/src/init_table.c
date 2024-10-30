/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_table.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svan-hoo <svan-hoo@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 20:54:19 by svan-hoo          #+#    #+#             */
/*   Updated: 2024/10/30 19:25:22 by svan-hoo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

static short	ft_swap(void *a, void *b, size_t size)
{
	char	temp[256];
	size_t	i;

	if (size > 256)
		return (EXIT_FAILURE);
	i = 0;
	while (i < size)
	{
		temp[i] = ((char *)a)[i];
		((char *)a)[i] = ((char *)b)[i];
		i++;
	}
	while (i--)
	{
		((char *)b)[i] = temp[i];
	}
	return (EXIT_SUCCESS);
}

static int	init_forks(t_table *table)
{
	size_t	i;

	i = 0;
	while (i < table->n_philo)
	{
		table->forks[i].is_initialised = false;
		i++;
	}
	while (i-- > 0)
	{
		if (pthread_mutex_init(&table->forks[i].mutex, NULL))
			return (EXIT_FAILURE);
		table->forks[i].is_initialised = true;
	}
	return (EXIT_SUCCESS);
}

static int	init_philosophers(t_table *table)
{
	size_t	i;
	t_philo	*philo;

	i = table->n_philo;
	while (i--)
	{
		philo = &table->philosophers[i];
		if (pthread_mutex_init(&philo->structlock.mutex, NULL))
			return (EXIT_FAILURE);
		philo->structlock.is_initialised = true;
		if (pthread_mutex_init(&philo->is_live.mutex, NULL))
			return (EXIT_FAILURE);
		philo->is_live.is_initialised = true;
		philo->r_table = table;
		philo->id = i + 1;
		philo->state = thinking;
		philo->meal_count = 0;
		philo->deadline = get_time() + table->time_to_die;
		philo->left_fork = &table->forks[i].mutex;
		philo->right_fork = &table->forks[(i + 1) % table->n_philo].mutex;
		if (i == table->n_philo)
			ft_swap(philo->left_fork, philo->right_fork, sizeof(pthread_mutex_t *));
		if (i % 2 == 0)
			ft_swap(philo->left_fork, philo->right_fork, sizeof(pthread_mutex_t *));
	}
	return (EXIT_SUCCESS);
}

void	set_table(t_table *table, const int argc, const char **argv)
{
	table->forks = NULL;
	table->philosophers = NULL;
	table->n_philo = ft_atoui(argv[1]);
	table->time_to_die = ft_atoui(argv[2]);
	table->time_to_eat = ft_atoui(argv[3]);
	table->time_to_sleep = ft_atoui(argv[4]);
	table->meal_goal = 0;
	table->satisfaction = 0;
	table->active_meal_goal = (argc == 6);
	if (table->active_meal_goal == true)
		table->meal_goal = (int)ft_atoui(argv[5]);
	table->simulation_running = false;
}

static void	init_default_values(t_table *table)
{
	size_t	i;

	i = table->n_philo;
	while (i--)
	{
		table->philosophers[i].structlock.is_initialised = false;
		table->forks[i].is_initialised = false;
	}
	table->structlock.is_initialised = false;
	table->write_stdout.is_initialised = false;
}

int	init_table(t_table *table)
{
	table->philosophers = malloc(sizeof(t_philo) * table->n_philo);
	if (table->philosophers == NULL)
		return (EXIT_FAILURE);
	table->forks = malloc(sizeof(t_prot_mutex) * table->n_philo);
	if (table->forks == NULL)
		return (EXIT_FAILURE);
	init_default_values(table);
	if (init_philosophers(table) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	if (init_forks(table) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	if (pthread_mutex_init(&table->write_stdout.mutex, NULL))
		return (EXIT_FAILURE);
	table->write_stdout.is_initialised = true;
	if (pthread_mutex_init(&table->structlock.mutex, NULL))
		return (EXIT_FAILURE);
	table->structlock.is_initialised = true;
	table->start_time = get_time();
	return (EXIT_SUCCESS);
}

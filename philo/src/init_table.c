/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_table.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svan-hoo <svan-hoo@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 20:54:19 by svan-hoo          #+#    #+#             */
/*   Updated: 2024/10/06 22:32:02 by svan-hoo         ###   ########.fr       */
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

static int	init_philosophers(t_table *table)
{
	size_t	i;
	t_philo	*philo;

	i = 0;
	while (i < table->n_philo)
		if (pthread_mutex_init(&table->forks[i++], NULL))
			return (EXIT_FAILURE);
	while (i-- > 0)
	{
		philo = &table->philosophers[i];
		if (pthread_mutex_init(&philo->structlock, NULL))
			return (EXIT_FAILURE);
		philo->r_table = table;
		philo->id = i + 1;
		philo->state = thinking;
		philo->meal_count = 0;
		philo->deadline = table->time_to_die;
		philo->left_fork = &table->forks[i];
		philo->right_fork = &table->forks[(i + 1) % table->n_philo];
		if (i == table->n_philo - 1)
			if (ft_swap(&philo->left_fork, &philo->right_fork,
					sizeof(&philo->left_fork)) == EXIT_FAILURE)
				return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

int	init_table(t_table *table, const int argc, const char **argv)
{
	table->n_philo = ft_atoui(argv[1]);
	table->time_to_die = ft_atoui(argv[2]);
	table->time_to_eat = ft_atoui(argv[3]);
	table->time_to_sleep = ft_atoui(argv[4]);
	table->meal_goal = 0;
	table->satisfaction = 0;
	table->active_meal_goal = (argc == 6);
	if (table->active_meal_goal == true)
		table->meal_goal = (int)ft_atoui(argv[5]);
	table->forks = malloc(sizeof(pthread_mutex_t) * table->n_philo);
	if (table->forks == NULL)
		return (EXIT_FAILURE);
	table->philosophers = malloc(sizeof(t_philo) * table->n_philo);
	if (table->philosophers == NULL)
		return (EXIT_FAILURE);
	if (pthread_mutex_init(&table->structlock, NULL)
		|| pthread_mutex_init(&table->write_stdout, NULL))
		return (EXIT_FAILURE);
	if (init_philosophers(table))
		return (EXIT_FAILURE);
	table->game_over = false;
	table->start_time = get_time();
	return (EXIT_SUCCESS);
}

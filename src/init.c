/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: simon <simon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 20:54:19 by svan-hoo          #+#    #+#             */
/*   Updated: 2024/06/11 23:46:40 by simon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

static int
	init_philosophers(
		t_simdata *data)
{
	int				i;
	t_philosopher	philo;

	i = 0;
	while (i++ < data->n_philo)
		if (pthread_mutex_init(&data->forks[i], NULL))
			return (errno);
	while (i-- > 0)
	{
		philo = data->philosophers[i];
		philo.id = i;
		philo.state = thinking;
		philo.n_meals = 0;
		philo.left_fork = &data->forks[i];
		philo.right_fork = &data->forks[(i + 1) % data->n_philo];
	}
	return (EXIT_SUCCESS);
}

int
	init(
		t_simdata *data,
		int argc,
		char **argv)
{
	data->n_philo = ft_atoi(argv[1]);
	data->time_to_die = atoui(argv[2]);
	data->time_to_eat = atoui(argv[3]);
	data->time_to_sleep = atoui(argv[4]);
	data->n_meals = -1;
	if (argc == 6)
		data->n_meals = ft_atoi(argv[5]);
	data->philosophers = malloc(sizeof(t_philosopher) * data->n_philo);
	if (data->philosophers == NULL)
		return (errno);
	data->forks = malloc(sizeof(pthread_mutex_t) * data->n_philo);
	if (data->forks == NULL)
		return (errno);
	if (pthread_mutex_init(&data->write_stdout, NULL)
		|| pthread_mutex_init(&data->read_stdin, NULL))
			return (errno);
	if (init_philosophers(data))
		return (errno);
	return (EXIT_SUCCESS);
}

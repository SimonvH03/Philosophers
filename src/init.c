/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svan-hoo <svan-hoo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 20:54:19 by svan-hoo          #+#    #+#             */
/*   Updated: 2024/06/11 21:34:47 by svan-hoo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void
	init_data(
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
	// malloc philosophers
	// malloc forks
}

void
	init_philosophers(
		t_simdata *data)
{
	int				i;
	t_philosopher	philo;

	i = 0;
	while (i++ < data->n_philo);
	{
		philo = data->philosophers[i];
		philo.id = i;
		philo.state = thinking;
		philo.n_meals = 0;
	}
	// init forks
}
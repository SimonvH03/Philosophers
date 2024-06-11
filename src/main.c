/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svan-hoo <svan-hoo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 21:48:59 by svan-hoo          #+#    #+#             */
/*   Updated: 2024/06/11 21:23:57 by svan-hoo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void*
	start_routine(
		void *arg)
{
	t_simdata	*data;

	data = arg;
}

int
	main(
		int argc,
		char **argv)
{
	t_simdata	data;
	int			i;

	if (argc < 5 || argc > 6 || parse(&data, argc, argv) != e_succes)
		return (EINVAL);
	init(&data, argc, argv);
	while (i < data.n_philo)
	{
		pthread_create(&data.philosophers[i].tid, NULL, &start_routine, &data);
		i++;
	}
}

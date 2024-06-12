/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svan-hoo <svan-hoo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 21:48:59 by svan-hoo          #+#    #+#             */
/*   Updated: 2024/06/12 19:34:20 by svan-hoo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void*
	routine(
		void *arg)
{
	t_simdata	*table;

	table = arg;
}

void*
	routine2(
		void *arg)
{
	t_philosopher	*table;

	table = arg;
}


int
	main(
		int argc,
		char **argv)
{
	t_simdata	table;

	if (argc < 5 || argc > 6 || parse(&table, argc, argv))
		return (EINVAL);
	if (init(&table, argc, argv))
		return (errno);
	pthread_create(&table.philosophers[0].tid, NULL, &routine, &table);
	return (EXIT_SUCCESS);
}

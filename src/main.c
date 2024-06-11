/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svan-hoo <svan-hoo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 21:48:59 by svan-hoo          #+#    #+#             */
/*   Updated: 2024/06/11 20:19:20 by svan-hoo         ###   ########.fr       */
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
	pthread_t	tid;
	int			i;

	if (argc < 6 || parse(&data, argc, argv) != e_succes)
		return (EINVAL);
	while ((unsigned int)i < data.n_philo)
	{
		pthread_create(&tid, NULL, &start_routine, &data);
		i++;
	}
}

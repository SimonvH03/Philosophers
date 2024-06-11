/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: simon <simon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 21:48:59 by svan-hoo          #+#    #+#             */
/*   Updated: 2024/06/11 23:48:14 by simon            ###   ########.fr       */
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

	if (argc < 5 || argc > 6 || parse(&data, argc, argv))
		return (EINVAL);
	if (init(&data, argc, argv))
		return (errno);
	return (EXIT_SUCCESS);
}

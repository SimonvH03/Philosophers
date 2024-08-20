/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_exit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svan-hoo <svan-hoo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 16:01:08 by svan-hoo          #+#    #+#             */
/*   Updated: 2024/08/20 20:35:29 by svan-hoo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

static void	clean_table(t_table *table)
{
	int	i;

	i = 0;
	printf("\e[31mcleaning table\n\e[0m");
	while (i < table->n_philo)
	{
		pthread_mutex_destroy(&table->forks[i]);
		pthread_mutex_destroy(&table->philosophers[i].lock);
		++i;
	}
	free(table->philosophers);
	free(table->forks);
	pthread_mutex_destroy(&table->lock);
	pthread_mutex_destroy(&table->write_stdout);
}

void	error_exit(t_table *table, char *err_message)
{
	if (err_message)
	{
		pthread_mutex_lock(&table->write_stdout);
		printf("philo: %s: %s\n", strerror(errno), err_message);
		pthread_mutex_unlock(&table->write_stdout);
	}
	clean_table(table);
	exit(errno);
}

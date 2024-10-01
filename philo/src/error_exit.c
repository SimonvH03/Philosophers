/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_exit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svan-hoo <svan-hoo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 16:01:08 by svan-hoo          #+#    #+#             */
/*   Updated: 2024/10/01 20:22:03 by svan-hoo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	clean_table(t_table *table)
{
	size_t	i;

	i = 0;
	while (i < table->n_philo)
	{
		pthread_mutex_destroy(&table->forks[i]);
		pthread_mutex_destroy(&table->philosophers[i].lock);
		pthread_mutex_destroy(&table->philosophers[i].lock);
		++i;
	}
	free(table->philosophers);
	free(table->forks);
	pthread_mutex_destroy(&table->lock);
	pthread_mutex_destroy(&table->write_stdout);
}

void	error_exit(int custom_errno, char *err_message)
{
	if (custom_errno)
	{
		errno = custom_errno;
	}
	if (errno || err_message)
	{
		printf("philo: %s: %s\n", strerror(errno), err_message);
	}
	exit(errno);
}

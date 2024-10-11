/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_exit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svan-hoo <svan-hoo@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 16:01:08 by svan-hoo          #+#    #+#             */
/*   Updated: 2024/10/11 02:07:26 by svan-hoo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	clean_table(t_table *table)
{
	size_t	i;

	i = 0;
	while (i < table->n_philo)
	{
		if (table->forks[i].is_initialised == true)
			pthread_mutex_destroy(&table->forks[i].mutex);
		if (table->philosophers[i].structlock.is_initialised == true)
			pthread_mutex_destroy(&table->philosophers[i].structlock.mutex);
		if (table->philosophers[i].is_live.is_initialised == true)
			pthread_mutex_destroy(&table->philosophers[i].is_live.mutex);
		++i;
	}
	if (table->philosophers)
		free(table->philosophers);
	if (table->forks)
		free(table->forks);
	if (table->write_stdout.is_initialised == true)
		pthread_mutex_destroy(&table->write_stdout.mutex);
	if (table->structlock.is_initialised == true)
		pthread_mutex_destroy(&table->structlock.mutex);
}

void	error_exit(const int custom_errno, const char *err_message)
{
	int	exit_code;

	exit_code = errno;
	if (custom_errno)
		errno = custom_errno;
	if (exit_code)
	{
		dup2(STDERR_FILENO, STDOUT_FILENO);
		printf("philo: %s", strerror(exit_code));
		if (err_message)
			printf(": %s", err_message);
		printf("\n");
	}
	exit(exit_code);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_exit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svan-hoo <svan-hoo@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 16:01:08 by svan-hoo          #+#    #+#             */
/*   Updated: 2024/09/19 20:51:57 by svan-hoo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

static size_t	ft_strlen(const char *c)
{
	size_t	i;

	i = 0;
	while (c[i])
		i++;
	return (i);
}

static void	ft_putstr_fd(char *s, int fd)
{
	write(fd, s, ft_strlen(s));
}

static void	error_message(char *err_message)
{
	ft_putstr_fd("philo: ", STDERR_FILENO);
	if (errno)
		ft_putstr_fd(strerror(errno), STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
	ft_putstr_fd(err_message, STDERR_FILENO);
	ft_putstr_fd("\n", STDERR_FILENO);
}

void	clean_table(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->n_philo)
	{
		pthread_mutex_destroy(&table->forks[i]);
		pthread_mutex_destroy(&table->philosophers[i].lock);
		++i;
	}
	free(table->philosophers);
	free(table->forks);
	pthread_mutex_destroy(&table->lock);
	pthread_mutex_destroy(&table->write_stderr);
	pthread_mutex_destroy(&table->write_stdout);
}

void	error_exit(int custom_errno, t_table *table, char *err_message)
{
	if (custom_errno)
	{
		errno = custom_errno;
	}
	if (err_message)
	{
		pthread_mutex_lock(&table->write_stderr);
		error_message(err_message);
		pthread_mutex_unlock(&table->write_stderr);
	}
	exit(errno);
}

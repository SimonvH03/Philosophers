/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   state_log.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svan-hoo <svan-hoo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 17:08:00 by svan-hoo          #+#    #+#             */
/*   Updated: 2024/08/19 19:29:59 by svan-hoo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

unsigned int	get_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

void	log_change(t_philo *philo, char *state_msg)
{
	const unsigned int	timestamp_in_ms = get_time() - philo->table->start_time;

	pthread_mutex_lock(&philo->table->write_stdout);
	printf("%d %d %s\n", timestamp_in_ms, philo->id, state_msg);
	pthread_mutex_unlock(&philo->table->write_stdout);
}

void	do_eat_sleep_think(t_philo *philo)
{
	pthread_mutex_lock(&philo->lock);
	pthread_mutex_lock(philo->left_fork);
	log_change(philo, "has taken a fork");
	pthread_mutex_lock(philo->right_fork);
	log_change(philo, "has taken a fork");
	philo->state = eating;
	philo->deadline = get_time() + philo->table->time_to_die;
	log_change(philo, "is eating");
	usleep(philo->table->time_to_eat);
	++philo->meal_count;
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
	philo->state = sleeping;
	log_change(philo, "is sleeping");
	usleep(philo->table->time_to_sleep);
	philo->state = thinking;
	log_change(philo, "is thinking");
	pthread_mutex_unlock(&philo->lock);
}

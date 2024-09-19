/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   state_log.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svan-hoo <svan-hoo@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 17:08:00 by svan-hoo          #+#    #+#             */
/*   Updated: 2024/09/19 21:05:25 by svan-hoo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

unsigned long	get_time(void)
{
	struct timeval	tv;
	unsigned long		time_in_ms;

	gettimeofday(&tv, NULL);
	time_in_ms = (tv.tv_sec * (unsigned long)1000) + (tv.tv_usec / (unsigned long)1000);
	return (time_in_ms);
}

void	log_change(t_philo *philo, char *state_msg)
{
	const unsigned int	timestamp_in_ms = get_time() - philo->table->start_time;

	pthread_mutex_lock(&philo->table->write_stdout);
	// printf("%d %d %s\n", timestamp_in_ms, philo->id, state_msg);
	pthread_mutex_unlock(&philo->table->write_stdout);
}

void	do_eat_sleep_think(t_philo *philo)
{
	pthread_mutex_lock(&philo->lock);
	pthread_mutex_lock(philo->left_fork);
	log_change(philo, "has taken a fork -1");
	pthread_mutex_lock(philo->right_fork);
	log_change(philo, "has taken a fork +1");
	philo->state = eating;
	philo->deadline = get_time() + philo->table->time_to_die;
	log_change(philo, "is eating");
	++philo->meal_count;
	pthread_mutex_unlock(&philo->lock);
	usleep(philo->table->time_to_eat * 1000);
	pthread_mutex_lock(&philo->lock);
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
	philo->state = sleeping;
	log_change(philo, "is sleeping");
	pthread_mutex_unlock(&philo->lock);
	usleep(philo->table->time_to_sleep * 1000);
	pthread_mutex_lock(&philo->lock);
	philo->state = thinking;
	log_change(philo, "is thinking");
	pthread_mutex_unlock(&philo->lock);
}

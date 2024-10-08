/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   state_log.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svan-hoo <svan-hoo@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 17:08:00 by svan-hoo          #+#    #+#             */
/*   Updated: 2024/10/08 02:03:05 by svan-hoo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

unsigned long	get_time(void)
{
	struct timeval	tv;
	unsigned long	time_in_ms;

	gettimeofday(&tv, NULL);
	time_in_ms = (tv.tv_sec * (unsigned long)1000)
		+ (tv.tv_usec / (unsigned long)1000);
	return (time_in_ms);
}

void	log_change(t_philo *philo, const char *state_msg)
{
	const unsigned int	timestamp_in_ms = get_time()
		- philo->r_table->start_time;

	pthread_mutex_lock(&philo->r_table->write_stdout);
	printf("%d %d %s\n", timestamp_in_ms, philo->id, state_msg);
	pthread_mutex_unlock(&philo->r_table->write_stdout);
}

void	do_think(t_philo *philo)
{
	pthread_mutex_lock(&philo->structlock);
	philo->state = thinking;
	log_change(philo, "is thinking");
	pthread_mutex_unlock(&philo->structlock);
}

void	do_eat(t_philo *philo)
{
	pthread_mutex_lock(philo->left_fork);
	if (safe_bool(&philo->r_table->structlock, &philo->r_table->game_over))
	{
		pthread_mutex_unlock(philo->left_fork);
		return ;
	}
	log_change(philo, "has taken a fork");
	if (philo->left_fork == philo->right_fork)
		return ((void)usleep(philo->r_table->time_to_die * 1000));
	pthread_mutex_lock(philo->right_fork);
	if (safe_bool(&philo->r_table->structlock, &philo->r_table->game_over))
	{
		pthread_mutex_unlock(philo->left_fork);
		pthread_mutex_unlock(philo->right_fork);
		return ;
	}
	log_change(philo, "has taken a fork");
	pthread_mutex_lock(&philo->structlock);
	philo->deadline = get_time() + philo->r_table->time_to_die;
	philo->state = eating;
	log_change(philo, "is eating");
	pthread_mutex_unlock(&philo->structlock);
	usleep(philo->r_table->time_to_eat * 1000);
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
}

void	do_sleep(t_philo *philo)
{
	pthread_mutex_lock(&philo->structlock);
	++philo->meal_count;
	philo->state = sleeping;
	log_change(philo, "is sleeping");
	pthread_mutex_unlock(&philo->structlock);
	usleep(philo->r_table->time_to_sleep * 1000);
}

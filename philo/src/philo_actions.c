/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_actions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svan-hoo <svan-hoo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 17:08:00 by svan-hoo          #+#    #+#             */
/*   Updated: 2024/10/10 19:22:26 by svan-hoo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

static int	take_forks(t_philo *philo)
{
	pthread_mutex_lock(philo->left_fork);
	if (safe_bool(&philo->r_table->structlock.mutex,
			&philo->r_table->game_over) == true)
	{
		pthread_mutex_unlock(philo->left_fork);
		return (EXIT_FAILURE);
	}
	log_change(philo, "has taken a fork");
	if (philo->left_fork == philo->right_fork)
	{
		pthread_mutex_lock(&philo->structlock.mutex);
		philo->state = satisfied;
		pthread_mutex_unlock(&philo->structlock.mutex);
		return (EXIT_FAILURE);
	}
	pthread_mutex_lock(philo->right_fork);
	if (safe_bool(&philo->r_table->structlock.mutex,
			&philo->r_table->game_over) == true)
	{
		pthread_mutex_unlock(philo->left_fork);
		pthread_mutex_unlock(philo->right_fork);
		return (EXIT_FAILURE);
	}
	log_change(philo, "has taken a fork");
	return (EXIT_SUCCESS);
}

void	do_think(t_philo *philo)
{
	pthread_mutex_lock(&philo->structlock.mutex);
	philo->state = thinking;
	log_change(philo, "is thinking");
	pthread_mutex_unlock(&philo->structlock.mutex);
}

void	do_eat(t_philo *philo)
{
	if (take_forks(philo) == EXIT_FAILURE)
		return ;
	pthread_mutex_lock(&philo->structlock.mutex);
	philo->deadline = get_time() + philo->r_table->time_to_die;
	philo->state = eating;
	log_change(philo, "is eating");
	pthread_mutex_unlock(&philo->structlock.mutex);
	usleep(philo->r_table->time_to_eat * 1000);
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
}

void	do_sleep(t_philo *philo)
{
	pthread_mutex_lock(&philo->structlock.mutex);
	++philo->meal_count;
	philo->state = sleeping;
	log_change(philo, "is sleeping");
	pthread_mutex_unlock(&philo->structlock.mutex);
	usleep(philo->r_table->time_to_sleep * 1000);
}

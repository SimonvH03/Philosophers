/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_actions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svan-hoo <svan-hoo@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 17:08:00 by svan-hoo          #+#    #+#             */
/*   Updated: 2024/11/08 17:54:41 by svan-hoo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

static int	take_forks(t_philo *philo)
{
	pthread_mutex_lock(philo->left_fork);
	if (safe_bool(&philo->r_table->structlock.mutex,
			&philo->r_table->simulation_running) == false)
	{
		pthread_mutex_unlock(philo->left_fork);
		return (EXIT_FAILURE);
	}
	log_change(philo, forking);
	if (philo->left_fork == philo->right_fork)
	{
		pthread_mutex_unlock(philo->left_fork);
		return (EXIT_FAILURE);
	}
	pthread_mutex_lock(philo->right_fork);
	if (safe_bool(&philo->r_table->structlock.mutex,
			&philo->r_table->simulation_running) == false)
	{
		pthread_mutex_unlock(philo->left_fork);
		pthread_mutex_unlock(philo->right_fork);
		return (EXIT_FAILURE);
	}
	log_change(philo, forking);
	return (EXIT_SUCCESS);
}

void	do_think(t_philo *philo)
{
	log_change(philo, thinking);
}

void	do_eat(t_philo *philo)
{
	if (take_forks(philo) == EXIT_FAILURE)
	{
		pthread_mutex_lock(&philo->structlock.mutex);
		philo->state = dead;
		pthread_mutex_unlock(&philo->structlock.mutex);
		return ;
	}
	pthread_mutex_lock(&philo->structlock.mutex);
	philo->deadline = get_time() + philo->r_table->time_to_die;
	++philo->meal_count;
	if (philo->r_table->active_meal_goal == true
		&& philo->meal_count == philo->r_table->meal_goal)
	{
		philo->state = satisfied;
		pthread_mutex_lock(&philo->r_table->structlock.mutex);
		++philo->r_table->satisfaction;
		pthread_mutex_unlock(&philo->r_table->structlock.mutex);
	}
	log_change(philo, eating);
	pthread_mutex_unlock(&philo->structlock.mutex);
	usleep(philo->r_table->time_to_eat * 1000);
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
}

void	do_sleep(t_philo *philo)
{
	log_change(philo, sleeping);
	usleep(philo->r_table->time_to_sleep * 1000);
}

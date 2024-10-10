/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   log_change.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svan-hoo <svan-hoo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 17:08:00 by svan-hoo          #+#    #+#             */
/*   Updated: 2024/10/10 18:41:34 by svan-hoo         ###   ########.fr       */
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

	pthread_mutex_lock(&philo->r_table->write_stdout.mutex);
	printf("%d %d %s\n", timestamp_in_ms, philo->id, state_msg);
	pthread_mutex_unlock(&philo->r_table->write_stdout.mutex);
}

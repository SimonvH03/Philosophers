/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   log_change.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svan-hoo <svan-hoo@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 17:08:00 by svan-hoo          #+#    #+#             */
/*   Updated: 2024/11/08 16:23:09 by svan-hoo         ###   ########.fr       */
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

void	log_change(t_philo *philo, const t_state state)
{
	static char			*log_messages[6]
		= {"is thinking", "has taken a fork",
		"is eating", "is sleeping", "died"};
	const unsigned int	timestamp_in_ms = get_time()
		- philo->r_table->start_time;

	// if (state != thinking)
	// 	return ;
	pthread_mutex_lock(&philo->r_table->write_stdout.mutex);
	// if (philo->id % 2 == 0)
	// 	printf("\t\t");
	// else
	// 	printf(" ");
	printf("%d %d %s\n", timestamp_in_ms, philo->id, log_messages[state]);
	pthread_mutex_unlock(&philo->r_table->write_stdout.mutex);
	// if (philo->id == 200 && state == thinking)
	// 	printf("\t\t%d %d %s\n", timestamp_in_ms, philo->id, log_messages[state]);
}

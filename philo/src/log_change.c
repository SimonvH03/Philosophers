/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   log_change.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svan-hoo <svan-hoo@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 17:08:00 by svan-hoo          #+#    #+#             */
/*   Updated: 2024/11/08 16:25:40 by svan-hoo         ###   ########.fr       */
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

	pthread_mutex_lock(&philo->r_table->write_stdout.mutex);
	printf("%d %d %s\n", timestamp_in_ms, philo->id, log_messages[state]);
	pthread_mutex_unlock(&philo->r_table->write_stdout.mutex);
}

void	ft_sleep(t_philo *philo, unsigned long time_in_ms)
{
	unsigned long	start_time;
	int				i;

	start_time = get_time();
	while (get_time() - start_time < time_in_ms
		&& safe_bool(&philo->r_table->structlock.mutex,
			&philo->r_table->simulation_running) == true)
	{
		i = 0;
		while (get_time() - start_time < time_in_ms && i++ < 100)
			usleep(100);
	}
}

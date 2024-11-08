/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   safe_read.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svan-hoo <svan-hoo@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/06 03:13:26 by svan-hoo          #+#    #+#             */
/*   Updated: 2024/11/08 16:54:30 by svan-hoo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

bool	safe_bool(pthread_mutex_t *lock, const bool *read)
{
	bool	safe_copy;

	pthread_mutex_lock(lock);
	safe_copy = *read;
	pthread_mutex_unlock(lock);
	return (safe_copy);
}

unsigned int	safe_uint(pthread_mutex_t *lock, const unsigned int *read)
{
	unsigned int	safe_copy;

	pthread_mutex_lock(lock);
	safe_copy = *read;
	pthread_mutex_unlock(lock);
	return (safe_copy);
}

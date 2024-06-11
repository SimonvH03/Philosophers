/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: simon <simon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 00:00:32 by simon             #+#    #+#             */
/*   Updated: 2024/06/12 00:05:27 by simon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int
	ft_isdigit(
		char c)
{
	if (c < '0' || c > '9')
		return (false);
	return (true);
}

unsigned int
	ft_atoui(
		const char *str)
{
	unsigned int	n;
	int				i;

	i = 0;
	if (str == NULL)
		return (errno);
	n = 0;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (errno);
		n *= 10;
		n += str[i] - '0';
		i++;
	}
	return (n);
}

int
	ft_atoi(
	const char *str)
{
	int	n;
	int	sign;
	int	i;

	if (str == NULL)
		return (errno);
	n = 0;
	sign = 1;
	i = 0;
	if (str[i] == '-')
	{
		sign = -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		n *= 10;
		n += str[i] - '0';
		i++;
	}
	return (n * sign);
}

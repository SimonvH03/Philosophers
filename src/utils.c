/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svan-hoo <svan-hoo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 17:13:16 by svan-hoo          #+#    #+#             */
/*   Updated: 2024/08/19 17:57:28 by svan-hoo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

static int	ft_strncmp(const char *a, const char *b, size_t n)
{
	const unsigned char	*uca = (unsigned char *)a;
	const unsigned char	*ucb = (unsigned char *)b;

	while (n-- && (*uca || *ucb))
		if (*uca++ != *ucb++)
			return (*(uca - 1) - *(ucb - 1));
	return (EXIT_SUCCESS);
}

static int	ft_isdigit(char c)
{
	if (c < '0' || c > '9')
		return (false);
	return (true);
}

unsigned int	ft_atoui(const char *str)
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

short	ft_aisui(const char *str)
{
	int	i;

	if (str == NULL)
		return (errno);
	i = 0;
	while (i < 11 && ft_isdigit(str[i]))
		i++;
	if (i < 1 || i > 10)
		return (false);
	if (i == 10 && ft_strncmp(str, "4294967295", 10) > 0)
		return (false);
	return (true);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: simon <simon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 18:49:19 by svan-hoo          #+#    #+#             */
/*   Updated: 2024/06/11 23:27:15 by simon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

static int
	ft_isdigit(
		char c)
{
	if (c < '0' || c > '9')
		return (false);
	return (true);
}

static int
	ft_strncmp(
		const char *a,
		const char *b,
		size_t n)
{
	const unsigned char	*uca = (unsigned char *)a;
	const unsigned char	*ucb = (unsigned char *)b;

	while (n-- && (*uca || *ucb))
		if (*uca++ != *ucb++)
			return (*(uca - 1) - *(ucb - 1));
	return (EXIT_SUCCESS);
}

static int
	aisi(
		const char *str)
{
	int	i;

	if (str == NULL)
		return (errno);
	i = 0;
	if (str[i] == '-')
		i++;
	while (i < 12 && ft_isdigit(str[i]))
		i++;
	if (i < 1 || i > 11)
		return (false);
	if (i == 10 && ft_strncmp(str, "2147483647", 10) > 0
		|| i == 11 && ft_strncmp(str, "-2147483648", 11) > 0)
		return (false);
	return (true);
}

static int
	aisui(
		const char *str)
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

int
	parse(
		t_simdata *data,
		int argc,
		char **argv)
{
	int	i;

	i = 0;
	if (argv == NULL)
		return (errno);
	if (!aisi(argv[i++]))
		return (EXIT_FAILURE);
	while (i < argc - 1)
		if (!aisui(argv[i++]))
			return (EXIT_FAILURE);
	if (!aisi(argv[i]))
		return (EXIT_FAILURE);
	if (argv[0][0] == '-' || argv[i][0] == '-')
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

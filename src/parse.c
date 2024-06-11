/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svan-hoo <svan-hoo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 18:49:19 by svan-hoo          #+#    #+#             */
/*   Updated: 2024/06/11 20:20:17 by svan-hoo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

static int
	ft_isdigit(
		char c)
{
	if (c < '0' || c > '9')
		return (e_false);
	return (e_true);
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
	return (e_succes);
}

static int
	aisui(
		const char *str)
{
	int	i;

	if (str == NULL)
		return (e_error);
	i = 0;
	while (i < 11 && ft_isdigit(str[i]))
		i++;
	if (i < 1 || i > 10)
		return (e_false);
	if (i == 10 && ft_strncmp(str, "4294967295", 10) >= 0)
		return (e_false);
	return (e_true);
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
		return (e_error);
	while (i < argc)
		if (!aisui(argv[i++]))
			return (e_failure);
	data->n_philo = atoui(argv[1]);
	data->time_to_die = atoui(argv[2]);
	data->time_to_eat = atoui(argv[3]);
	data->time_to_sleep = atoui(argv[4]);
	if (argc == 6)
		data->n_meals = atoui(argv[5]);
	return (e_succes);
}

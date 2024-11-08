/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svan-hoo <svan-hoo@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 00:12:41 by simon             #+#    #+#             */
/*   Updated: 2024/11/08 17:01:10 by svan-hoo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

unsigned int	ft_atoui(const char *str)
{
	unsigned int	n;
	int				i;

	i = 0;
	n = 0;
	while (str && str[i])
	{
		n *= 10;
		n += str[i] - '0';
		i++;
	}
	return (n);
}

void	set_table(t_table *table, const int argc, const char **argv)
{
	table->forks = NULL;
	table->philosophers = NULL;
	table->n_philo = ft_atoui(argv[1]);
	table->time_to_die = ft_atoui(argv[2]);
	table->time_to_eat = ft_atoui(argv[3]);
	table->time_to_sleep = ft_atoui(argv[4]);
	table->meal_goal = 0;
	table->satisfaction = 0;
	table->active_meal_goal = (argc == 6);
	if (table->active_meal_goal == true)
		table->meal_goal = (int)ft_atoui(argv[5]);
	table->simulation_running = true;
}

static int	ft_strncmp(const char *a, const char *b, size_t n)
{
	const unsigned char	*uca = (unsigned char *)a;
	const unsigned char	*ucb = (unsigned char *)b;

	while (n-- && (*uca || *ucb))
		if (*uca++ != *ucb++)
			return (*(uca - 1) - *(ucb - 1));
	return (EXIT_SUCCESS);
}

static short	ft_aisui(const char *str)
{
	int	i;

	if (str == NULL)
		return (false);
	i = 0;
	while (str[i] && i < 11)
	{
		if (str[i] < '0' || str[i] > '9')
			return (false);
		i++;
	}
	if (i < 1 || i > 10)
		return (false);
	if (i == 10 && ft_strncmp(str, "4294967295", 10) > 0)
		return (false);
	return (true);
}

int	parse(const int argc, const char **argv)
{
	int	i;

	if (argv == NULL)
		return (EXIT_FAILURE);
	i = 1;
	if (ft_aisui(argv[i++]) == false)
		return (EXIT_FAILURE);
	while (i < argc - 1)
		if (ft_aisui(argv[i++]) == false)
			return (EXIT_FAILURE);
	if (ft_aisui(argv[i]) == false)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

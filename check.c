/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: makboga <makboga@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/24 17:29:33 by makboga           #+#    #+#             */
/*   Updated: 2025/10/27 11:43:53 by makboga          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	skip_spaces(char p)
{
	if (p == ' ' || p == '\t' || p == '\n' || p == '\r' || p == '\v'
		|| p == '\f')
		return (1);
	return (0);
}

static int	mini_latoi(char *arg, int *j, t_parse *p)
{
	unsigned int	digit;

	while (arg[*j] && !skip_spaces(arg[*j]))
	{
		if (arg[*j] < '0' || arg[*j] > '9')
			return (-1);
		if (p->first_digit == 1)
		{
			if (arg[*j] == '0' && arg[*j + 1] == '\0')
				return (-1);
			p->first_digit = 0;
		}
		digit = arg[*j] - '0';
		if (p->temp > (long)(UINT_MAX / 10) || (p->temp == (long)(UINT_MAX / 10)
			&& digit > UINT_MAX % 10))
			p->flag = 1;
		if (p->flag == 0)
			p->temp = p->temp * 10 + digit;
		(*j)++;
	}
	while (arg[*j] && skip_spaces(arg[*j]))
		(*j)++;
	if (arg[*j] != '\0')
		return (-1);
	return (0);
}

int	check(int ac, char **av)
{
	int		i;
	int		j;
	t_parse	p;

	i = 1;
	while (i < ac)
	{
		j = 0;
		p.temp = 0;
		p.first_digit = 1;
		p.flag = 0;
		while (skip_spaces(av[i][j]))
			j++;
		if (av[i][j] == '\0')
			return (0);
		if (mini_latoi(av[i], &j, &p) == -1)
			return (-1);
		if (p.flag == 1)
			return (-1);
		i++;
	}
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: makboga <makboga@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/24 17:36:58 by makboga           #+#    #+#             */
/*   Updated: 2025/10/24 17:36:58 by makboga          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	start_routine(t_program *program)
{
	int			i;
	pthread_t	monitor;

	i = 0;
	while (i < program->num_of_philos)
	{
		if (pthread_create(&program->philos[i].thread, NULL, philo_routine,
				&program->philos[i]) != 0)
			return (1);
		i++;
	}
	if (pthread_create(&monitor, NULL, monitor_routine, program) != 0)
		return (1);
	i = 0;
	while (i < program->num_of_philos)
	{
		if (pthread_join(program->philos[i].thread, NULL) != 0)
			return (1);
		i++;
	}
	if (pthread_join(monitor, NULL) != 0)
		return (1);
	return (0);
}

static int	start_simulation(t_program *program)
{
	int					i;
	unsigned long long	start_time;

	i = 0;
	start_time = get_time();
	program->start_time = start_time;
	while (i < program->num_of_philos)
	{
		program->philos[i].start_time = start_time;
		program->philos[i].last_meal = start_time;
		i++;
	}
	start_routine(program);
	return (0);
}

static int	inits(t_program *program)
{
	if (init_mutexes(program) != 0)
		return (1);
	if (init_philos(program) != 0)
		return (1);
	return (0);
}

int	main(int ac, char **av)
{
	t_program	program;

	if (ac < 5 || ac > 6)
	{
		printf("Error\n");
		return (1);
	}
	if (check(ac, av) != 0)
	{
		printf("Error\n");
		return (1);
	}
	init_args(&program, av);
	if (inits(&program) != 0)
	{
		printf("Error\n");
		return (1);
	}
	start_simulation(&program);
	destroy_all(&program);
	return (0);
}

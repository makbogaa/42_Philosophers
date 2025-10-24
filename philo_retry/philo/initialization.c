/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialization.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: makboga <makboga@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/24 17:36:54 by makboga           #+#    #+#             */
/*   Updated: 2025/10/24 17:36:54 by makboga          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init_args(t_program *program, char **av)
{
	program->num_of_philos = ft_atoui(av[1]);
	program->time_to_die = ft_atoui(av[2]);
	program->time_to_eat = ft_atoui(av[3]);
	program->time_to_sleep = ft_atoui(av[4]);
	if (av[5])
		program->num_times_to_eat = ft_atoui(av[5]);
	else
		program->num_times_to_eat = -1;
	program->dead_flag = 0;
}

int	init_mutexes(t_program *program)
{
	int	i;

	pthread_mutex_init(&program->dead_lock, NULL);
	pthread_mutex_init(&program->meal_lock, NULL);
	pthread_mutex_init(&program->write_lock, NULL);
	program->forks = malloc(sizeof(pthread_mutex_t) * program->num_of_philos);
	if (!program->forks)
		return (1);
	i = 0;
	while (i < program->num_of_philos)
	{
		pthread_mutex_init(&program->forks[i], NULL);
		i++;
	}
	return (0);
}

static	void	pick_up_forks(t_philo *philo)
{
	if (philo->id % 2 == 0)
	{
		philo->first_fork = philo->left_fork;
		philo->second_fork = philo->right_fork;
	}
	else
	{
		philo->first_fork = philo->right_fork;
		philo->second_fork = philo->left_fork;
	}
}

int	init_philos(t_program *program)
{
	int		i;
	t_philo	*philo;

	program->philos = malloc(sizeof(t_philo) * program->num_of_philos);
	if (!program->philos)
		return (1);
	i = 0;
	while (i < program->num_of_philos)
	{
		philo = &program->philos[i];
		philo->id = i + 1;
		philo->meals_eaten = 0;
		philo->eating = 0;
		philo->last_meal = 0;
		philo->program = program;
		philo->dead = &program->dead_flag;
		philo->dead_lock = &program->dead_lock;
		philo->meal_lock = &program->meal_lock;
		philo->write_lock = &program->write_lock;
		philo->right_fork = &program->forks[i];
		philo->left_fork = &program->forks[(i + 1) % program->num_of_philos];
		pick_up_forks(philo);
		i++;
	}
	return (0);
}

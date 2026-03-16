/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: makboga <makboga@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/24 17:37:02 by makboga           #+#    #+#             */
/*   Updated: 2025/10/27 14:33:58 by makboga          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	philo_is_dead(t_philo *philo)
{
	unsigned long long	time_last_meal;

	pthread_mutex_lock(philo->meal_lock);
	time_last_meal = get_time() - philo->last_meal;
	if (time_last_meal >= philo->program->time_to_die && philo->eating == 0)
	{
		pthread_mutex_lock(philo->dead_lock);
		if (*philo->dead == 0)
		{
			*philo->dead = 1;
			pthread_mutex_unlock(philo->dead_lock);
			pthread_mutex_lock(philo->write_lock);
			printf("%llu %d died\n", get_time() - philo->program->start_time,
				philo->id);
			pthread_mutex_unlock(philo->write_lock);
			pthread_mutex_unlock(philo->meal_lock);
			return (1);
		}
		pthread_mutex_unlock(philo->dead_lock);
	}
	pthread_mutex_unlock(philo->meal_lock);
	return (0);
}

static int	philo_ate(t_program *program)
{
	int	i;
	int	eat_count;

	if (program->num_times_to_eat == -1)
		return (0);
	eat_count = 0;
	i = 0;
	while (i < program->num_of_philos)
	{
		pthread_mutex_lock(&program->meal_lock);
		if (program->philos[i].meals_eaten >= program->num_times_to_eat)
			eat_count++;
		pthread_mutex_unlock(&program->meal_lock);
		i++;
	}
	if (eat_count == program->num_of_philos)
	{
		pthread_mutex_lock(&program->dead_lock);
		program->dead_flag = 1;
		pthread_mutex_unlock(&program->dead_lock);
		return (1);
	}
	return (0);
}

void	*monitor_routine(void *arg)
{
	t_program	*program;
	int			i;

	program = (t_program *)arg;
	ft_usleep(program->time_to_die / 2);
	while (1)
	{
		i = 0;
		while (i < program->num_of_philos)
		{
			if (philo_is_dead(&program->philos[i]))
				return (NULL);
			if (philo_ate(program))
				return (NULL);
			i++;
		}
		pthread_mutex_lock(&program->dead_lock);
		if (program->dead_flag != 0)
		{
			pthread_mutex_unlock(&program->dead_lock);
			return (NULL);
		}
		pthread_mutex_unlock(&program->dead_lock);
	}
	return (NULL);
}

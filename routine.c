/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: makboga <makboga@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/24 17:37:09 by makboga           #+#    #+#             */
/*   Updated: 2025/10/24 17:37:09 by makboga          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	print_status(t_philo *philo, char *msg)
{
	unsigned long long	time;

	pthread_mutex_lock(philo->dead_lock);
	if (*philo->dead == 0)
	{
		time = get_time() - philo->start_time;
		pthread_mutex_lock(philo->write_lock);
		printf("%llu %d %s\n", time, philo->id, msg);
		pthread_mutex_unlock(philo->write_lock);
	}
	pthread_mutex_unlock(philo->dead_lock);
}

static void	philo_eat(t_philo *philo)
{
	pthread_mutex_lock(philo->first_fork);
	print_status(philo, "has taken a fork");
	pthread_mutex_lock(philo->second_fork);
	print_status(philo, "has taken a fork");
	pthread_mutex_lock(philo->meal_lock);
	philo->eating = 1;
	philo->last_meal = get_time();
	philo->meals_eaten++;
	pthread_mutex_unlock(philo->meal_lock);
	print_status(philo, "is eating");
	ft_usleep(philo->program->time_to_eat);
	pthread_mutex_lock(philo->meal_lock);
	philo->eating = 0;
	pthread_mutex_unlock(philo->meal_lock);
	pthread_mutex_unlock(philo->second_fork);
	pthread_mutex_unlock(philo->first_fork);
}

static void	routine_three(t_philo *philo)
{
	if (philo->program->num_of_philos % 2 == 1)
	{
		if (philo->program->time_to_eat > philo->program->time_to_sleep)
			ft_usleep(philo->program->time_to_eat
				- philo->program->time_to_sleep + 1);
		else
			ft_usleep(1);
	}
}

static void	routine_two(t_philo *philo)
{
	while (1)
	{
		philo_eat(philo);
		pthread_mutex_lock(philo->meal_lock);
		if (philo->program->num_times_to_eat != -1
			&& philo->meals_eaten >= philo->program->num_times_to_eat)
		{
			pthread_mutex_unlock(philo->meal_lock);
			break ;
		}
		pthread_mutex_unlock(philo->meal_lock);
		print_status(philo, "is sleeping");
		ft_usleep(philo->program->time_to_sleep);
		routine_three(philo);
		print_status(philo, "is thinking");
		pthread_mutex_lock(philo->dead_lock);
		if (*philo->dead != 0)
		{
			pthread_mutex_unlock(philo->dead_lock);
			break ;
		}
		pthread_mutex_unlock(philo->dead_lock);
	}
}

void	*philo_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->program->num_of_philos == 1)
	{
		pthread_mutex_lock(philo->right_fork);
		print_status(philo, "has taken a fork");
		ft_usleep(philo->program->time_to_die + 1);
		pthread_mutex_unlock(philo->right_fork);
		return (NULL);
	}
	if (philo->id % 2 != 0)
		ft_usleep(philo->program->time_to_eat / 2);
	routine_two(philo);
	return (NULL);
}

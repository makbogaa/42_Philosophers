/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: makboga <makboga@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/24 17:37:12 by makboga           #+#    #+#             */
/*   Updated: 2025/10/24 17:37:12 by makboga          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

unsigned int	ft_atoui(const char *str)
{
	size_t			i;
	unsigned int	nb;

	i = 0;
	nb = 0;
	while (str[i] == ' ' || str[i] == '\f' || str[i] == '\n'
		|| str[i] == '\r' || str[i] == '\t' || str[i] == '\v')
	{
		i++;
	}
	if (str[i] == '+' || str[i] == '-')
		i++;
	while (str[i] >= '0' && str[i] <= '9')
	{
		nb = (nb * 10) + (str[i] - '0');
		i++;
	}
	return (nb);
}

unsigned long long	get_time_ms(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((unsigned long long)time.tv_sec * 1000ULL
		+ (unsigned long long)(time.tv_usec / 1000ULL));
}

unsigned long long	get_time(void)
{
	static unsigned long long	last;
	unsigned long long			now;

	last = 0;
	now = get_time_ms();
	if (now < last)
		now = last;
	last = now;
	return (now);
}

void	ft_usleep(unsigned long long time_ms)
{
	unsigned long long	start_time;
	unsigned long long	elapsed;
	unsigned long long	remaining;

	start_time = get_time();
	while (1)
	{
		elapsed = get_time() - start_time;
		if (elapsed >= time_ms)
			break ;
		remaining = time_ms - elapsed;
		if (remaining > 5)
			usleep(1000);
		else if (remaining > 1)
			usleep(300);
		else if (remaining > 0)
			usleep(100);
		else
			break ;
	}
}

void	destroy_all(t_program *program)
{
	int	i;
	int	num_philos;

	num_philos = program->num_of_philos;
	if (program->forks)
	{
		i = 0;
		while (i < num_philos)
		{
			pthread_mutex_destroy(&program->forks[i]);
			i++;
		}
		free(program->forks);
		program->forks = NULL;
	}
	pthread_mutex_destroy(&program->dead_lock);
	pthread_mutex_destroy(&program->meal_lock);
	pthread_mutex_destroy(&program->write_lock);
	if (program->philos)
	{
		free(program->philos);
		program->philos = NULL;
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: makboga <makboga@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/24 17:37:06 by makboga           #+#    #+#             */
/*   Updated: 2025/10/24 17:37:06 by makboga          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <pthread.h>
# include <stdbool.h>
# include <limits.h>
# include <sys/time.h>

typedef struct s_program	t_program;

typedef struct s_philo
{
	pthread_t			thread;
	int					id;
	int					eating;
	int					meals_eaten;
	unsigned long long	last_meal;
	unsigned long long	start_time;
	t_program			*program;
	pthread_mutex_t		*right_fork;
	pthread_mutex_t		*left_fork;
	pthread_mutex_t		*write_lock;
	pthread_mutex_t		*dead_lock;
	pthread_mutex_t		*meal_lock;
	pthread_mutex_t		*first_fork;
	pthread_mutex_t		*second_fork;
	int					*dead;
}						t_philo;

typedef struct s_program
{
	int					num_of_philos;
	unsigned long long	time_to_die;
	unsigned long long	time_to_eat;
	unsigned long long	time_to_sleep;
	int					num_times_to_eat;
	int					dead_flag;
	unsigned long long	start_time;
	pthread_mutex_t		*forks;
	pthread_mutex_t		dead_lock;
	pthread_mutex_t		meal_lock;
	pthread_mutex_t		write_lock;
	t_philo				*philos;
}						t_program;

typedef struct s_parse
{
	long	temp;
	int		flag;
	int		first_digit;
}			t_parse;

int					check(int ac, char **av);

void				init_args(t_program *program, char **av);
int					init_mutexes(t_program *program);
int					init_philos(t_program *program);

unsigned int		ft_atoui(const char *str);
unsigned long long	get_time(void);
void				ft_usleep(unsigned long long time_ms);

void				*philo_routine(void *arg);
void				*monitor_routine(void *arg);
void				destroy_all(t_program *program);

#endif
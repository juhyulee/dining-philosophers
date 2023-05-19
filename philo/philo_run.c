/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   3.c                                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juhyulee <juhyulee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/10 19:50:33 by juhyulee          #+#    #+#             */
/*   Updated: 2023/05/15 14:02:00 by juhyulee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header/philo.h"

void	*philosopher(t_philo *philo)
{
	long long		difftime;
	struct timeval	now;

	if (philo->id % 2 == 0)
		usleep(philo->stat->time_to_eat * 500);
	while (1)
	{
		if (check_philo_died(philo))
			return (NULL);
		if (!philo_eating(philo))
			return (NULL);
		philo_sleep(philo);
		if (check_philo_died(philo))
			return (NULL);
		if (!philo_sleeping(philo))
			return (NULL);
		gettimeofday(&now, NULL);
		ft_sleep(tv_to_ms(now), philo->stat->time_to_sleep);
		if (check_philo_died(philo))
			return (NULL);
		difftime = get_diff_time(tv_to_ms(philo->stat->starttime));
		printf("%5lld %lld is thinking\n", difftime, philo->id);
	}
	return (NULL);
}

void	init_input(t_status *stat, char **av)
{
	stat->num = ft_atoi(av[1]);
	stat->time_to_die = ft_atoi(av[2]);
	stat->time_to_eat = ft_atoi(av[3]);
	stat->time_to_sleep = ft_atoi(av[4]);
	if (av[5])
		stat->must_eat = ft_atoi(av[5]);
	else
		stat->must_eat = 0;
	gettimeofday(&stat->starttime, NULL);
}

t_philo	*init_philo(t_status *input)
{
	t_philo		*philo;
	long long	i;

	philo = malloc(sizeof(t_philo) * (input->num));
	i = 0;
	while (i < input->num)
	{
		philo[i].id = i + 1;
		philo[i].lfork = &input->forks[i];
		philo[i].rfork = &(input->forks[(i + 1) % (input->num)]);
		philo[i].eat_cnt = 0;
		philo[i].time_to_die = input->time_to_die;
		philo[i].last_meal = input->starttime;
		philo[i].stat = input;
		philo[i].died = 0;
		pthread_mutex_init(&(philo[i].state), NULL);
		i++;
	}
	return (philo);
}

void	philo_all_dead(t_philo *philo)
{
	int	i;

	i = 0;
	while (i < philo->stat->num)
	{
		pthread_mutex_lock(&philo[i].state);
		philo[i].died = 1;
		pthread_mutex_unlock(&philo[i].state);
		i++;
	}
}

int	ft_str_is_digit(char *str)
{
	while (*str)
	{
		if (*str < '0' || *str > '9')
			return (0);
		str++;
	}
	return (1);
}

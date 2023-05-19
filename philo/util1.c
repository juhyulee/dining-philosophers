/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   2.c                                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juhyulee <juhyulee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/10 19:50:28 by juhyulee          #+#    #+#             */
/*   Updated: 2023/05/15 15:39:57 by juhyulee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header/philo.h"

int	take_forks(t_philo *philo)
{
	struct timeval	now;

	pthread_mutex_lock(philo->lfork);
	if (check_philo_died(philo))
	{
		pthread_mutex_unlock(philo->lfork);
		return (1);
	}
	gettimeofday(&now, NULL);
	print_take_fork(philo);
	if (philo->stat->num == 1)
		return (1);
	pthread_mutex_lock(philo->rfork);
	if (check_philo_died(philo))
	{
		pthread_mutex_unlock(philo->lfork);
		pthread_mutex_unlock(philo->rfork);
		return (1);
	}
	gettimeofday(&now, NULL);
	printf("%5lld %lld has taken a fork\n", \
	get_diff_time(tv_to_ms(philo->stat->starttime)), philo->id);
	return (0);
}

void	sleep_philo(t_philo *philo)
{
	pthread_mutex_unlock(philo->lfork);
	pthread_mutex_unlock(philo->rfork);
}

void	ft_sleep(long long time, long long wait_time)
{
	struct timeval	now;
	long long		now_time;

	gettimeofday(&now, NULL);
	now_time = tv_to_ms(now);
	while (now_time - time < wait_time)
	{
		usleep(100);
		gettimeofday(&now, NULL);
		now_time = tv_to_ms(now);
	}
}

int	philo_eating(t_philo *philo)
{
	long long	difftime;

	difftime = get_diff_time(tv_to_ms(philo->stat->starttime));
	if (take_forks(philo))
		return (0);
	gettimeofday(&philo->last_meal, NULL);
	difftime = get_diff_time(tv_to_ms(philo->stat->starttime));
	printf("%5lld %lld is eating\n", difftime, philo->id);
	return (1);
}

void	philo_sleep(t_philo *philo)
{
	pthread_mutex_lock(&philo->state);
	philo->eat_cnt += 1;
	pthread_mutex_unlock(&philo->state);
	ft_sleep(tv_to_ms(philo->last_meal), philo->stat->time_to_eat);
	sleep_philo(philo);
}

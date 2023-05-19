/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   1.c                                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juhyulee <juhyulee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/10 19:51:09 by juhyulee          #+#    #+#             */
/*   Updated: 2023/05/15 14:04:35 by juhyulee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header/philo.h"

long long	tv_to_ms(struct timeval tv)
{
	long long	time;

	time = (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
	return (time);
}

long long	get_diff_time(long long tv)
{
	struct timeval	now;
	long long		time;

	gettimeofday(&now, NULL);
	time = tv_to_ms(now);
	return (time - tv);
}

long long	ft_atoi(const char *str)
{
	long long	ans;
	long long	sign;

	ans = 0;
	sign = 1;
	while ((9 <= *str && *str <= 13) || *str == ' ')
		str++;
	if (*str == '+' || *str == '-')
	{
		if (*str == '-')
			sign = -1;
		str++;
	}
	while ('0' <= *str && *str <= '9')
	{
		ans *= 10;
		ans += (*str - '0');
		str++;
	}
	return ((ans * sign));
}

pthread_mutex_t	*init_forks(t_status *stat)
{
	pthread_mutex_t	*forks;
	long long		i;

	forks = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * stat->num);
	if (!forks)
	{
		return (NULL);
	}
	i = 0;
	while (i < stat->num)
	{
		if (pthread_mutex_init(&forks[i], NULL) < 0)
		{
			free(forks);
			return (NULL);
		}
		i++;
	}
	return (forks);
}

int	check_philo_died(t_philo *philo)
{
	int	i;

	i = 0;
	pthread_mutex_lock(&(philo->state));
	i = philo->died;
	pthread_mutex_unlock(&(philo->state));
	return (i);
}

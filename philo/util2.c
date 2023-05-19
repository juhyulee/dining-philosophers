/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juhyulee <juhyulee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 13:48:35 by juhyulee          #+#    #+#             */
/*   Updated: 2023/05/18 20:03:20 by juhyulee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header/philo.h"

int	philo_sleeping(t_philo *philo)
{
	long long	difftime;

	difftime = get_diff_time(tv_to_ms(philo->stat->starttime));
	if (check_philo_died(philo))
		return (0);
	pthread_mutex_lock(&philo->stat->printer);
	difftime = get_diff_time(tv_to_ms(philo->stat->starttime));
	printf("%5lld %lld is sleeping\n", difftime, philo->id);
	pthread_mutex_unlock(&philo->stat->printer);
	return (1);
}

void	print_take_fork(t_philo *philo)
{
	pthread_mutex_lock(&philo->stat->printer);
	printf("%5lld %lld has taken a fork\n", \
	get_diff_time(tv_to_ms(philo->stat->starttime)), philo->id);
	pthread_mutex_unlock(&philo->stat->printer);
}

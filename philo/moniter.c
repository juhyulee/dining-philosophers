/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   4.c                                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juhyulee <juhyulee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/10 19:51:37 by juhyulee          #+#    #+#             */
/*   Updated: 2023/05/15 15:35:19 by juhyulee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header/philo.h"

int	check_error(int ac, char **av)
{
	int	i;

	i = 1;
	if (ac != 5 && ac != 6)
		return (0);
	if (ac == 0)
		return (0);
	while (av[i])
	{
		if (ft_atoi(av[i]) <= 0 || ft_str_is_digit(av[i]) == 0)
		{
			return (0);
		}
		i++;
	}
	return (1);
}

void	init_all(t_status *input, char **av)
{
	init_input(input, av);
	input->forks = init_forks(input);
	pthread_mutex_init(&input->printer, NULL);
}

void	print_died(t_philo *philo, t_status *input)
{
	pthread_mutex_lock(&philo->state);
	philo->died = 1;
	pthread_mutex_unlock(&philo->state);
	printf("%5lld %lld has died\n", \
	get_diff_time(tv_to_ms(input->starttime)), philo->id);
}

int	moniter_sub(t_status *input, t_philo *philo, int *flag)
{
	struct timeval	time;

	pthread_mutex_lock(&(philo->state));
	if (input->must_eat && philo->eat_cnt >= \
	input->must_eat && !(philo->died))
	{
		philo->died = 1;
		(*flag) += 1;
		if (*flag == input->num)
		{
			pthread_mutex_unlock(&philo->state);
			return (0);
		}
	}
	pthread_mutex_unlock(&(philo->state));
	gettimeofday(&time, NULL);
	if (tv_to_ms(time) - tv_to_ms(philo->last_meal) \
	>= philo->time_to_die && !(philo->died))
	{
		pthread_mutex_lock(&philo->stat->printer);
		print_died(philo, input);
		return (0);
	}
	return (1);
}

int	died_moniter(t_status *input, t_philo *philo)
{
	int	flag;
	int	i;

	flag = 0;
	while (1)
	{
		i = -1;
		while (++i < input->num)
		{
			if (!moniter_sub(input, &philo[i], &flag))
			{
				philo_all_dead(philo);
				return (0);
			}
		}
	}
	return (0);
}

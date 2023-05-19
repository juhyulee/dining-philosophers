/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juhyulee <juhyulee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/09 18:18:27 by juhyulee          #+#    #+#             */
/*   Updated: 2023/05/15 15:19:12 by juhyulee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header/philo.h"

void	free_philo(t_philo *philo)
{
	t_status	*stat;
	int			i;

	stat = philo->stat;
	i = 0;
	while (i < stat->num)
	{
		pthread_mutex_destroy(&stat->forks[i]);
		++i;
	}
	free(stat->forks);
	pthread_mutex_destroy(&philo->state);
}

int	main(int ac, char **av)
{
	t_status		input;
	t_philo			*philo;
	int				i;

	if (check_error(ac, av) != 1)
		return (0);
	init_all(&input, av);
	philo = init_philo(&input);
	i = -1;
	while (++i < input.num)
	{
		pthread_create(&(philo[i].pid), NULL, (void *)philosopher, &philo[i]);
		pthread_detach(philo[i].pid);
	}
	died_moniter(&input, philo);
	free_philo(philo);
	return (0);
}

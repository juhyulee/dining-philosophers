/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juhyulee <juhyulee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/04 17:18:55 by juhyulee          #+#    #+#             */
/*   Updated: 2023/05/15 15:40:33 by juhyulee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <pthread.h>
# include <unistd.h>
# include <sys/time.h>
# include <stdlib.h>

typedef struct s_status
{
	long long		num;
	long long		time_to_die;
	long long		time_to_eat;
	long long		time_to_sleep;
	long long		must_eat;
	pthread_mutex_t	printer;
	pthread_mutex_t	*forks;
	struct timeval	starttime;
}				t_status;

typedef struct s_philo
{
	long long		id;
	pthread_mutex_t	*lfork;
	pthread_mutex_t	*rfork;
	pthread_mutex_t	state;
	pthread_t		pid;
	long long		eat_cnt;
	long long		time_to_die;
	long long		died;
	struct timeval	last_meal;
	t_status		*stat;
}				t_philo;

int				check_philo_died(t_philo *philo);
pthread_mutex_t	*init_forks(t_status *stat);
long long		ft_atoi(const char *str);
long long		get_diff_time(long long tv);
long long		tv_to_ms(struct timeval tv);
void			philo_sleep(t_philo *philo);
int				philo_eating(t_philo *philo);
void			ft_sleep(long long time, long long wait_time);
void			sleep_philo(t_philo *philo);
int				take_forks(t_philo *philo);
int				ft_str_is_digit(char *str);
void			philo_all_dead(t_philo *philo);
t_philo			*init_philo(t_status *input);
void			init_input(t_status *stat, char **av);
void			*philosopher(t_philo *philo);
void			philo_sleep(t_philo *philo);
int				philo_eating(t_philo *philo);
void			ft_sleep(long long time, long long wait_time);
void			sleep_philo(t_philo *philo);
int				take_forks(t_philo *philo);
int				check_philo_died(t_philo *philo);
pthread_mutex_t	*init_forks(t_status *stat);
long long		ft_atoi(const char *str);
long long		get_diff_time(long long tv);
long long		tv_to_ms(struct timeval tv);
int				died_moniter(t_status *input, t_philo *philo);
int				moniter_sub(t_status *input, t_philo *philo, int *flag);
void			print_died(t_philo *philo, t_status *input);
void			init_all(t_status *input, char **av);
int				check_error(int ac, char **av);
int				philo_sleeping(t_philo *philo);
void			print_take_fork(t_philo *philo);

#endif

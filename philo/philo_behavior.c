/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_behavior.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: woosekim <woosekim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 19:52:56 by woosekim          #+#    #+#             */
/*   Updated: 2023/06/27 19:46:45 by woosekim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	in_action(t_philo *philo)
{
	int		remain_time;
	int		action_time;
	t_time	start_time;

	remain_time = philo->share->t_die - time_diff_calculator(philo->time);
	if (remain_time == 0)
		remain_time = 1;
	print_philo(philo);
	if (gettimeofday(&(start_time), NULL) == -1)
		return (1);
	action_time = select_action_time(philo);
	while (time_diff_calculator(start_time) < action_time)
	{
		usleep(T_UNIT * remain_time);
		if (time_diff_calculator(philo->time) > philo->share->t_die)
		{
			time_over_in_action(philo);
			return (1);
		}
	}
	return (0);
}

void	eat_spaghetti(t_philo *philo)
{
	int	fork;

	if (check_end_flag(philo->share))
		return ;
	fork = fork_grab(philo);
	if (fork == 2)
	{
		if (check_time_before_eat(philo))
			return ;
		pthread_mutex_lock(&(philo->status_lock));
		philo->status = EATING;
		pthread_mutex_unlock(&(philo->status_lock));
		if (in_action(philo))
			return ;
		pthread_mutex_lock(&(philo->n_eat_lock));
		if (philo->share->eat_flag == 1)
			philo->n_eat++;
		pthread_mutex_unlock(&(philo->n_eat_lock));
		fork_release(philo);
		sleep_philo(philo);
	}
}

void	sleep_philo(t_philo *philo)
{
	if (check_end_flag(philo->share))
		return ;
	pthread_mutex_lock(&(philo->status_lock));
	philo->status = SLEEPING;
	pthread_mutex_unlock(&(philo->status_lock));
	if (in_action(philo))
		return ;
	think_philo(philo);
}

void	*think_philo(void *philo_temp)
{
	t_philo	*philo;

	philo = (t_philo *)philo_temp;
	if (check_end_flag(philo->share))
		return (NULL);
	pthread_mutex_lock(&(philo->status_lock));
	philo->status = THINKING;
	pthread_mutex_unlock(&(philo->status_lock));
	print_philo(philo);
	eat_spaghetti(philo);
	return (NULL);
}

void	die_philo(t_philo *philo)
{
	pthread_mutex_lock(&(philo->status_lock));
	philo->status = DIE;
	pthread_mutex_unlock(&(philo->status_lock));
	print_philo(philo);
	pthread_mutex_lock(&(philo->share->end_lock));
	philo->share->end_flag = 1;
	pthread_mutex_unlock(&(philo->share->end_lock));
}

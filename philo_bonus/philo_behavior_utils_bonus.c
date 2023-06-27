/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_behavior_utils_bonus.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: woosekim <woosekim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 19:53:39 by woosekim          #+#    #+#             */
/*   Updated: 2023/06/27 19:37:36 by woosekim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	select_action_time(t_philo *philo)
{
	int	action_time;

	action_time = 0;
	if (philo->status == EATING)
	{
		action_time = philo->share->t_eat;
		if (gettimeofday(&(philo->time), NULL) == -1)
			return (1);
	}
	else if (philo->status == SLEEPING)
		action_time = philo->share->t_sleep;
	return (action_time);
}

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
			if (philo->status == EATING)
				fork_release(philo);
			die_philo(philo);
		}
	}
	return (0);
}

void	fork_grab(t_philo *philo)
{
	sem_wait(philo->share->fork_sem);
	philo->status = GRAB;
	print_philo(philo);
	if (philo->share->n_philo == 1)
		sem_post(philo->share->fork_sem);
	sem_wait(philo->share->fork_sem);
	print_philo(philo);
}

void	fork_release(t_philo *philo)
{
	sem_post(philo->share->fork_sem);
	sem_post(philo->share->fork_sem);
}

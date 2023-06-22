/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_behavior_utils_bonus.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: woosekim <woosekim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 19:53:39 by woosekim          #+#    #+#             */
/*   Updated: 2023/06/22 16:35:23 by woosekim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	select_action_time(t_philo *philo)
{
	int	action_time;

	action_time = 0;
	// pthread_mutex_lock(&(philo->status_lock));
	if (philo->status == EATING)
	{
		action_time = philo->share->t_eat;
		if (gettimeofday(&(philo->time), NULL) == -1)
			return (1);
	}
	else if (philo->status == SLEEPING)
		action_time = philo->share->t_sleep;
	// pthread_mutex_unlock(&(philo->status_lock));
	return (action_time);
}

void	time_over_in_action(t_philo *philo)
{
	// pthread_mutex_lock(&(philo->status_lock));
	// if (philo->status == EATING)
		// fork_release(philo);
	// pthread_mutex_unlock(&(philo->status_lock));
	die_philo(philo);
}

int	check_time_before_eat(t_philo *philo)
{
	int	elapsed_time;

	elapsed_time = time_diff_calculator(philo->time);
	if (elapsed_time == -1)
		return (1);
	if (elapsed_time > philo->share->t_die)
	{
		die_philo(philo);
		// fork_release(philo);
		return (1);
	}
	return (0);
}

int	fork_grab(t_philo *philo)
{
	int	fork;

	fork = 0;
	// pthread_mutex_lock(&(philo->share->fork[philo->index % philo->share->n_philo].lock));
	// pthread_mutex_lock(&(philo->status_lock));
	philo->status = GRAB;
	// pthread_mutex_unlock(&(philo->status_lock));
	// philo->share->fork[philo->index % philo->share->n_philo].in_use = 1;
	print_philo(philo);
	// if (philo->share->n_philo == 1)
	// {
	// 	pthread_mutex_unlock(&(philo->share->\
	// 					fork[philo->index % philo->share->n_philo].lock));
	// 	philo->share->fork[philo->index % philo->share->n_philo].in_use = 0;
	// 	return (fork);
	// }
	// pthread_mutex_lock(&(philo->share->fork[philo->index - 1].lock));
	// philo->share->fork[philo->index - 1].in_use = 1;
	print_philo(philo);
	// fork = philo->share->fork[philo->index % philo->share->n_philo].in_use + philo->share->fork[philo->index - 1].in_use;
	return (fork);
}

void	fork_release(t_philo *philo)
{
	if (philo->share->fork[philo->index % philo->share->n_philo].in_use)
	{
		philo->share->fork[philo->index % philo->share->n_philo].in_use = 0;
		// pthread_mutex_unlock(&(philo->share->fork[philo->index % philo->share->n_philo].lock));
	}
	if (philo->share->fork[philo->index - 1].in_use)
	{
		philo->share->fork[philo->index - 1].in_use = 0;
		// pthread_mutex_unlock(&(philo->share->fork[philo->index - 1].lock));
	}
}

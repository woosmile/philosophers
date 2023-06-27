/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_behavior_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: woosekim <woosekim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 19:52:56 by woosekim          #+#    #+#             */
/*   Updated: 2023/06/27 15:22:01 by woosekim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	eat_spaghetti(t_philo *philo)
{
	fork_grab(philo);
	if (check_time_before_eat(philo))
		return ;
	philo->status = EATING;
	if (in_action(philo))
		return ;
	if (philo->share->eat_flag)
	{
		philo->n_eat++;
		if (philo->n_eat == philo->share->n_eat)
			sem_wait(philo->share->eat_sem);
	}
	fork_release(philo);
	sleep_philo(philo);
}

void	sleep_philo(t_philo *philo)
{
	philo->status = SLEEPING;
	if (in_action(philo))
		return ;
	think_philo(philo);
}

void	*think_philo(t_philo *philo)
{
	philo->status = THINKING;
	print_philo(philo);
	eat_spaghetti(philo);
	return (NULL);
}

void	die_philo(t_philo *philo)
{
	philo->status = DIE;
	print_philo(philo);
}

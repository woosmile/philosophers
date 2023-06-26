/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_behavior_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: woosekim <woosekim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 19:52:56 by woosekim          #+#    #+#             */
/*   Updated: 2023/06/26 20:41:22 by woosekim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	in_action(t_philo *philo)
{
	int		remain_time;
	int		action_time;
	t_time	start_time;

	remain_time = philo->share->t_die - time_diff_calculator(philo->time);
	if (remain_time == 0)
		remain_time = 1;
	action_time = select_action_time(philo);
	print_philo(philo);
	if (gettimeofday(&(start_time), NULL) == -1)
		return (1);
	while (time_diff_calculator(start_time) < action_time)
	{
		usleep(T_UNIT * remain_time);
		if (time_diff_calculator(philo->time) > philo->share->t_die)
			die_philo(philo);
	}
	return (0);
}

void	eat_spaghetti(t_philo *philo)
{
	fork_grab(philo);
	if (check_time_before_eat(philo))
		return ;
	philo->status = EATING;
	if (in_action(philo))
		return ;
	if (philo->share->eat_flag == 1 && philo->n_eat < philo->share->n_eat)
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
	usleep(T_UNIT * 10);
	print_philo(philo);
	eat_spaghetti(philo);
	return (NULL);
}

void	die_philo(t_philo *philo)
{
	sem_wait(philo->die_lock);
	philo->status = DIE;
	print_philo(philo);
	sem_post(philo->die_lock);
}

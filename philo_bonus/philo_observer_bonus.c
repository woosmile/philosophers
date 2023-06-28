/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_observer_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: woosekim <woosekim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 19:51:04 by woosekim          #+#    #+#             */
/*   Updated: 2023/06/28 13:53:36 by woosekim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	*check_time_over(void *philo_temp)
{
	int		elapsed_time;
	t_philo	*philo;
	int		time_diff;

	philo = (t_philo *)philo_temp;
	usleep((T_UNIT * philo->share->n_philo) * 3);
	while (1)
	{
		elapsed_time = time_diff_calculator(philo->time);
		if (elapsed_time == -1)
			return (NULL);
		if (elapsed_time >= philo->share->t_die)
		{
			time_diff = time_diff_calculator(philo->share->time);
			sem_wait(philo->share->print_sem);
			printf("%d %d died\n", time_diff, philo->index);
			exit(2);
		}
		usleep(T_UNIT * 10);
	}
	return (NULL);
}

void	*eat_sem_in(void *share_temp)
{
	t_share	*share;

	share = (t_share *)share_temp;
	usleep((T_UNIT * share->n_philo) * 3);
	while (1)
	{
		sem_wait(share->eat_sem);
		if (gettimeofday(&(share->eat_sem_time), NULL) == -1)
			return (NULL);
		sem_post(share->eat_sem);
		usleep(T_UNIT * 10);
	}
	return (NULL);
}

void	*check_eat_sem_time(void *share_temp)
{
	t_share	*share;
	int		elapsed_time;

	share = (t_share *)share_temp;
	usleep((T_UNIT * share->n_philo) * 3);
	while (1)
	{
		elapsed_time = time_diff_calculator(share->eat_sem_time);
		if (elapsed_time == -1)
			break ;
		if (elapsed_time > 1)
			kill(0, SIGINT);
		usleep(T_UNIT * 10);
	}
	return (NULL);
}

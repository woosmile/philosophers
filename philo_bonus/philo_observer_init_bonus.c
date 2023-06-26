/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_observer_init_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: woosekim <woosekim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/16 16:35:40 by woosekim          #+#    #+#             */
/*   Updated: 2023/06/26 20:42:59 by woosekim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	init_check_eat_thread(t_share *share)
{
	if (pthread_create(&(share->eat_sem_in), NULL, eat_sem_in, share))
		return (1);
	if (pthread_create(&(share->check_eat_sem_time), NULL, check_eat_sem_time, share))
		return (1);
	return (0);
}

int	init_fork_wait_thread(t_philo *philo)
{
	if (pthread_create(&(philo->fork_wait), NULL, check_time_over, philo))
		return (1);
	return (0);
}

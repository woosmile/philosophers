/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_observer_init_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: woosekim <woosekim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/16 16:35:40 by woosekim          #+#    #+#             */
/*   Updated: 2023/06/28 13:28:05 by woosekim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	init_check_eat_thread(t_share *share)
{
	if (!share->eat_flag)
		return (0);
	if (pthread_create(&(share->eat_sem_in), NULL, eat_sem_in, share))
		return (1);
	usleep(T_UNIT * 10);
	if (pthread_create(&(share->check_eat_sem_time), NULL, \
						check_eat_sem_time, share))
		return (1);
	return (0);
}

int	join_check_eat_thread(t_share *share)
{
	if (!share->eat_flag)
		return (0);
	if (pthread_join(share->eat_sem_in, NULL))
		return (1);
	if (pthread_join(share->check_eat_sem_time, NULL))
		return (1);
	return (0);
}

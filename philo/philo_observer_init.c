/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_observer_init.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: woosekim <woosekim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/16 16:35:40 by woosekim          #+#    #+#             */
/*   Updated: 2023/06/21 13:07:44 by woosekim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_check_eat_thread(t_eat *eat, t_philo *philos, t_share *share)
{
	eat->rec = (int *)malloc(sizeof(int) * share->n_philo);
	memset(eat->rec, 0, share->n_philo * 4);
	if (!eat->rec)
		return (1);
	eat->philo = philos;
	eat->share = share;
	if (pthread_create(&(eat->thread), NULL, check_eat_done, eat))
		return (1);
	return (0);
}

int	init_check_time_thread(t_obs *obs, t_philo *philos, t_share *share)
{
	obs->philo = philos;
	obs->share = share;
	if (pthread_create(&(obs->thread), NULL, check_time_over, obs))
		return (1);
	return (0);
}

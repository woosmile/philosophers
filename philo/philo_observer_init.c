/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_observer_init.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: woosekim <woosekim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/16 16:35:40 by woosekim          #+#    #+#             */
/*   Updated: 2023/06/16 17:35:09 by woosekim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_observer(t_observer *obs, t_philo *philos, t_share *share)
{
	obs->eat_rec = (int *)malloc(sizeof(int) * share->n_philo);
	memset(obs->eat_rec, 0, share->n_philo * 4);
	if (!obs->eat_rec)
		return (1);
	obs->philo = philos;
	obs->share = share;
	if (pthread_create(&(obs->thread), NULL, philo_observer, obs))
		return (1);
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: woosekim <woosekim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/10 17:04:59 by woosekim          #+#    #+#             */
/*   Updated: 2023/06/10 19:30:07 by woosekim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_philo(t_philo *philos, t_share *share)
{
	philos = (t_philo *)malloc(sizeof(t_philo) * share->n_philo);
	if (pthread_create(philos[0].thread, NULL, test_thread, share))
		return (1);
	return (0);
}

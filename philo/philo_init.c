/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: woosekim <woosekim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/10 17:04:59 by woosekim          #+#    #+#             */
/*   Updated: 2023/06/12 21:35:36 by woosekim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_philo(t_philo *philos, t_share *share)
{
	int	id_p;

	id_p = 0;
	while (id_p < share->n_philo)
	{
		philos[id_p].index = id_p + 1;
		philos[id_p].status = THINK;
		philos[id_p].n_eat = share->n_eat;
		philos[id_p].share = share;
		if (gettimeofday(&(philos[id_p].time), NULL) == -1)
			return (1);
		if (pthread_create(&(philos[id_p].thread), NULL, print_philo, &philos[id_p]))
			return (1);
		if (pthread_join(philos[id_p].thread, NULL))
			return (1);
		id_p++;
	}
	return (0);
}

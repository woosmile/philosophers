/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: woosekim <woosekim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/10 17:04:59 by woosekim          #+#    #+#             */
/*   Updated: 2023/06/13 19:45:59 by woosekim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init_philo(t_philo *philos, t_share *share)
{
	int	id_p;

	id_p = 0;
	while (id_p < share->n_philo)
	{
		philos[id_p].index = id_p + 1;
		philos[id_p].status = THINK;
		philos[id_p].n_eat = share->n_eat;
		philos[id_p].share = share;
		id_p++;
	}
	start_philo(philos, share);
}

int	start_philo(t_philo *philos, t_share *share)
{
	int	id_p;
	int	even_odd;

	id_p = 0;
	even_odd = 0;
	while (id_p < share->n_philo)
	{
		if ((philos[id_p].index % 2) == even_odd)
		{
			if (gettimeofday(&(philos[id_p].time), NULL) == -1)
				return (1);
			if (pthread_create(&(philos[id_p].thread), NULL, eat_spaghetti, &philos[id_p]))
				return (1);
			if (pthread_join(philos[id_p].thread, NULL))
				return (1);
		}
		id_p++;
		if (id_p == share->n_philo && even_odd == 0)
		{
			id_p = 0;
			even_odd = 1;
			usleep(share->t_eat * 1000);
		}
	}
	return (0);
}

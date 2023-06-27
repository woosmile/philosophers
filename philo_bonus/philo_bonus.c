/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: woosekim <woosekim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 13:41:22 by woosekim          #+#    #+#             */
/*   Updated: 2023/06/27 16:04:06 by woosekim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	main(int ac, char **av)
{
	t_share		share;
	t_philo		*philos;

	if (ac < 2)
		return (1);
	if (sem_unlink_func())
		return (1);
	if (init_share(ac, av, &share))
		return (1);
	philos = (t_philo *)malloc(sizeof(t_philo) * share.n_philo);
	if (init_philo(philos, &share))
		return (1);
	if (init_check_eat_thread(&share))
		return (1);
	if (start_philo(philos, &share))
		return (1);
	wait_philo(&share);
	if (join_check_eat_thread(&share))
		return (1);
	return (0);
}

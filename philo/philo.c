/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: woosekim <woosekim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 14:06:13 by woosekim          #+#    #+#             */
/*   Updated: 2023/06/12 21:12:14 by woosekim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*print_philo(void *philo_temp)
{
	t_philo	*philo;
	double	time_gap;

	philo = (t_philo *)philo_temp;
	//pthread_mutex_lock(&(philo->share->print_lock));
	time_gap = (philo->time.tv_sec - philo->share->time.tv_sec) + \
				((philo->time.tv_usec - philo->share->time.tv_usec) / 1000000);
	time_gap = time_gap * 1000;
	printf("%d %d print thread\n", (int)time_gap, philo->index);
	usleep(100);
	if (gettimeofday(&(philo->time), NULL) == -1)
		return (NULL);
	//pthread_mutex_unlock(&(philo->share->print_lock));
	return (NULL);
}

int	main(int ac, char **av)
{
	t_share	share;
	t_philo	*philos;

	if (ac < 2)
		return (1);
	if (init_share(ac, av, &share))
		return (1);
	philos = (t_philo *)malloc(sizeof(t_philo) * share.n_philo);
	if (!philos)
		return (1);
	if (init_philo(philos, &share))
		return (1);
	return (0);
}

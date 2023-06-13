/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: woosekim <woosekim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 14:06:13 by woosekim          #+#    #+#             */
/*   Updated: 2023/06/13 19:50:50 by woosekim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*eat_spaghetti(void *philo_temp)
{
	t_philo	*philo;
	t_time	time;
	double	time_diff;
	double	time_usec_diff;

	philo = (t_philo *)philo_temp;
	if (gettimeofday(&(time), NULL) == -1)
		return (NULL);
	// pthread_mutex_lock(&(philo->share->print_lock));
	time_diff = (time.tv_sec - philo->time.tv_sec) * 1000;
	time_usec_diff = (time.tv_usec - philo->time.tv_usec) / 1000;
	time_diff = time_diff + time_usec_diff;
	if (time_diff + philo->share->t_eat > philo->share->t_die)
		philo->status = DIE;
	else
	{
		philo->status = EAT;
		usleep(philo->share->t_eat * 1000);
		time_diff = (time.tv_sec - philo->share->time.tv_sec) * 1000;
		time_usec_diff = (time.tv_usec - philo->share->time.tv_usec) / 1000;
		time_diff = time_diff + time_usec_diff;
		printf("%d %d is eating\n", (int)time_diff, philo->index);
	}
	// pthread_mutex_unlock(&(philo->share->print_lock));
	return (NULL);

}
/*
void	sleep()
{
	
}
*/
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
	init_philo(philos, &share);
	return (0);
}

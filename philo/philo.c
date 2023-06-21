/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: woosekim <woosekim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 14:06:13 by woosekim          #+#    #+#             */
/*   Updated: 2023/06/21 13:18:06 by woosekim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_func(t_share *share, t_philo *philos, t_eat *eat, t_obs *obs)
{
	if (init_philo_thread(philos, share))
		return (1);
	if (init_check_time_thread(obs, philos, share))
		return (1);
	if (share->eat_flag)
	{
		if (init_check_eat_thread(eat, philos, share))
			return (1);
	}
	return (0);
}

int	join_func(t_share *share, t_philo *philos, t_eat *eat, t_obs *obs)
{
	if (philo_thread_join(*share, philos))
		return (1);
	if (pthread_join(obs->thread, NULL))
		return (1);
	if (share->eat_flag)
	{
		if (pthread_join(eat->thread, NULL))
			return (1);
	}
	return (0);
}

int	main(int ac, char **av)
{
	t_share		share;
	t_philo		*philos;
	t_eat		eat;
	t_obs		obs;

	if (ac < 2)
		return (1);
	if (init_share(ac, av, &share))
		return (1);
	philos = (t_philo *)malloc(sizeof(t_philo) * share.n_philo);
	if (!philos)
		return (1);
	if (init_func(&share, philos, &eat, &obs))
		return (1);
	if (join_func(&share, philos, &eat, &obs))
		return (1);
	free(share.fork);
	free(philos);
	return (0);
}

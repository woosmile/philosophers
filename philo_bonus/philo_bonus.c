/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: woosekim <woosekim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 13:41:22 by woosekim          #+#    #+#             */
/*   Updated: 2023/06/22 20:43:07 by woosekim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	main(int ac, char **av)
{
	t_share		share;
	t_philo		*philos;
	// t_eat		eat;
	// t_obs		obs;
	pid_t			pid;
	int				id_p;
	int				even_odd;

	pid = 0;
	id_p = 0;
	even_odd = 0;
	if (ac < 2)
		return (1);
	if (init_share(ac, av, &share))
		return (1);
	philos = (t_philo *)malloc(sizeof(t_philo) * share.n_philo);
	init_philo(philos, &share);
	// generate philos
	while (id_p < share.n_philo)
	{
		// pid = fork();
		// if (pid == -1)
		// 	return (1);
		// else if (pid == 0)
		// {
		// 	if ((philos[id_p].index % 2) == even_odd)
		// 	{
		// 		if (gettimeofday(&(philos[id_p].time), NULL) == -1)
		// 			return (1);
		// 		think_philo(&philos[id_p]);
		// 	}
		// 	else
		// 		return (0);
		// }
		// id_p++;
		// if (id_p == share.n_philo && even_odd == 0)
		// {
		// 	id_p = 0;
		// 	even_odd = 1;
		// 	usleep(200);
		// }


		// if ((philos[id_p].index % 2) == even_odd)
		// {
		// 	pid = fork();
		// 	if (pid == -1)
		// 		return (1);
		// 	else if (pid == 0)
		// 	{
		// 	if (gettimeofday(&(philos[id_p].time), NULL) == -1)
		// 		return (1);
		// 	think_philo(&philos[id_p]);
		// }
		// else
		// 	return (0);
		// }
		// id_p++;
		// if (id_p == share.n_philo && even_odd == 0)
		// {
		// 	id_p = 0;
		// 	even_odd = 1;
		// 	usleep(200);
		// }

		pid = fork();
		if (pid == -1)
			return (1)
	}
	return (0);
}

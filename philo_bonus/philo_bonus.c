/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: woosekim <woosekim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 13:41:22 by woosekim          #+#    #+#             */
/*   Updated: 2023/06/23 19:21:25 by woosekim         ###   ########.fr       */
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
	int				status;

	pid = 0;
	id_p = 0;
	even_odd = 0;
	if (ac < 2)
		return (1);
	if (init_share(ac, av, &share))
		return (1);
	philos = (t_philo *)malloc(sizeof(t_philo) * share.n_philo);
	init_philo(philos, &share);
	// generate process
	
	share.print_sem = sem_open("print_sem", O_CREAT, 0644, 2);
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
		if ((philos[id_p].index % 2) == even_odd)
		{
			pid = fork();
			if (pid == -1)
				return (1);
			else if (pid == 0)
			{
				if (gettimeofday(&(philos[id_p].time), NULL) == -1)
					return (1);
				think_philo(&philos[id_p]);
			}
		}
		id_p++;
		if (id_p == share.n_philo && even_odd == 0)
		{
			id_p = 0;
			even_odd = 1;
			usleep(T_UNIT * share.n_philo);
		}
	}
	//join
	id_p = 0;
	while (id_p < share.n_philo)
	{
		waitpid(-1, &status, 0);
		if (WIFEXITED(status))
		{
			kill(0, SIGINT);
			sem_unlink("print_sem");
			sem_close(share.print_sem);
			return (0);
		}
		id_p++;
	}

	return (0);
}

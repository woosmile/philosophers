/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_init_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: woosekim <woosekim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/10 17:04:59 by woosekim          #+#    #+#             */
/*   Updated: 2023/06/26 20:46:27 by woosekim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	init_philo(t_philo *philos, t_share *share)
{
	int		id_p;
	char	**die_lock_name;

	id_p = 0;
	die_lock_name = init_die_lock_name(share->n_philo);
	if (!die_lock_name)
		return (1);
	while (id_p < share->n_philo)
	{
		philos[id_p].index = id_p + 1;
		philos[id_p].status = THINKING;
		philos[id_p].n_eat = 0;
		philos[id_p].share = share;
		philos[id_p].die_lock = sem_open(die_lock_name[id_p], O_CREAT, 0644, 1);
		id_p++;
	}
	free_double_ptr(die_lock_name);
	return (0);
}

int	philo_process_setup(t_philo *philos, int id_p)
{
	if (gettimeofday(&(philos[id_p].time), NULL) == -1)
		return (1);
	if (init_fork_wait_thread(&philos[id_p]))
		return (1);
	think_philo(&philos[id_p]);
	if (pthread_join(philos[id_p].fork_wait, NULL))
		return (1);
	return (0);
}

void	even_odd_change(t_share *share, int *even_odd, int *id_p)
{
	if (*id_p == share->n_philo && *even_odd == 0)
	{
		*id_p = 0;
		*even_odd = 1;
		usleep(T_UNIT * share->n_philo);
	}
}

int	start_philo(t_philo *philos, t_share *share)
{
	int	id_p;
	int	even_odd;
	int	pid;

	id_p = 0;
	even_odd = 0;
	while (id_p < share->n_philo)
	{
		if ((philos[id_p].index % 2) == even_odd)
		{
			pid = fork();
			if (pid == -1)
				return (1);
			else if (pid == 0)
			{
				if (philo_process_setup(philos, id_p))
					return (1);
			}
		}
		id_p++;
		even_odd_change(share, &even_odd, &id_p);
	}
	return (0);
}

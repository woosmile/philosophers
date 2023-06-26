/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: woosekim <woosekim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 13:41:22 by woosekim          #+#    #+#             */
/*   Updated: 2023/06/26 20:48:37 by woosekim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	sem_unlink_func(void)
{
	int		i;
	char	*wait_lock_num;

	i = 1;
	sem_unlink("print_sem");
	sem_unlink("fork_sem");
	sem_unlink("eat_sem");
	wait_lock_num = ft_itoa(i);
	if (!wait_lock_num)
		return (1);
	while (sem_unlink(wait_lock_num) == 0)
	{
		free(wait_lock_num);
		i++;
		wait_lock_num = ft_itoa(i);
		if (!wait_lock_num)
			return (1);
	}
	free(wait_lock_num);
	return (0);
}

char	**init_die_lock_name(int n_philo)
{
	int		i;
	char	*name;
	char	**name_set;

	i = 1;
	name_set = (char **)malloc(sizeof(char *) * (n_philo + 1));
	if (!name_set)
		return (NULL);
	while (i <= n_philo)
	{
		name = ft_itoa(i);
		if (!name)
			return (NULL);
		name_set[i - 1] = name;
		i++;
	}
	name_set[n_philo] = NULL;
	return (name_set);
}

void	wait_philo(t_share *share)
{
	int	id_p;
	int	status;

	id_p = 0;
	while (id_p < share->n_philo)
	{
		waitpid(0, &status, 0);
		if (WIFEXITED(status))
		{
			sem_unlink_func();
			sem_close(share->print_sem);
			sem_close(share->fork_sem);
			sem_close(share->eat_sem);
			kill(0, SIGINT);
		}
		id_p++;
	}
}

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
	if (share.eat_flag)
	{
		if (init_check_eat_thread(&share))
			return (1);
	}
	if (start_philo(philos, &share))
		return (1);
	wait_philo(&share);
	if (share.eat_flag)
	{
		if (pthread_join(share.eat_sem_in, NULL))
			return (1);
		if (pthread_join(share.check_eat_sem_time, NULL))
			return (1);
	}
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: woosekim <woosekim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 13:41:22 by woosekim          #+#    #+#             */
/*   Updated: 2023/06/21 18:01:21 by woosekim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	main(int ac, char **av)
{
	t_share		share;
	// t_philo		*philos;
	// t_eat		eat;
	// t_obs		obs;
	pid_t			pid_num;

	pid_num = -1;
	if (ac < 2)
		return (1);
	if (init_share(ac, av, &share))
		return (1);
	pid_num = fork();
	printf("pid : %d\n", pid_num);
	usleep(100);
	pid_num = fork();
	printf("pid : %d\n", pid_num);
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: woosekim <woosekim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 14:06:13 by woosekim          #+#    #+#             */
/*   Updated: 2023/06/09 20:03:47 by woosekim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int ac, char **av)
{
	t_share	share;
	//t_philo	*philos;

	if (!(ac == 5 || ac == 6))
		return (1);
	if (init_philo(ac, av, &share))
		return (1);
	printf("n_philo : %d | t_die : %d | t_eat : %d | t_sleep : %d | n_eat : %d | n_eat_flag : %d\n", 
			share.n_philo, share.t_die, share.t_eat, share.t_sleep, share.n_eat, share.n_eat_flag);
	return (0);
}

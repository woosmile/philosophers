/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: woosekim <woosekim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 14:06:20 by woosekim          #+#    #+#             */
/*   Updated: 2023/06/16 14:07:57 by woosekim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	free_double_ptr(char **ptr)
{
	int	i;

	if (ptr == NULL)
		return ;
	i = 0;
	while (ptr[i])
	{
		free(ptr[i]);
		i++;
	}
	free (ptr);
}

int	time_diff_calculator(t_time old)
{
	t_time	present;
	int		time_diff;

	if (gettimeofday(&(present), NULL) == -1)
		return (-1);
	time_diff = (present.tv_sec - old.tv_sec) * 1000 + \
				((present.tv_usec - old.tv_usec) / 1000);
	return (time_diff);
}

void	print_philo(t_philo *philo)
{
	int	time_diff;

	pthread_mutex_lock(&(philo->share->print_lock));
	if (!philo->share->die_flag)
	{
		time_diff = time_diff_calculator(philo->share->time);
		if (philo->status == EATING)
			printf("%d %d is eating\n", time_diff, philo->index);
		else if (philo->status == GRAB)
			printf("%d %d has taken a fork\n", time_diff, philo->index);
		else if (philo->status == SLEEPING)
			printf("%d %d is sleeping\n", time_diff, philo->index);
		else if (philo->status == THINKING)
			printf("%d %d is thinking\n", time_diff, philo->index);
		else if (philo->status == DIE)
		{
			printf("%d %d died\n", time_diff, philo->index);
			philo->share->die_flag = 1;
		}
	}
	pthread_mutex_unlock(&(philo->share->print_lock));
}

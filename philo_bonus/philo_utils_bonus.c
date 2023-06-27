/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: woosekim <woosekim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 14:06:20 by woosekim          #+#    #+#             */
/*   Updated: 2023/06/27 16:13:53 by woosekim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

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

	sem_wait(philo->share->print_sem);
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
		exit(2);
	}
	sem_post(philo->share->print_sem);
}

void	sem_unlink_func(void)
{
	sem_unlink("print_sem");
	sem_unlink("fork_sem");
	sem_unlink("eat_sem");
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
			kill(0, SIGINT);
		id_p++;
	}
}

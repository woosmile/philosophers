/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: woosekim <woosekim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 14:06:13 by woosekim          #+#    #+#             */
/*   Updated: 2023/06/16 17:50:37 by woosekim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_time_before_eat(t_philo *philo)
{
	int	elapsed_time;

	elapsed_time = time_diff_calculator(philo->time);
	if (elapsed_time == -1)
		return (1);
	if (elapsed_time > philo->share->t_die)
	{
		philo->status = DIE;
		print_philo(philo);
		pthread_mutex_unlock(&(philo->share->fork[philo->index - 1].lock));
		if (philo->index == 1)
			pthread_mutex_unlock(&(philo->share->fork[philo->share->n_philo - 1].lock));
		else
			pthread_mutex_unlock(&(philo->share->fork[philo->index - 2].lock));
		return (1);
	}
	return (0);
}

int	in_action(t_philo *philo)
{
	int		remain_time;
	int		action_time;
	t_time	start_time;

	remain_time = philo->share->t_die - time_diff_calculator(philo->time);
	if (remain_time == 0)
		remain_time = 1;
	if (philo->status == EATING)
	{
		action_time = philo->share->t_eat;
		if (gettimeofday(&(philo->time), NULL) == -1)
			return (1);
	}
	else if (philo->status == SLEEPING)
		action_time = philo->share->t_sleep;
	print_philo(philo);
	if (gettimeofday(&(start_time), NULL) == -1)
		return (1);
	while (time_diff_calculator(start_time) < action_time)
	{
		usleep(T_UNIT * remain_time);
		if (time_diff_calculator(philo->time) > philo->share->t_die)
		{
			if (philo->status == EATING)
			{
				pthread_mutex_unlock(&(philo->share->fork[philo->index - 1].lock));
				if (philo->index == 1)
					pthread_mutex_unlock(&(philo->share->fork[philo->share->n_philo - 1].lock));
				else
					pthread_mutex_unlock(&(philo->share->fork[philo->index - 2].lock));
			}
			philo->status = DIE;
			print_philo(philo);
			return (1);
		}
	}
	return (0);
}

void	eat_spaghetti(t_philo *philo)
{
	int	fork;

	pthread_mutex_lock(&(philo->share->fork[philo->index - 1].lock));
	philo->status = GRAB;
	print_philo(philo);
	if (philo->index == 1)
		pthread_mutex_lock(&(philo->share->fork[philo->share->n_philo - 1].lock));
	else
		pthread_mutex_lock(&(philo->share->fork[philo->index - 2].lock));
	print_philo(philo);
	fork = 0;
	philo->share->fork[philo->index - 1].in_use = 1;
	if (philo->index == 1)
		philo->share->fork[philo->share->n_philo - 1].in_use = 1;
	else
		philo->share->fork[philo->index - 2].in_use = 1;
	fork = fork + philo->share->fork[philo->index - 1].in_use;
	if (philo->index == 1)
		fork = fork + philo->share->fork[philo->share->n_philo - 1].in_use;
	else
		fork = fork + philo->share->fork[philo->index - 2].in_use;
	if (philo->share->die_flag || philo->share->n_eat_done)
		return ;
	if (fork == 2)
	{
		if (check_time_before_eat(philo))
			return ;
		philo->status = EATING;
		if (in_action(philo))
			return ;
		pthread_mutex_lock(&(philo->share->n_eat_lock));
		if (philo->share->n_eat_flag == 1)
			philo->n_eat++;
		pthread_mutex_unlock(&(philo->share->n_eat_lock));
		philo->share->fork[philo->index - 1].in_use = 0;
		if (philo->index == 1)
			philo->share->fork[philo->share->n_philo - 1].in_use = 0;
		else
			philo->share->fork[philo->index - 2].in_use = 0;
		pthread_mutex_unlock(&(philo->share->fork[philo->index - 1].lock));
		if (philo->index == 1)
			pthread_mutex_unlock(&(philo->share->fork[philo->share->n_philo - 1].lock));
		else
			pthread_mutex_unlock(&(philo->share->fork[philo->index - 2].lock));
		sleep_philo(philo);
	}
}

void	sleep_philo(t_philo *philo)
{
	if (philo->share->die_flag || philo->share->n_eat_done)
		return ;
	philo->status = SLEEPING;
	if (in_action(philo))
		return ;
	think_philo(philo);
}

void	*think_philo(void *philo_temp)
{
	t_philo	*philo;

	philo = (t_philo *)philo_temp;
	if (philo->share->die_flag || philo->share->n_eat_done)
		return (NULL);
	philo->status = THINKING;
	print_philo(philo);
	eat_spaghetti(philo);
	return (NULL);
}

void	*philo_observer(void *obs_temp)
{
	t_observer	*obs;
	int			id_p;
	int			id_r;
	int			all_eat;

	obs = (t_observer *)obs_temp;
	id_p = 0;
	pthread_mutex_lock(&(obs->share->n_eat_lock));
	while (1)
	{
		if (obs->philo[id_p].n_eat >= obs->share->n_eat)
			obs->eat_rec[obs->philo[id_p].index - 1] = 1;
		id_r = 0;
		all_eat = 0;
		while (id_r < obs->share->n_philo)
		{
			if (obs->eat_rec[id_r] == 1)
				all_eat = 1;
			else
			{
				all_eat = 0;
				break ;
			}
			id_r++;
		}
		if (id_r == obs->share->n_philo)
		{
			obs->share->n_eat_done = 1;
			break ;
		}
		id_p = (id_p + 1) % obs->share->n_philo;
	}
	pthread_mutex_unlock(&(obs->share->n_eat_lock));
	return (NULL);
}

int	main(int ac, char **av)
{
	t_share		share;
	t_philo		*philos;
	t_observer	obs;

	if (ac < 2)
		return (1);
	if (init_share(ac, av, &share))
		return (1);
	philos = (t_philo *)malloc(sizeof(t_philo) * share.n_philo);
	if (!philos)
		return (1);
	if (init_philo(philos, &share))
		return (1);
	if (init_observer(&obs, philos, &share))
		return (1);
	if (philo_thread_join(share, philos))
		return (1);
	if (pthread_join(obs.thread, NULL))
		return (1);
	free(share.fork);
	free(philos);
	return (0);
}

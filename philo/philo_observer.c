/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_observer.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: woosekim <woosekim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 19:51:04 by woosekim          #+#    #+#             */
/*   Updated: 2023/06/21 13:17:53 by woosekim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_all_eat(t_eat *eat)
{
	int	id_r;
	int	all_eat;

	id_r = 0;
	all_eat = 0;
	while (id_r < eat->share->n_philo)
	{
		if (eat->rec[id_r] == 1)
			all_eat = 1;
		else
		{
			all_eat = 0;
			break ;
		}
		id_r++;
	}
	return (all_eat);
}

void	*check_eat_done(void *eat_temp)
{
	t_eat		*eat;
	int			id_p;

	eat = (t_eat *)eat_temp;
	id_p = 0;
	while (1)
	{
		if (check_end_flag(eat->share))
			break ;
		pthread_mutex_lock(&(eat->philo[id_p].n_eat_lock));
		if ((eat->rec[eat->philo[id_p].index - 1] == 0) && \
			(eat->philo[id_p].n_eat >= eat->share->n_eat))
			eat->rec[eat->philo[id_p].index - 1] = 1;
		pthread_mutex_unlock(&(eat->philo[id_p].n_eat_lock));
		if (check_all_eat(eat))
		{
			pthread_mutex_lock(&(eat->share->end_lock));
			eat->share->end_flag = 1;
			pthread_mutex_unlock(&(eat->share->end_lock));
			break ;
		}
		id_p = (id_p + 1) % eat->share->n_philo;
	}
	free(eat->rec);
	return (NULL);
}

void	*check_time_over(void *obs_temp)
{
	int		elapsed_time;
	int		id_p;
	t_obs	*obs;

	obs = (t_obs *)obs_temp;
	id_p = 0;
	while (1)
	{
		if (check_end_flag(obs->share))
			break ;
		elapsed_time = time_diff_calculator(obs->philo[id_p].time);
		if (elapsed_time == -1)
			break ;
		if (elapsed_time >= obs->share->t_die)
		{
			die_philo(&(obs->philo[id_p]));
			break ;
		}
		id_p = (id_p + 1) % obs->share->n_philo;
	}
	return (NULL);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_share_init.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: woosekim <woosekim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/10 15:21:59 by woosekim          #+#    #+#             */
/*   Updated: 2023/06/27 19:31:33 by woosekim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_share(t_share *share)
{
	if (share->n_philo < 1)
		return (1);
	else if (share->t_die < 1)
		return (1);
	else if (share->t_eat < 1)
		return (1);
	else if (share->t_sleep < 1)
		return (1);
	else if (share->eat_flag == 1)
	{
		if (share->n_eat < 1)
			return (1);
	}
	return (0);
}

int	input_arr(int ac, char **av, int *value)
{
	int		idx_a;
	int		idx_v;
	int		idx_s;
	char	**split;

	idx_a = 1;
	idx_v = 0;
	while (idx_a < ac)
	{
		split = ft_split(av[idx_a], ' ');
		if (!split)
			return (1);
		idx_s = 0;
		while (split[idx_s] != NULL)
		{
			value[idx_v] = ft_atoi(split[idx_s]);
			if (check_str_num(split, idx_s, value, idx_v))
				return (1);
			idx_s++;
			idx_v++;
		}
		free_double_ptr(split);
		idx_a++;
	}
	return (0);
}

void	input_share(int argv_count, int *value, t_share *share)
{
	int	idx_v;

	idx_v = 0;
	while (idx_v < argv_count)
	{
		share->eat_flag = 0;
		share->n_eat = 0;
		share->end_flag = 0;
		if (idx_v == 0)
			share->n_philo = value[idx_v];
		else if (idx_v == 1)
			share->t_die = value[idx_v];
		else if (idx_v == 2)
			share->t_eat = value[idx_v];
		else if (idx_v == 3)
			share->t_sleep = value[idx_v];
		else if (idx_v == 4)
		{
			share->n_eat = value[idx_v];
			share->eat_flag = 1;
		}
		idx_v++;
	}
}

int	init_mutex(t_share *share)
{
	int	id_f;

	share->fork = (t_fork *)malloc(sizeof(t_fork) * share->n_philo);
	if (!share->fork)
		return (1);
	id_f = 0;
	while (id_f < share->n_philo)
	{
		if (pthread_mutex_init(&(share->fork[id_f].lock), NULL))
			return (1);
		share->fork[id_f].in_use = 0;
		id_f++;
	}
	if (pthread_mutex_init(&(share->print_lock), NULL))
		return (1);
	if (pthread_mutex_init(&(share->end_lock), NULL))
		return (1);
	return (0);
}

int	init_share(int ac, char **av, t_share *share)
{
	int		*value;
	int		argv_count;

	argv_count = argv_counter(ac, av);
	if (!(argv_count == 4 || argv_count == 5))
		return (1);
	value = (int *)malloc(sizeof(int) * argv_count);
	if (input_arr(ac, av, value))
	{
		free(value);
		return (1);
	}
	input_share(argv_count, value, share);
	free(value);
	if (check_share(share))
		return (1);
	if (init_mutex(share))
		return (1);
	return (0);
}

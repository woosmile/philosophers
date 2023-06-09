/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: woosekim <woosekim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 14:06:17 by woosekim          #+#    #+#             */
/*   Updated: 2023/06/09 19:55:21 by woosekim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>
# include <pthread.h>

typedef enum e_status
{
	EAT = 0,
	SLEEP,
	THINK
}	t_status;

typedef struct s_share
{
	int				n_philo;
	int				n_eat;
	int				n_eat_flag;
	int				t_die;
	int				t_eat;
	int				t_sleep;
	struct timeval	time;
	int				*fork;
	pthread_mutex_t	*fork_lock;
	pthread_mutex_t	print_lock;
}	t_share;

typedef struct s_philo
{
	int				index;
	t_status		status;
	pthread_t		thread;
	struct timeval	time;
	int				n_eat;
	t_share			*share;
}	t_philo;

int	init_philo(int ac, char **av, t_share *share);

#endif
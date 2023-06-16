/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: woosekim <woosekim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 14:06:17 by woosekim          #+#    #+#             */
/*   Updated: 2023/06/16 18:17:42 by woosekim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>
# include <pthread.h>
# include <string.h>

# define T_UNIT 10

typedef pthread_mutex_t	t_mutex;
typedef struct timeval	t_time;
typedef pthread_t		t_pthread;

typedef enum e_status
{
	EATING = 0,
	SLEEPING,
	GRAB,
	THINKING,
	DIE,
}	t_status;

typedef struct s_fork
{
	t_mutex	lock;
	int		in_use;
}	t_fork;

typedef struct s_share
{
	int				n_philo;
	int				t_die;
	int				t_eat;
	int				t_sleep;
	int				n_eat;
	t_mutex			n_eat_lock;
	int				n_eat_flag;
	int				n_eat_done;
	t_mutex			n_eat_done_lock; //lock
	int				die_flag;
	t_mutex			n_die_flag_lock; //lock
	t_time			time;
	t_fork			*fork;
	t_mutex			print_lock;
}	t_share;

typedef struct s_philo
{
	int				index;
	t_status		status;
	t_pthread		thread;
	t_time			time;
	int				n_eat;
	t_share			*share;
}	t_philo;

typedef struct s_observer
{
	int			*eat_rec;
	t_time		time;
	t_pthread	thread;
	t_philo		*philo;
	t_share		*share;
}	t_observer;

size_t	ft_strlen(const char *s);
size_t	ft_numlen(int num);
void	free_double_ptr(char **ptr);

int		init_share(int ac, char **av, t_share *share);
int		argv_counter(int ac, char **av);
int		input_arr(int ac, char **av, int *value);
int		ft_atoi(const char *str);
char	**ft_split(char const *s, char c);
int		check_str_num(char **split, int idx_s, int *value, int idx_v);
void	input_share(int argv_count, int *value, t_share *share);
int		check_share(t_share *share);
int		init_mutex(t_share *share);

int		time_diff_calculator(t_time old);
void	print_philo(t_philo *philo);

int		init_philo(t_philo *philos, t_share *share);
int		philo_thread_join(t_share share, t_philo *philos);
int		start_philo(t_philo *philos, t_share *share);
void	*think_philo(void *philo_temp);
void	eat_spaghetti(t_philo *philo);
void	sleep_philo(t_philo *philo);

int		init_observer(t_observer *obs, t_philo *philos, t_share *share);
void	*philo_observer(void *obs);

#endif
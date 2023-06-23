/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: woosekim <woosekim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 14:06:17 by woosekim          #+#    #+#             */
/*   Updated: 2023/06/23 14:03:13 by woosekim         ###   ########.fr       */
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

# define T_UNIT 12

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
	int				eat_flag;
	int				n_eat;
	t_mutex			end_lock;
	int				end_flag;
	t_time			time;
	t_fork			*fork;
	t_mutex			print_lock;
}	t_share;

typedef struct s_philo
{
	int				index;
	t_mutex			status_lock;
	t_status		status;
	t_pthread		thread;
	t_time			time;
	t_mutex			n_eat_lock;
	int				n_eat;
	t_share			*share;
}	t_philo;

typedef struct s_eat
{
	int			*rec;
	t_pthread	thread;
	t_philo		*philo;
	t_share		*share;
}	t_eat;

typedef struct s_obs
{
	t_pthread	thread;
	t_philo		*philo;
	t_share		*share;
}	t_obs;

void	free_double_ptr(char **ptr);
int		time_diff_calculator(t_time old);
void	print_philo(t_philo *philo);
int		check_end_flag(t_share *share);

int		init_share(int ac, char **av, t_share *share);
int		argv_counter(int ac, char **av);
int		input_arr(int ac, char **av, int *value);
char	**ft_split(char const *s, char c);
int		ft_atoi(const char *str);
int		check_str_num(char **split, int idx_s, int *value, int idx_v);
size_t	ft_strlen(const char *s);
size_t	ft_numlen(int num);
void	input_share(int argv_count, int *value, t_share *share);
int		check_share(t_share *share);
int		init_mutex(t_share *share);

int		init_philo_thread(t_philo *philos, t_share *share);
int		start_philo(t_philo *philos, t_share *share);
int		philo_thread_join(t_share share, t_philo *philos);

int		in_action(t_philo *philo);
void	eat_spaghetti(t_philo *philo);
void	sleep_philo(t_philo *philo);
void	*think_philo(void *philo_temp);
void	die_philo(t_philo *philo);

int		select_action_time(t_philo *philo);
void	time_over_in_action(t_philo *philo);
int		check_time_before_eat(t_philo *philo);
int		fork_grab(t_philo *philo);
void	fork_release(t_philo *philo);

int		init_check_eat_thread(t_eat *eat, t_philo *philos, t_share *share);
void	*check_eat_done(void *eat_temp);
int		check_all_eat(t_eat *eat);

int		init_check_time_thread(t_obs *obs, t_philo *philos, t_share *share);
void	*check_time_over(void *obs_temp);

int		init_func(t_share *share, t_philo *philos, t_eat *eat, t_obs *obs);
int		join_func(t_share *share, t_philo *philos, t_eat *eat, t_obs *obs);

#endif
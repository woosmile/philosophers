/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: woosekim <woosekim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 13:42:40 by woosekim          #+#    #+#             */
/*   Updated: 2023/06/27 15:22:07 by woosekim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <signal.h>
# include <sys/wait.h>
# include <sys/time.h>
# include <pthread.h>
# include <string.h>
# include <semaphore.h>
# include <errno.h>

# define T_UNIT 12

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

typedef struct s_share
{
	t_time		time;
	int			n_philo;
	int			t_die;
	int			t_eat;
	int			t_sleep;
	int			n_eat;
	int			eat_flag;
	sem_t		*eat_sem;
	t_time		eat_sem_time;
	t_pthread	eat_sem_in;
	t_pthread	check_eat_sem_time;
	sem_t		*fork_sem;
	sem_t		*print_sem;
}	t_share;

typedef struct s_philo
{
	int			index;
	t_status	status;
	t_time		time;
	int			n_eat;
	t_share		*share;
	t_pthread	fork_wait;
}	t_philo;

int		sem_unlink_func(void);
void	free_double_ptr(char **ptr);
int		time_diff_calculator(t_time old);
void	print_philo(t_philo *philo);
void	wait_philo(t_share *share);

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

int		select_action_time(t_philo *philo);
int		check_time_before_eat(t_philo *philo);

char	*ft_itoa(int n);
int		init_philo(t_philo *philos, t_share *share);
int		start_philo(t_philo *philos, t_share *share);

int		in_action(t_philo *philo);
void	eat_spaghetti(t_philo *philo);
void	sleep_philo(t_philo *philo);
void	*think_philo(t_philo *philo);
void	die_philo(t_philo *philo);

void	fork_grab(t_philo *philo);
void	fork_release(t_philo *philo);

void	*check_time_over(void *obs_temp);

int		init_check_eat_thread(t_share *share);
void	*eat_sem_in(void *eat_temp);
void	*check_eat_sem_time(void *share_temp);
int		join_check_eat_thread(t_share *share);

#endif
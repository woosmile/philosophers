/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: woosekim <woosekim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 14:06:17 by woosekim          #+#    #+#             */
/*   Updated: 2023/06/12 21:35:15 by woosekim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>
# include <pthread.h>

typedef pthread_mutex_t	t_mutex;
typedef struct timeval	t_time;
typedef pthread_t		t_pthread;

typedef enum e_status
{
	EAT = 0,
	SLEEP,
	THINK
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
	int				n_eat_flag;
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

size_t	ft_strlen(const char *s);
size_t	ft_numlen(int num);
void	free_double_ptr(char **ptr);
void	*ft_calloc(size_t count, size_t size);

int		init_share(int ac, char **av, t_share *share);
int		argv_counter(int ac, char **av);
int		input_arr(int ac, char **av, int *value);
int		ft_atoi(const char *str);
char	**ft_split(char const *s, char c);
int		check_str_num(char **split, int idx_s, int *value, int idx_v);
void	input_share(int argv_count, int *value, t_share *share);
int		check_share(t_share *share);
int		init_fork(t_share *share);

void	*print_philo(void *share);
int		init_philo(t_philo *philos, t_share *share);

#endif
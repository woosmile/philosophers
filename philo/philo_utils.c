/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: woosekim <woosekim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 14:06:20 by woosekim          #+#    #+#             */
/*   Updated: 2023/06/09 20:04:57 by woosekim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	number_result(const char *str, int sign)
{
	int		result;
	long	result_l;
	long	check;

	result = 0;
	result_l = 0;
	check = 0;
	while (*str >= '0' && *str <= '9')
	{
		result = (result * 10) + (*str - '0');
		result_l = (result_l * 10) + (*str - '0');
		if (sign == -1)
		{
			if (result_l < check)
				return (0);
		}
		else if (sign == 1)
		{
			if (result_l < check)
				return (-1);
		}
		check = result_l;
		str++;
	}
	return (result);
}

int	ft_atoi(const char *str)
{
	int		sign;

	sign = 1;
	while ((*str >= 9 && *str <= 13) || (*str == 32))
		str++;
	if (*str == '+' || *str == '-')
	{
		if (*str == '-')
			sign = -1;
		str++;
	}
	return (number_result(str, sign) * sign);
}

size_t	ft_strlen(const char *s)
{
	size_t	len;

	len = 0;
	while (s[len] != 0)
		len++;
	return (len);
}

size_t	ft_numlen(int num)
{
	size_t	len;

	len = 0;
	while (num != 0)
	{
		num = num / 10;
		len++;
	}
	return (len);
}

int	check_share_value(t_share *share)
{
	if (share->n_philo < 2)
		return (1);
	else if (share->t_die < 1)
		return (1);
	else if (share->t_eat < 1)
		return (1);
	else if (share->t_sleep < 1)
		return (1);
	else if (share->n_eat_flag == 1)
	{
		if (share->n_eat < 1)
			return (1);
	}
	return (0);
}

int	init_philo(int ac, char **av, t_share *share)
{
	int	id_x;
	int	*value;

	id_x = 0;
	value = (int *)malloc(sizeof(int) * (ac - 1));
	while (id_x + 1 < ac)
	{
		value[id_x] = ft_atoi(av[id_x + 1]);
		if (ft_strlen(av[id_x + 1]) != ft_numlen(value[id_x]))
		{
			free(value);
			return (1);
		}
		id_x++;
	}
	id_x = 0;
	while (id_x < ac - 1)
	{
		if (id_x == 0)
			share->n_philo = value[id_x];
		else if (id_x == 1)
			share->t_die = value[id_x];
		else if (id_x == 2)
			share->t_eat = value[id_x];
		else if (id_x == 3)
			share->t_sleep = value[id_x];
		else if (id_x == 4)
		{
			share->n_eat = value[id_x];
			share->n_eat_flag = 1;
		}
		id_x++;
	}
	if (ac == 5)
	{
		share->n_eat_flag = 0;
		share->n_eat = 0;
	}
	free(value);
	if (check_share_value(share))
		return (1);
	return (0);
}
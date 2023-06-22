/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_share_init_utils_bonus.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: woosekim <woosekim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/10 16:47:40 by woosekim          #+#    #+#             */
/*   Updated: 2023/06/22 16:35:17 by woosekim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	argv_counter(int ac, char **av)
{
	int	x;
	int	y;
	int	count;

	x = 1;
	count = 0;
	while (x < ac)
	{
		y = 0;
		while (av[x][y] != 0)
		{
			if (av[x][y] != ' ' && (av[x][y + 1] == ' ' || av[x][y + 1] == 0))
				count++;
			y++;
		}
		x++;
	}
	return (count);
}

int	check_str_num(char **split, int idx_s, int *value, int idx_v)
{
	if (ft_strlen(split[idx_s]) != ft_numlen(value[idx_v]))
	{
		free_double_ptr(split);
		return (1);
	}
	return (0);
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

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: woosekim <woosekim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 14:06:20 by woosekim          #+#    #+#             */
/*   Updated: 2023/06/10 17:17:25 by woosekim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	free_double_ptr(char **ptr)
{
	int	i;

	if (ptr == NULL)
		return ;
	i = 0;
	while (ptr[i])
	{
		free(ptr[i]);
		i++;
	}
	free (ptr);
}

void	*ft_calloc(size_t count, size_t size)
{
	unsigned char	*arr;
	size_t			i;

	if ((count * size) / size != count)
		return (0);
	arr = (unsigned char *)malloc(count * size);
	if (!arr)
		return (0);
	i = 0;
	while (i < count * size)
	{
		arr[i] = 0;
		i++;
	}
	return ((void *)arr);
}
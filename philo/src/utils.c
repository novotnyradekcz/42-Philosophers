/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnovotny <rnovotny@student.42prague.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/19 12:30:06 by rnovotny          #+#    #+#             */
/*   Updated: 2024/05/19 16:51:32 by rnovotny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_atoi(const char *nptr)
{
	int				i;
	int				neg;
	unsigned int	res;

	neg = 1;
	res = 0;
	i = 0;
	while ((nptr[i] >= 9 && nptr[i] <= 13) || nptr[i] == 32)
		i++;
	if (nptr[i] == '-' || nptr[i] == '+')
	{
		if (nptr[i] == '-')
			neg = -neg;
		i++;
	}
	while (nptr[i] >= 48 && nptr[i] <= 57)
	{
		res = res * 10 + (nptr[i] - 48);
		i++;
	}
	if (res > 2147483647)
		return -1;
	return neg * res;
}

size_t	get_time(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) == -1)
		write(2, "Error in gettimeofday() function\n", 33);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}
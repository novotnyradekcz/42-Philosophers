/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnovotny <rnovotny@student.42prague.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/19 12:30:06 by rnovotny          #+#    #+#             */
/*   Updated: 2024/05/19 20:30:34 by rnovotny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

size_t	ft_strlen(const char *str)
{
	int	n;

	n = 0;
	while (str[n] != 0)
		n++;
	return (n);
}

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
		return (-1);
	return (neg * res);
}

int	ft_usleep(size_t ms)
{
	size_t	start;

	start = get_time();
	while (get_time() - start < ms)
		if (usleep(500) == -1)
			write(2, "Error in usleep() function\n", 29);
	return (0);
}

size_t	get_time(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) == -1)
		write(2, "Error in gettimeofday() function\n", 33);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

void	destory_all(char *str, t_program *program, pthread_mutex_t *forks)
{
	int	i;

	i = 0;
	if (str)
		write(2, str, ft_strlen(str));
	pthread_mutex_destroy(&program->write_lock);
	pthread_mutex_destroy(&program->meal_lock);
	pthread_mutex_destroy(&program->dead_lock);
	while (i < program->num_of_philos)
	{
		pthread_mutex_destroy(&forks[i]);
		i++;
	}
	free(program->philos);
	free(forks);
}

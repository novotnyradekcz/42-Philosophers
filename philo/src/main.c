/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnovotny <rnovotny@student.42prague.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/05 18:15:50 by rnovotny          #+#    #+#             */
/*   Updated: 2024/05/21 11:03:56 by rnovotny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	dead_loop(t_philo *philo)
{
	pthread_mutex_lock(philo->dead_lock);
	if (*philo->dead == 1)
		return (pthread_mutex_unlock(philo->dead_lock), 1);
	pthread_mutex_unlock(philo->dead_lock);
	return (0);
}

void	*philo_loop(void *pointer)
{
	t_philo	*philo;

	philo = (t_philo *)pointer;
	if (philo->id % 2 == 0)
		ft_usleep(1);
	while (!dead_loop(philo))
	{
		eat(philo);
		snooze(philo);
		think(philo);
	}
	return (pointer);
}

int	check_input(int argc, char **argv)
{
	if (argc < 5 || argc > 6)
		return (write(2, "Invalid number of arguments.\n", 29));
	if (ft_atoi(argv[1]) <= 0)
		return (write(2, "No. of philosophers must be a positive int.\n", 44));
	if (ft_atoi(argv[2]) <= 0)
		return (write(2, "Time to die must be a positive int.\n", 36));
	if (ft_atoi(argv[3]) <= 0)
		return (write(2, "Time to eat must be a positive int.\n", 36));
	if (ft_atoi(argv[4]) <= 0)
		return (write(2, "Time to sleep must be a positive int.\n", 38));
	if (argc > 5 && ft_atoi(argv[5]) < 0)
	{
		write(2, "Number of times each philosopher must eat ", 42);
		return (write(2, "must be a non-negative int.\n", 28));
	}
	return (0);
}

int	main(int argc, char **argv)
{
	t_program		program;
	t_philo			*philos;
	pthread_mutex_t	*forks;

	if (check_input(argc, argv))
		return (1);
	philos = malloc(ft_atoi(argv[1]) * sizeof(t_philo));
	if (!philos)
		return (write(2, "Error in malloc() - philosophers.\n", 33));
	forks = malloc(ft_atoi(argv[1]) * sizeof(pthread_mutex_t));
	if (!philos)
	{
		free(philos);
		return (write(2, "Error in malloc() - forks.\n", 33));
	}
	init_program(&program, philos);
	init_forks(forks, ft_atoi(argv[1]));
	init_philos(philos, &program, forks, argv);
	thread_create_join(&program, forks);
	destory_all(NULL, &program, forks);
	return (0);
}

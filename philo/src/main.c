/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnovotny <rnovotny@student.42prague.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/05 18:15:50 by rnovotny          #+#    #+#             */
/*   Updated: 2024/05/19 19:45:12 by rnovotny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*monitor(void *pointer)
{
	t_philo	*philos;

	philos = (t_philo *)pointer;
	while (1)
		if (check_if_dead(philos) == 1 || check_if_all_ate(philos) == 1)
			break ;
	return (pointer);
}

void	init_philos(t_program *program, pthread_mutex_t *forks, char **argv)
{
	int	i;

	i = 0;
	while (i < ft_atoi(argv[1]))
	{
		program->philos[i].id = i + 1;
		program->philos[i].eating = 0;
		program->philos[i].meals_eaten = 0;
		
		program->philos[i].last_meal = program->start_time;
		program->philos[i].write_lock = &program->write_lock;
		program->philos[i].dead_lock = &program->dead_lock;
		program->philos[i].meal_lock = &program->meal_lock;
		program->philos[i].dead = &program->dead_flag;
		program->philos[i].l_fork = &forks[i];
		if (i == 0)
			philos[i].r_fork = &forks[program->num_of_philos - 1];
		else
			philos[i].r_fork = &forks[i - 1];
		i++;
	}
}

void	init_program(t_program *program, t_philo *philos, t_philo *forks,
		char **argv)
{
	int	i;

	program->dead_flag = 0;
	program->philos = philos;
	program->time_to_die = ft_atoi(argv[2]);
	program->time_to_eat = ft_atoi(argv[3]);
	program->time_to_sleep = ft_atoi(argv[4]);
	program->start_time = get_time();
	program->num_of_philos = ft_atoi(argv[1]);
	if (argv[5])
		program->num_times_to_eat = ft_atoi(argv[5]);
	else
		program->num_times_to_eat = -1;
	pthread_mutex_init(&program->write_lock, NULL);
	pthread_mutex_init(&program->dead_lock, NULL);
	pthread_mutex_init(&program->meal_lock, NULL);
	i = -1;
	while (++i < program->num_of_philos)
		pthread_mutex_init(&forks[i], NULL);
}

int	check_input(int argc, char **argv)
{
	if (argc < 5 || argc > 6)
		return write(2, "Invalid number of arguments.\n", 29);
	if (ft_atoi(argv[1]) <= 0)
		return write(2, "Number of philosophers must be a positive int.\n", 47);
	if (ft_atoi(argv[2]) <= 0)
		return write(2, "Time to die must be a positive int.\n", 36);
	if (ft_atoi(argv[3]) <= 0)
		return write(2, "Time to eat must be a positive int.\n", 36);
	if (ft_atoi(argv[4]) <= 0)
		return write(2, "Time to sleep must be a positive int.\n", 38);
	if (argc > 5 && ft_atoi(argv[5]) <= 0)
	{
		write(2, "Number of times each philosopher must eat ", 42);
		return write(2, "must be a positive integer or zero.\n", 36);
	}
	return 0;
}

int	main(int argc, char **argv)
{
	t_program		program;
	t_philo			*philos;
	pthread_mutex_t	*forks;

	if (check_input(argc, argv))
		return 1;
	philos = malloc(ft_atoi(argv[1]) * sizeof(t_philo));
	forks = malloc(ft_atoi(argv[1]) * sizeof(pthread_mutex_t));
	init_program(&program, philos, forks, ft_atoi(argv[1]));
	init_philos(&program, forks, argv);
	create_threads(&program, forks);
	destory_all(NULL, &program, forks);
	return 0;
}
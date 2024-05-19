/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   program.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnovotny <rnovotny@student.42prague.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/19 19:01:12 by rnovotny          #+#    #+#             */
/*   Updated: 2024/05/19 20:14:55 by rnovotny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_if_dead(t_program *program, t_philo *philos)
{
	int	i;
	int	dead;

	i = 0;
	while (i < program->num_of_philos)
	{
		pthread_mutex_lock(philos[i].meal_lock);
		dead = get_time() - philos[i].last_meal >= philos[i].time_to_die
			&& !philos[i].eating;
		pthread_mutex_unlock(philos[i].meal_lock);
		if (dead)
		{
			print_message("died", &philos[i], philos[i].id);
			pthread_mutex_lock(philos[0].dead_lock);
			*philos->dead = 1;
			pthread_mutex_unlock(philos[0].dead_lock);
			return (1);
		}
		i++;
	}
	return (0);
}

int	check_if_all_ate(t_program *program, t_philo *philos)
{
	int	i;
	int	finished_eating;

	i = 0;
	finished_eating = 0;
	if (program->num_times_to_eat == -1)
		return (0);
	while (i < program->num_of_philos)
	{
		pthread_mutex_lock(philos[i].meal_lock);
		if (philos[i].meals_eaten >= program->num_times_to_eat)
			finished_eating++;
		pthread_mutex_unlock(philos[i].meal_lock);
		i++;
	}
	if (finished_eating == program->num_of_philos)
	{
		pthread_mutex_lock(philos[0].dead_lock);
		*philos->dead = 1;
		pthread_mutex_unlock(philos[0].dead_lock);
		return (1);
	}
	return (0);
}

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

int	create_threads(t_program *program, pthread_mutex_t *forks)
{
	pthread_t	observer;
	int			i;

	if (pthread_create(&observer, NULL, &monitor, program->philos) != 0)
		destory_all("Thread creation failed.\n", program, forks);
	i = 0;
	while (i < program->num_of_philos)
	{
		if (pthread_create(&program->philos[i].thread, NULL, &philo_loop,
				&program->philos[i]) != 0)
			destory_all("Thread creation failed.\n", program, forks);
		i++;
	}
	i = 0;
	if (pthread_join(observer, NULL) != 0)
		destory_all("Thread join failed.\n", program, forks);
	while (i < program->num_of_philos)
	{
		if (pthread_join(program->philos[i].thread, NULL) != 0)
			destory_all("Thread join error.\n", program, forks);
		i++;
	}
	return (0);
}
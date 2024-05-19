/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnovotny <rnovotny@student.42prague.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/05 18:16:40 by rnovotny          #+#    #+#             */
/*   Updated: 2024/05/19 20:32:25 by rnovotny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

typedef struct s_philo
{
	pthread_t		thread;
	int				id;
	int				eating;
	int				meals_eaten;
	size_t			start_time;
	size_t			last_meal;
	size_t			time_to_die;
	size_t			time_to_eat;
	size_t			time_to_sleep;
	int				num_of_philos;
	int				*dead;
	pthread_mutex_t	*r_fork;
	pthread_mutex_t	*l_fork;
	pthread_mutex_t	*write_lock;
	pthread_mutex_t	*dead_lock;
	pthread_mutex_t	*meal_lock;
}					t_philo;

typedef struct s_program
{
	int				dead_flag;
	int				num_of_philos;
	int				num_times_to_eat;
	pthread_mutex_t	dead_lock;
	pthread_mutex_t	meal_lock;
	pthread_mutex_t	write_lock;
	t_philo			*philos;
}					t_program;

int		main(int argc, char **argv);
int		check_input(int argc, char **argv);
void	init_program(t_program *program, t_philo *philos,
			pthread_mutex_t *forks, char **argv);
void	init_philos(t_program *program, pthread_mutex_t *forks, char **argv);
void	*monitor(void *pointer);

int		create_threads(t_program *program, pthread_mutex_t *forks);
void	*philo_loop(void *pointer);
int		dead_loop(t_philo *philo);
int		check_if_all_ate(t_program *program, t_philo *philos);
int		check_if_dead(t_program *program, t_philo *philos);

void	eat(t_philo *philo);
void	snooze(t_philo *philo);
void	think(t_philo *philo);
void	log_message(char *str, t_philo *philo, int id);

size_t	ft_strlen(const char *str);
int		ft_atoi(const char *nptr);
int		ft_usleep(size_t ms);
size_t	get_time(void);
void	destory_all(char *str, t_program *program, pthread_mutex_t *forks);

#endif
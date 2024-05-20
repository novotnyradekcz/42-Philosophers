/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnovotny <rnovotny@student.42prague.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/05 18:16:40 by rnovotny          #+#    #+#             */
/*   Updated: 2024/05/20 18:45:38 by rnovotny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

# define PHILO_MAX 300

typedef struct s_philo
{
	pthread_t		thread;
	int				id;
	int				eating;
	int				meals_eaten;
	size_t			last_meal;
	size_t			time_to_die;
	size_t			time_to_eat;
	size_t			time_to_sleep;
	size_t			start_time;
	int				num_of_philos;
	int				num_times_to_eat;
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
	pthread_mutex_t	dead_lock;
	pthread_mutex_t	meal_lock;
	pthread_mutex_t	write_lock;
	t_philo			*philos;
}					t_program;

int		main(int argc, char **argv);
int		check_input(int argc, char **argv);
void	*philo_loop(void *pointer);
int		dead_loop(t_philo *philo);

void	init_program(t_program *program, t_philo *philos);
void	init_forks(pthread_mutex_t *forks, int philo_num);
void	init_philos(t_philo *philos, t_program *program, pthread_mutex_t *forks,
		char **argv);
void	init_input(t_philo *philo, char **argv);
int		thread_create_join(t_program *program, pthread_mutex_t *forks);

void	*monitor(void *pointer);
int		check_if_all_ate(t_philo *philos);
int		check_if_dead(t_philo *philos);

void	eat(t_philo *philo);
void	snooze(t_philo *philo);
void	think(t_philo *philo);
void	log_message(char *str, t_philo *philo, int id);

size_t	ft_gettimeofday(void);
int		ft_usleep(size_t milliseconds);
void	destory_all(char *str, t_program *program, pthread_mutex_t *forks);
int		ft_atoi(const char *nptr);
size_t	ft_strlen(const char *str);

#endif

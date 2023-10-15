/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akaniber <akaniber@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/30 12:42:18 by akaniber          #+#    #+#             */
/*   Updated: 2023/10/15 13:50:37 by akaniber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <stdlib.h>
# include <pthread.h>

typedef struct s_philo
{
	struct s_env	*env;
	pthread_t		thread;
	pthread_mutex_t	*m_right_fork;
	pthread_mutex_t	*m_left_fork;
	uint64_t		id;
	uint64_t		last_eat;
	int				eat_count;
}	t_philo;

typedef struct s_env
{
	t_philo			*philos;
	int				number_of_philo;
	int				time_to_eat;
	int				time_to_sleep;
	int				number_of_must_eat;
	int				stop;
	uint64_t		time_to_die;
	uint64_t		time;
	pthread_mutex_t	m_stop;
	pthread_mutex_t	m_eat_count;
	pthread_mutex_t	m_last_eat;
	pthread_mutex_t	*m_forks;
	pthread_mutex_t	m_write;
	pthread_mutex_t	m_die;
}	t_env;

int				arg_control(int argc, char **argv);
void			destroy_threads(t_env *env, int thread_count);
unsigned int	ft_atoi(char *str);
int				print_error(char *str);
void			message(t_philo *philo, char *str);
int				init_forks(t_philo *philo, t_env *env, int i);
int				init_philo(t_philo *philo, t_env *env, int i);
int				init_threads(t_env *env);
void			destroy_threads(t_env *env, int thread_count);
t_env			*init_args(int argc, char **argv);
t_env			*init_params(t_env *env);
void			*routine(void *_philo);
uint64_t		current_time(void);
uint64_t		time_from_start(t_env *env);
void			time_usleep(uint16_t micsec);
void			die_controller(t_env *env);
int				init_philo_or_fork(t_env *env, \
	int (callback)(t_philo *philo, t_env *env, int i));
int				init_mutexes(t_env *env);
void			destroy_mutexes(t_env *env, int mutex_count);

#endif
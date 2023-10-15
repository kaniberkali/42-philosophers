/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akaniber <akaniber@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 15:17:41 by akaniber          #+#    #+#             */
/*   Updated: 2023/10/14 17:44:41 by akaniber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#define MSG_FORK "has taken a fork"
#define MSG_EAT "is eating"
#define MSG_SLEEP "is sleeping"
#define MSG_THINK "is thinking"

static void	philo_eat(t_philo *philo)
{
	if (philo->eat_count == philo->env->number_of_must_eat)
		return ;
	pthread_mutex_lock(philo->m_right_fork);
	message(philo, MSG_FORK);
	pthread_mutex_lock(philo->m_left_fork);
	message(philo, MSG_FORK);
	message(philo, MSG_EAT);
	pthread_mutex_lock(&philo->env->m_eat_count);
	philo->eat_count++;
	pthread_mutex_unlock(&philo->env->m_eat_count);
	time_usleep(philo->env->time_to_eat);
	pthread_mutex_lock(&philo->env->m_last_eat);
	philo->last_eat = current_time();
	pthread_mutex_unlock(&philo->env->m_last_eat);
	pthread_mutex_unlock(philo->m_right_fork);
	pthread_mutex_unlock(philo->m_left_fork);
}

static void	philo_sleep(t_philo *philo)
{
	message(philo, MSG_SLEEP);
	time_usleep(philo->env->time_to_sleep);
}

static void	philo_think(t_philo *philo)
{
	message(philo, MSG_THINK);
}

void	*routine(void *_philo)
{
	t_philo	*philo;
	int		stop;

	philo = (t_philo *)_philo;
	if (philo->env->number_of_philo == 1)
	{
		pthread_mutex_lock(philo->m_right_fork);
		message(philo, MSG_FORK);
		return (NULL);
	}
	if (philo->id % 2 == 0)
		time_usleep(10);
	while (1)
	{
		pthread_mutex_lock(&philo->env->m_stop);
		stop = philo->env->stop;
		pthread_mutex_unlock(&philo->env->m_stop);
		if (stop == 1)
			break ;
		philo_eat(philo);
		philo_sleep(philo);
		philo_think(philo);
	}
	return (NULL);
}

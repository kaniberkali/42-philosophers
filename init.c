/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akaniber <akaniber@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 15:18:59 by akaniber          #+#    #+#             */
/*   Updated: 2023/10/15 13:37:15 by akaniber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_env	*init_args(int argc, char **argv)
{
	t_env	*env;

	env = malloc(sizeof(t_env));
	if (!env)
		return (NULL);
	env->number_of_philo = ft_atoi(argv[1]);
	env->time_to_die = ft_atoi(argv[2]);
	env->time_to_eat = ft_atoi(argv[3]);
	env->time_to_sleep = ft_atoi(argv[4]);
	env->number_of_must_eat = -1;
	if (argc == 6)
		env->number_of_must_eat = ft_atoi(argv[5]);
	return (env);
}

t_env	*init_params(t_env *env)
{
	if (!env)
		return (NULL);
	env->philos = malloc(sizeof(t_philo) * env->number_of_philo);
	if (!env->philos)
	{
		free(env);
		return (NULL);
	}
	env->m_forks = malloc(sizeof(pthread_mutex_t) * env->number_of_philo);
	if (!env->m_forks)
	{
		free(env->philos);
		free(env);
		return (NULL);
	}
	env->time = current_time();
	env->stop = 0;
	return (env);
}

int	init_philo(t_philo *philo, t_env *env, int i)
{
	philo->id = i + 1;
	philo->env = env;
	philo->eat_count = 0;
	philo->last_eat = current_time();
	return (!pthread_mutex_init(&env->m_forks[i], NULL));
}

int	init_forks(t_philo *philo, t_env *env, int i)
{
	if (i - 1 < 0)
		philo->m_right_fork = env->m_forks + (env->number_of_philo - 1);
	else
		philo->m_right_fork = &env->m_forks[i - 1];
	philo->m_left_fork = &env->m_forks[i];
	return (1);
}

int	init_philo_or_fork(t_env *env, \
	int (callback)(t_philo *philo, t_env *env, int i))
{
	int	i;

	i = -1;
	while (++i < env->number_of_philo)
	{
		if (!callback(&env->philos[i], env, i))
			return (i);
	}
	return (env->number_of_philo);
}

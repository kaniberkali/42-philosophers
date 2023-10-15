/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutexes.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akaniber <akaniber@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 22:46:49 by akaniber          #+#    #+#             */
/*   Updated: 2023/10/15 13:46:46 by akaniber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	init_global_mutexes(t_env *env)
{
	int	result;

	result = 0;
	if (!pthread_mutex_init(&env->m_stop, NULL))
		result++;
	if (result == 1 && !pthread_mutex_init(&env->m_eat_count, NULL))
		result++;
	if (result == 2 && !pthread_mutex_init(&env->m_last_eat, NULL))
		result++;
	if (result == 3 && !pthread_mutex_init(&env->m_write, NULL))
		result++;
	if (result == 4 && !pthread_mutex_init(&env->m_die, NULL))
		result++;
	return (result);
}

int	init_mutexes(t_env *env)
{
	int	mutex_count;

	mutex_count = init_global_mutexes(env);
	if (mutex_count == 5)
	{
		mutex_count += init_philo_or_fork(env, init_philo);
		if ((env->number_of_philo + 5) == mutex_count)
			init_philo_or_fork(env, init_forks);
	}
	return (mutex_count);
}

void	destroy_mutexes(t_env *env, int mutex_count)
{
	int	i;

	i = 0;
	if (mutex_count >= 1)
		pthread_mutex_destroy(&env->m_stop);
	if (mutex_count >= 2)
		pthread_mutex_destroy(&env->m_eat_count);
	if (mutex_count >= 3)
		pthread_mutex_destroy(&env->m_last_eat);
	if (mutex_count >= 4)
		pthread_mutex_destroy(&env->m_write);
	if (mutex_count >= 5)
		pthread_mutex_destroy(&env->m_die);
	while (i < (mutex_count - 5) && i < env->number_of_philo)
		pthread_mutex_destroy(&env->m_forks[i++]);
}

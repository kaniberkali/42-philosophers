/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akaniber <akaniber@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 12:54:30 by akaniber          #+#    #+#             */
/*   Updated: 2023/10/15 13:47:07 by akaniber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_threads(t_env *env)
{
	int	i;

	i = -1;
	while (++i < env->number_of_philo)
	{
		if (pthread_create(&env->philos[i].thread, NULL, \
			routine, &env->philos[i]))
		{
			pthread_mutex_lock(&env->m_stop);
			env->stop = 1;
			pthread_mutex_unlock(&env->m_stop);
			return (i);
		}
	}
	die_controller(env);
	return (env->number_of_philo);
}

void	destroy_threads(t_env *env, int thread_count)
{
	int	i;

	i = -1;
	while (++i < thread_count)
		pthread_join(env->philos[i].thread, NULL);
}

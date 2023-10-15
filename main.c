/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akaniber <akaniber@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 12:53:32 by akaniber          #+#    #+#             */
/*   Updated: 2023/10/15 13:36:33 by akaniber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	finish(t_env *env, int mutex_count, int thread_count)
{
	int	result;

	result = 0;
	if ((env->number_of_philo + 5) != mutex_count)
		result = !print_error("Mutex initialization error!\n");
	else if (env->number_of_philo != thread_count)
		result = !print_error("Thread creation error!\n");
	free(env->m_forks);
	free(env->philos);
	free(env);
	return (result);
}

int	main(int argc, char **argv)
{
	int		mutex_count;
	int		thread_count;
	t_env	*env;

	if (!arg_control(argc, argv))
		return (1);
	env = init_args(argc, argv);
	env = init_params(env);
	if (env != NULL)
	{
		mutex_count = init_mutexes(env);
		thread_count = 0;
		if ((env->number_of_philo + 5) == mutex_count)
		{
			thread_count = init_threads(env);
			destroy_threads(env, thread_count);
		}
		destroy_mutexes(env, mutex_count);
		return (finish(env, mutex_count, thread_count));
	}
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akaniber <akaniber@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 20:18:15 by akaniber          #+#    #+#             */
/*   Updated: 2023/10/15 13:41:28 by akaniber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <stdio.h>

int	print_error(char *str)
{
	printf("%s", str);
	return (0);
}

unsigned int	ft_atoi(char *str)
{
	unsigned int	res;
	int				i;

	i = 0;
	res = 0;
	if (!str)
		return (0);
	while (str[i])
	{
		res = (res * 10) + (str[i] - '0');
		i++;
	}
	return (res);
}

void	message(t_philo *philo, char *str)
{
	uint64_t	time;

	time = time_from_start(philo->env);
	pthread_mutex_lock(&philo->env->m_write);
	pthread_mutex_lock(&philo->env->m_stop);
	if (!philo->env->stop)
		printf("%llu %llu %s\n", time, philo->id, str);
	pthread_mutex_unlock(&philo->env->m_stop);
	pthread_mutex_unlock(&philo->env->m_write);
}

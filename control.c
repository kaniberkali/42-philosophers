/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   control.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akaniber <akaniber@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 12:47:10 by akaniber          #+#    #+#             */
/*   Updated: 2023/10/15 13:39:09 by akaniber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	is_digit(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (0);
		i++;
	}
	return (1);
}

static int	nbr_control(int argc, char **argv)
{
	int	i;

	i = 1;
	if (!(argc == 5 || argc == 6))
		return (print_error("Please enter 4 or 5 arguments\n"));
	while (i < argc)
	{
		if (is_digit(argv[i]) == 0)
			return (0);
		i++;
	}
	return (1);
}

static int	max_control(char **argv)
{
	int	i;

	i = 1;
	while (argv[i])
	{
		if (ft_atoi(argv[i]) <= 0)
			return (0);
		i++;
	}
	return (1);
}

int	arg_control(int argc, char **argv)
{
	if (nbr_control(argc, argv) == 0)
		return (print_error("Incorret argument!\n"));
	if (max_control(argv) == 0)
		return (print_error("Invalid argument!\n"));
	return (1);
}

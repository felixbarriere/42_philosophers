/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbarrier <fbarrier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/02 06:23:32 by fbarrier          #+#    #+#             */
/*   Updated: 2022/02/02 06:23:32 by fbarrier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Include/philosophers.h"

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

int	ft_check_number_size(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	if (i > 10)
		return (1);
	return (0);
}

int	ft_atoi(char *str)
{
	int	res;
	int	sign;

	if (ft_check_number_size(str) == 1)
		return (-1);
	res = 0;
	sign = 1;
	while ((*str == ' ') || (*str >= '\t' && *str <= '\r'))
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			sign *= -1;
		str++;
	}
	while (*str >= '0' && *str <= '9')
	{
		res = 10 * res + (*str - '0');
		str++;
	}
	return (res * sign);
}

int	ft_is_digit(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
		{
			return (0);
		}
		i++;
	}
	return (1);
}

void	ft_usleep(long unsigned int time_in_ms, t_philo *philo)
{
	long unsigned int	start_time;

	start_time = 0;
	start_time = ft_get_time();
	while ((ft_get_time() - start_time) < time_in_ms
		&& ft_get_status(philo) == ALIVE)
		usleep(50);
}

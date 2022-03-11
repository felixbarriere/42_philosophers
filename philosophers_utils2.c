/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers_utils2.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbarrier <fbarrier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/07 14:09:58 by fbarrier          #+#    #+#             */
/*   Updated: 2022/02/11 20:51:22 by fbarrier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Include/philosophers.h"

void	ft_destroy_mutex(t_philo *philo)
{
	free(philo->start->forks_mutex);
	free(philo->start->lock);
}

void	ft_one_philo(t_philo *philo)
{
	if (philo->start->philo_nbr == 1)
	{
		ft_display(philo, TAKE_FORK);
		ft_usleep(philo->start->time_to_die, philo);
		ft_philo_kill(philo);
		ft_destroy_mutex(philo);
	}
}

int	ft_get_status(t_philo *philo)
{
	pthread_mutex_lock(philo->start->forks_mutex);
	if (philo->start->status != ALIVE)
	{
		pthread_mutex_unlock(philo->start->forks_mutex);
		return (DIED);
	}
	pthread_mutex_unlock(philo->start->forks_mutex);
	return (ALIVE);
}

u_int64_t	ft_get_time(void)
{
	static long			start_time = 0;
	long unsigned int	actual_time;
	struct timeval		tv;

	if (start_time == 0)
	{
		gettimeofday(&tv, NULL);
		start_time = (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
		actual_time = 0;
	}
	else
	{
		gettimeofday(&tv, NULL);
		actual_time = (tv.tv_sec * 1000) + (tv.tv_usec / 1000) - start_time;
	}
	return (actual_time);
}

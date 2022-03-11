/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbarrier <fbarrier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/05 17:15:09 by fbarrier          #+#    #+#             */
/*   Updated: 2022/02/11 20:59:43 by fbarrier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Include/philosophers.h"

void	ft_philo_kill(t_philo *philo)
{
	u_int64_t	time;	

	time = ft_get_time() - philo->start->time_start;
	pthread_mutex_lock(&philo->lock);
	printf("%lu\t", time);
	printf("%d is dead\n", philo->position + 1);
	philo->start->status = DIED;
	pthread_mutex_unlock(&philo->lock);
}

int	ft_philo_check_dead(t_philo *philo)
{
	if ((ft_get_time() - philo->last_meal)
		>= ((u_int64_t)philo->start->time_to_die))
	{
		ft_philo_kill(philo);
		pthread_mutex_unlock(philo->start->forks_mutex);
		return (1);
	}
	return (0);
}

void	ft_sleep(t_philo *philo)
{
	ft_display(philo, SLEEP);
	ft_usleep(philo->start->time_to_sleep, philo);
}

int	ft_forks(t_philo *philo)
{
	if (philo->position % 2 == 0)
		pthread_mutex_lock(&philo->right_fork);
	else
		pthread_mutex_lock(philo->left_fork);
	ft_display(philo, TAKE_FORK);
	if (philo->position % 2 == 0)
	{
		if (pthread_mutex_lock(philo->left_fork))
		{
			pthread_mutex_unlock(&philo->right_fork);
			return (1);
		}
		ft_display(philo, TAKE_FORK);
	}
	else
	{
		if (pthread_mutex_lock(&philo->right_fork))
		{
			pthread_mutex_unlock(philo->left_fork);
			return (1);
		}
		ft_display(philo, TAKE_FORK);
	}
	return (0);
}

int	ft_eat(t_philo *philo)
{	
	if (ft_forks(philo) == 1)
		return (1);
	ft_display(philo, EAT);
	pthread_mutex_lock(philo->start->forks_mutex);
	philo->last_meal = ft_get_time();
	pthread_mutex_unlock(philo->start->forks_mutex);
	ft_usleep(philo->start->time_to_eat, philo);
	pthread_mutex_lock(philo->start->forks_mutex);
	philo->meal_count++;
	pthread_mutex_unlock(philo->start->forks_mutex);
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(&philo->right_fork);
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbarrier <fbarrier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/05 20:22:54 by fbarrier          #+#    #+#             */
/*   Updated: 2022/02/13 18:02:20 by fbarrier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Include/philosophers.h"

int	ft_display_error(char *str)
{
	write(2, "Error\n", 6);
	write(2, str, ft_strlen(str));
	write(2, "\n", 1);
	return (1);
}

int	ft_print_message(t_philo *philo, char c)
{
	if (c == TAKE_FORK)
		printf("%d has taken a fork\n", philo->position + 1);
	else if (c == EAT)
		printf("%d is eating\n", philo->position + 1);
	else if (c == LEAVE_FORK)
		printf("%d has released the forks\n", philo->position + 1);
	else if (c == SLEEP)
		printf("%d is sleeping\n", philo->position + 1);
	else if (c == THINK)
		printf("%d is thinking\n", philo->position + 1);
	else if (c == DIED)
	{
		printf("%d is dead\n", philo->position + 1);
		return (1);
	}
	else if (c == ENOUGH)
	{	
		printf("Meal count is ok\n");
		return (1);
	}
	return (0);
}

void	ft_display(t_philo *philo, char c)
{
	u_int64_t	time;	

	pthread_mutex_lock(philo->start->forks_mutex);
	if (philo->start->status == DIED)
	{
		pthread_mutex_unlock(philo->start->forks_mutex);
		return ;
	}
	time = ft_get_time() - philo->start->time_start;
	printf("%lu\t", time);
	ft_print_message(philo, c);
	pthread_mutex_unlock(philo->start->forks_mutex);
}

/* int	ft_must_eat2(t_init *start)
{
	int	i;

	i = -1;
	while (++i < start->philo_nbr)
		start->philo[i].must_eat = -1;
	return (0);
}

int	ft_must_eat(t_init *start, char **av)
{
	int	i;

	i = -1;
	if (ft_atoi(av[5]) == 0)
	{
		ft_display_error("No one eats");
		return (1);
	}
	else
	{
		while (++i < start->philo_nbr)
			start->philo[i].must_eat = ft_atoi(av[5]);
	}
	return (0);
} */

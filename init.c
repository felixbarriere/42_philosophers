/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbarrier <fbarrier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/02 06:23:29 by fbarrier          #+#    #+#             */
/*   Updated: 2022/02/02 06:23:29 by fbarrier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Include/philosophers.h"

int	ft_init_mutex(t_philo *philo)
{
	philo->start->forks_mutex = malloc(sizeof(pthread_mutex_t));
	if (!philo->start->forks_mutex)
		return (1);
	philo->start->lock = malloc(sizeof(pthread_mutex_t));
	if (!philo->start->lock)
		return (1);
	pthread_mutex_init(philo->start->forks_mutex, NULL);
	pthread_mutex_init(philo->start->lock, NULL);
	return (0);
}

void	ft_init_start(t_init *start, char **av)
{
	start->philo_nbr = ft_atoi(av[1]);
	start->time_to_die = ft_atoi(av[2]);
	start->time_to_eat = ft_atoi(av[3]);
	start->time_to_sleep = ft_atoi(av[4]);
	start->status = ALIVE;
}

t_philo	*ft_init_all(t_init **start, char **av)
{
	t_philo			*philo;
	static int		i = -1;

	ft_init_start(*start, av);
	philo = malloc(sizeof(t_philo) * (ft_atoi(av[1])));
	if (!philo)
		return (0);
	while (++i < ft_atoi(av[1]))
	{
		philo[i].start = *start;
		philo[i].position = i;
		philo[i].must_eat = -1;
		philo[i].meal_count = 0;
		philo[i].last_meal = 0;
		philo[i].status = ALIVE;
		pthread_mutex_init(&philo[i].right_fork, NULL);
		pthread_mutex_init(&philo[i].lock, NULL);
		philo[(i + 1) % philo->start->philo_nbr].left_fork
			= &philo[i].right_fork;
	}
	return (philo);
}

t_philo	*ft_init_all2(t_init **start, char **av)
{
	t_philo		*philo;
	static int	i = -1;

	ft_init_start(*start, av);
	philo = malloc(sizeof(t_philo) * (ft_atoi(av[1])));
	if (!philo)
		return (0);
	while (++i < ft_atoi(av[1]))
	{
		philo[i].start = *start;
		philo[i].position = i;
		philo[i].meal_count = 0;
		philo[i].last_meal = 0;
		philo[i].must_eat = ft_atoi(av[5]);
		pthread_mutex_init(&philo[i].lock, NULL);
		pthread_mutex_init(&philo[i].right_fork, NULL);
		philo[(i + 1) % philo->start->philo_nbr].left_fork
			= &philo[i].right_fork;
		philo[i].status = ALIVE;
	}
	return (philo);
}

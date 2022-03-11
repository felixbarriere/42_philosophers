/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbarrier <fbarrier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/02 06:24:01 by fbarrier          #+#    #+#             */
/*   Updated: 2022/02/13 17:55:16 by fbarrier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <pthread.h>
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <sys/time.h>
# include <time.h>

# define DIED		0
# define ALIVE		1
# define TAKE_FORK	2
# define EAT		3
# define LEAVE_FORK	4
# define SLEEP		5
# define THINK		6
# define ENOUGH		7

struct	s_init;

/********** enregistre les infos de chaque philo *********/

typedef struct s_philo
{
	pthread_t		philo_th;
	int				position;
	int				is_eating;
	int				must_eat;
	int				meal_count;
	int				status;
	u_int64_t		last_meal;
	u_int64_t		time_limit;

	struct s_init	*start;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	right_fork;
	pthread_mutex_t	lock;
	pthread_mutex_t	*lock2;
	pthread_mutex_t	ft_display;
}		t_philo;

/******* enregistre les infos de départ du programme ******/

typedef struct s_init
{
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				philo_nbr;
	int				status;
	u_int64_t		time_start;
	pthread_t		th;
	pthread_t		th2;
	t_philo			*philo;
	pthread_mutex_t	*forks_mutex;
	pthread_mutex_t	*lock;
}	t_init;

t_philo		*ft_init_all(t_init **start, char **av);
t_philo		*ft_init_all2(t_init **start, char **av);
int			ft_display_error(char *str);
int			ft_atoi(char *str);
int			ft_strlen(char *str);
int			ft_is_digit(char *str);
int			ft_forks(t_philo *philo);
int			ft_eat(t_philo *philo);
void		ft_sleep(t_philo *philo);
void		ft_drop_forks(t_philo *philo);
void		ft_display(t_philo *philo, char c);
u_int64_t	ft_get_time(void);
void		ft_usleep2(size_t	time, t_init *ph);
int			ft_check_error(char **av);
int			ft_must_eat(t_init *start, char **av);
int			ft_must_eat2(t_init *start);
int			ft_is_int(t_init *start);
int			ft_init_mutex(t_philo *philo);
int			ft_philo_check_dead(t_philo *philo);
void		ft_destroy_mutex(t_philo *philo);
void		ft_usleep(long unsigned int time_in_ms, t_philo *philo);
int			ft_get_status(t_philo *philo);
void		ft_one_philo(t_philo *philo);
void		ft_philo_kill(t_philo *philo);

#endif

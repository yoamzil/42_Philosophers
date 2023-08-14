/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoamzil <yoamzil@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 12:09:58 by yoamzil           #+#    #+#             */
/*   Updated: 2023/08/14 12:12:53 by yoamzil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

typedef struct s_philo
{
	int				id;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	int				ate;
	int				num_of_meals;
	int				time_left;
	int				num_of_philos;
	long			last_meal;
	pthread_mutex_t	m1;
	pthread_mutex_t	m2;
	int				time_to_sleep;
	int				died;
	int				time_to_die;
	int				time_to_eat;
	int				must_eat;
	long			first_timestamp;
	long			current_timestamp;
}	t_philo;

#endif
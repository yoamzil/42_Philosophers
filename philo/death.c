/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   death.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoamzil <yoamzil@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/01 17:08:59 by yoamzil           #+#    #+#             */
/*   Updated: 2023/09/01 22:10:09 by yoamzil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	supply(t_philo *philo, int i)
{
	long	time;

	pthread_mutex_lock(&philo->check->m_print);
	philo->check->has_died = 1;
	pthread_mutex_unlock(&philo->check->m_print);
	time = timestamp() - philo[i].first_timestamp;
	pthread_mutex_lock(&philo[i].check->m_print);
	printf("%ld %d %s\n", time, philo[i].id, "died");
	return (0);
}

int	death_checker(t_philo *philo, int ac)
{
	int		i;
	int		diff;
	int		count;

	usleep(philo->time_to_die / 2);
	while (1)
	{
		i = -1;
		count = philo->num_of_philos;
		while (++i < philo->num_of_philos)
		{
			pthread_mutex_lock(&philo->check->m2);
			diff = timestamp() - philo[i].last_meal;
			count -= (philo[i].num_of_meals >= philo->must_eat);
			pthread_mutex_unlock(&philo->check->m2);
			if (diff >= philo[i].time_to_die)
			{
				supply(philo, i);
				return (0);
			}
		}
		if (ac == 6 && count == 0)
			return (0);
	}
	return (1);
}

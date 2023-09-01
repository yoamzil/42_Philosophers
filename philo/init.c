/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoamzil <yoamzil@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 14:40:32 by yoamzil           #+#    #+#             */
/*   Updated: 2023/09/01 22:27:08 by yoamzil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_mutex(t_philo *philo, pthread_mutex_t *forks)
{
	int	i;

	i = -1;
	while (++i < philo->num_of_philos)
		pthread_mutex_init(&forks[i], NULL);
	i = 0;
	while (i < philo->num_of_philos)
	{
		philo[i].left_fork = &forks[i];
		philo[i].right_fork = &forks[(i + 1) % philo->num_of_philos];
		i++;
	}
	return (0);
}

int	init_philosophers(t_philo *philo, char **argv)
{
	int			i;
	long		time;
	t_checker	*check;

	time = timestamp();
	i = 0;
	check = malloc(sizeof(t_checker));
	check->has_died = 0;
	pthread_mutex_init(&check->m_print, NULL);
	pthread_mutex_init(&check->m2, NULL);
	while (i < philo->num_of_philos)
	{
		philo[i].first_timestamp = time;
		philo[i].last_meal = time;
		philo[i].id = i + 1;
		philo[i].num_of_meals = 0;
		philo[i].ate = 0;
		philo[i].died = 0;
		philo[i].time_to_die = ft_atoi(argv[2]);
		philo[i].time_to_eat = ft_atoi(argv[3]);
		philo[i].time_to_sleep = ft_atoi(argv[4]);
		philo[i].check = check;
		i++;
	}
	return (0);
}

int	init_data(t_philo *philo, char **argv)
{
	init_philosophers(philo, argv);
	if (philo->num_of_philos < 1 || philo->time_to_die < 0
		|| philo->time_to_eat < 0 || philo->time_to_sleep < 0)
		return (1);
	if (argv[5])
	{
		philo->must_eat = ft_atoi(argv[5]) + 1;
		if (philo->must_eat <= 0)
			return (1);
	}
	else
		philo->must_eat = -1;
	return (0);
}

void	destroy(t_philo *philo, pthread_t *threads, pthread_mutex_t *forks)
{
	pthread_mutex_destroy(&philo->check->m2);
	pthread_mutex_destroy(&philo->check->m_print);
	free(threads);
	free(forks);
	free(philo[0].check);
	free(philo);
}

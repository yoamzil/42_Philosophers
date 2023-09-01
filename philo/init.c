/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoamzil <yoamzil@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 14:40:32 by yoamzil           #+#    #+#             */
/*   Updated: 2023/08/16 13:43:28 by yoamzil          ###   ########.fr       */
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
		// pthread_mutex_init(&philo[i].check->m_print, NULL);
		// pthread_mutex_init(&philo[i].check->m2, NULL);
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
	check->is_died = 0;
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
		philo->must_eat = ft_atoi(argv[5]) + 2;
		if (philo->must_eat <= 0)
			return (1);
	}
	else
		philo->must_eat = -1;
	return (0);
}

void	destroy(t_philo *philo, pthread_t *threads, pthread_mutex_t *forks)
{
	int	i;

	i = 0;
	while (i < philo->num_of_philos)
	{
		// pthread_mutex_destroy(&philo[i]->checkm_print);
		// pthread_mutex_destroy(&philo[i].m2);
		// i++;
	}
	free(philo);
	free(threads);
	free(forks);
}

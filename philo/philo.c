/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoamzil <yoamzil@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 01:36:27 by yoamzil           #+#    #+#             */
/*   Updated: 2023/08/16 13:43:09 by yoamzil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	death_checker(t_philo *philo, int ac)
{
	int		i;
	long	time;

	usleep(philo->time_to_die / 2);
	i = 0;
	while (1)
	{
		i = 0;
		int	count = philo->num_of_philos;
		while (i < philo->num_of_philos)
		{
			int diff;
		
			pthread_mutex_lock(&philo->check->m2);
			diff = timestamp() - philo[i].last_meal;
			count -= (philo[i].num_of_meals >= philo->must_eat);
			pthread_mutex_unlock(&philo->check->m2);

			if (diff >= philo[i].time_to_die)
			{
				pthread_mutex_lock(&philo->check->m_print);
				philo->check->is_died = 1;
				pthread_mutex_unlock(&philo->check->m_print);
				// pthread_mutex_unlock(&philo[i].m_print);
				time = timestamp() - philo[i].first_timestamp;
				pthread_mutex_lock(&philo[i].check->m_print);
					printf("%ld %d %s\n", time, philo[i].id, "died");
				// pthread_mutex_unlock(&philo[i].check->m_print);

				// pthread_mutex_lock(&philo[i].m2);
				// pthread_mutex_unlock(&philo[i].m2);
				// pthread_mutex_unlock(&philo[i].m_print);
				return (0);
			}
			// pthread_mutex_unlock(&philo[i].m_print);
			i++;
		}
		if (ac == 6 && count == 0)
			return (0);
	}
	return (1);
}

void	eating(t_philo *philo)
{
	pthread_mutex_lock(philo->left_fork);
	printing(philo, "has taken a fork");
	pthread_mutex_lock(philo->right_fork);
	printing(philo, "has taken a fork");
	printing(philo, "is eating");

	pthread_mutex_lock(&philo->check->m2);
	philo->num_of_meals++;
	philo->last_meal = timestamp();
	pthread_mutex_unlock(&philo->check->m2);

	ft_usleep(philo->time_to_eat);
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
}

void	*routine(void *void_philo)
{
	t_philo	*philo;
	int		variable;
	int		first_time = 1;

	philo = (t_philo *)void_philo;
	// if (philo->id % 2 == 0)
	// 	ft_usleep(philo->time_to_eat);
	// pthread_mutex_lock(&philo->m2);
	variable = philo->check->is_died;
	// pthread_mutex_unlock(&philo->m2);
	while (!variable)
	{
		// pthread_mutex_lock(&philo->m2);
		// variable = philo->died;
		// pthread_mutex_unlock(&philo->m2);
		printing(philo, "is thinking");
		/**/
			if (philo->id % 2 == 0 && first_time)
			{
				ft_usleep(philo->time_to_eat / 2);
				first_time = 0;
			}

		/**/
		eating(philo);
		printing(philo, "is sleeping");
		ft_usleep(philo->time_to_sleep);
	}
	return (NULL);
}

int	starting_thread(pthread_t *threads, t_philo *philo, int ac)
{
	int	i;

	i = 0;
	while (i < philo->num_of_philos)
	{
		if (pthread_create(&threads[i], NULL, routine, &philo[i]))
		{
			printf("Failed creating threads\n");
			return (1);
		}
		i++;
	}
	if (!death_checker(philo, ac))
		return (0);
	i = 0;
	while (i < philo->num_of_philos)
	{
		if (pthread_join(threads[i], NULL))
			return (1);
		i++;
	}
	return (0);
}

int	main(int argc, char **argv)
{
	int				variable;
	pthread_t		*threads;
	pthread_mutex_t	*forks;
	t_philo			*philo;

	if (argc < 5 || argc > 6 || checker(argv))
	{
		printf("Error: Wrong arguments\n");
		return (1);
	}
	variable = ft_atoi(argv[1]);
	if (variable <= 0)
		return (1);
	philo = malloc(sizeof(t_philo) * variable);
	threads = malloc(sizeof(pthread_t) * variable);
	forks = malloc(sizeof(pthread_mutex_t) * variable);
	if (!philo || !threads || !forks)
		return (1);
	philo->num_of_philos = variable;
	if (init_data(philo, argv) || init_mutex(philo, forks))
	{
		printf("Error: Wrong arguments\n");
		return (1);
	}
	starting_thread(threads, philo, argc);
	// destroy(philo, threads, forks);
	return (0);
}

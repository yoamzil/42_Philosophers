/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoamzil <yoamzil@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 01:36:27 by yoamzil           #+#    #+#             */
/*   Updated: 2023/09/01 22:29:23 by yoamzil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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
	int		first_time;

	philo = (t_philo *)void_philo;
	variable = philo->check->has_died;
	first_time = 1;
	while (!variable)
	{
		printing(philo, "is thinking");
		if (philo->id % 2 == 0 && first_time)
		{
			ft_usleep(philo->time_to_eat / 2);
			first_time = 0;
		}
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
		return (1);
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
	destroy(philo, threads, forks);
	return (0);
}

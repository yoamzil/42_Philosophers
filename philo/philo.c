/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoamzil <yoamzil@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 01:36:27 by yoamzil           #+#    #+#             */
/*   Updated: 2023/07/19 21:17:14 by yoamzil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_atoi(const char *str)
{
	int		i;
	int		number;
	int		sign;

	i = 0;
	number = 0;
	sign = 1;
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;
	while (str[i] == '+' || str[i] == '-')
	{
		if (str[i + 1] == '+' || str[i + 1] == '-')
			return (0);
		else if (str[i] == '-')
			sign *= (-1);
		i++;
	}
	while (str[i] != '\0' && str[i] >= '0' && str[i] <= '9')
	{
		number = (number * 10) + (str[i] - '0');
		i++;
	}
	return (number * sign);
}

int	checker(char **argv)
{
    int i;
	int	j;
    i = 1;
    while (argv[i])
	{
        j = 0;
        while (argv[i][j])
		{
            if (argv[i][j] != ' ' && (argv[i][j] < '0' || argv[i][j] > '9'))
                return (1);
            j++;
        }
        i++;
    }
    return (0);
}

int init_mutex(t_data *data)
{
    int i;
    int num_of_philos;
	
	i = 0;
	num_of_philos = data->num_of_philos;
	data->forks = malloc(sizeof(pthread_mutex_t) * num_of_philos);
    if (data->forks == NULL)
        return (1);
    while (i < num_of_philos)
	{
        if (pthread_mutex_init(&(data->forks[i]), NULL))
		{
            free(data->forks);
            return (1);
		}
        i++;
    }
    return (0);
}
int	init_philosophers(t_data *data, t_philo *philo)
{
	int i;

	i = data->num_of_philos;
	while (i > 0)
	{
		philo->id = i;
		// philo->x_ate = 0;
		philo->left_fork = i;
		philo->right_fork = (i + 1) % data->num_of_philos;
		// philo->t_last_meal = 0;
		// philo->rules = rules;
		// printf("philo %d: left fork: %d, right fork: %d\n", philo->id, philo->left_fork, philo->right_fork);
		i--;
	}
	return (0);
}

int	init_data(t_data *data, t_philo *philo, char **argv)
{
	data->num_of_philos = ft_atoi(argv[1]);
	data->time_to_die = ft_atoi(argv[2]);
	data->time_to_eat = ft_atoi(argv[3]);
	data->time_to_sleep = ft_atoi(argv[4]);
	data->full = 0;
	data->died = 0;
	if (data->num_of_philos < 1 || data->time_to_die < 0 || data->time_to_eat < 0 || data->time_to_sleep < 0)
		return (1);
	if (argv[5])
	{
		data->must_eat = ft_atoi(argv[5]);
		if (data->must_eat <= 0)
			return (1);
	}
	else
		data->must_eat = -1;
	if (init_mutex(data))
		return (2);
	init_philosophers(data, philo);
	return (0);
}



int	main(int argc, char **argv)
{
	t_data	data;
	t_philo	philo;
	
	if (argc < 5 || argc > 6)
	{
		printf("Error: Wrong number of arguments\n");
		return (1);
	}
	if (checker(argv))
	{
		printf("Error: Wrong arguments\n");
		return (1);
	}
	if (init_data(&data, &philo, argv))
	{
		printf("Error: Wrong arguments\n");
		return (1);
	}
}

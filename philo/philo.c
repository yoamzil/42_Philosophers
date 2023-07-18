/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoamzil <yoamzil@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 01:36:27 by yoamzil           #+#    #+#             */
/*   Updated: 2023/07/18 18:55:47 by yoamzil          ###   ########.fr       */
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

int	init_data(t_data *data, char **argv)
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
	// if (init_mutex(data))
	// 	return (2);
	// init_philosophers(data);
	return (0);
}

int	main(int argc, char **argv)
{
	t_data	data;
	
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
	if (init_data(&data, argv))
	{
		printf("Error: Wrong arguments\n");
		return (1);
	}
}
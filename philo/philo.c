/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoamzil <yoamzil@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 01:36:27 by yoamzil           #+#    #+#             */
/*   Updated: 2023/07/18 01:20:25 by yoamzil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"


// void	*philo(void *arg)
// {
// 	t_philo	*philo;

// 	philo = (t_philo*)arg;
// 	while (1)
// 	{
// 		// philo_eat(philo);
// 		// philo_sleep(philo);
// 		// philo_think(philo);
// 	}
// 	return (NULL);
// }

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

int	main(int argc, char **argv)
{
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
}
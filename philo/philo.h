#ifndef PHILO_H
#define PHILO_H

#include <pthread.h>
#include <stdio.h>

typedef struct s_philo
{
    int num;
    int id;
    struct s_data *data;
} t_philo;

typedef struct s_data
{
    int num_of_philos;
    int time_to_die;
    int time_to_eat;
    int time_to_sleep;
    int must_eat;
} t_data;

#endif
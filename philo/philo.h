#ifndef PHILO_H
#define PHILO_H

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

typedef struct s_philo
{
    int id;
    int left_fork;
    int right_fork;
    struct s_data *data;
} t_philo;

typedef struct s_data
{
    int num_of_philos;
    int time_to_die;
    int time_to_eat;
    int time_to_sleep;
    int must_eat;
    int full;
    int died;
    long first_timestamp;
    long current_timestamp;
    pthread_mutex_t *forks;
    t_philo *philo;
} t_data;

#endif
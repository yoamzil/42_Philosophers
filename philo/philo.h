#ifndef PHILO_H
#define PHILO_H

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

typedef struct s_philo
{
    int id;
    pthread_mutex_t *left_fork;
    pthread_mutex_t *right_fork;
    pthread_mutex_t mutex;
    struct s_data *data;
} t_philo;

typedef struct s_data
{
    pthread_t   *thread_id;
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
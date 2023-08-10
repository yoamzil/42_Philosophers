#ifndef PHILO_H
#define PHILO_H

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <unistd.h>

typedef struct s_philo
{
    int id;
    pthread_t   *thread_id;
    pthread_mutex_t *forks;
    int left_fork;
    int right_fork;
    int ate;
    int num_of_meals;
    int time_left;
    int num_of_philos;
    long long last_meal;
    pthread_mutex_t mutex;
    struct s_data *data;
} t_philo;

typedef struct s_data
{
    
    
    int time_to_die;
    int time_to_eat;
    int time_to_sleep;
    int must_eat;
    int full;
    int died;
    long first_timestamp;
    long current_timestamp;
} t_data;

#endif
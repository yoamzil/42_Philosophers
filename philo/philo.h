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
    pthread_mutex_t *left_fork;
    pthread_mutex_t *right_fork;
    int ate;
    int num_of_meals;
    int time_left;
    int num_of_philos;
    long last_meal;
    pthread_mutex_t m1;
    struct s_data *data;
    int time_to_sleep;
    int full;
    int died;
    int time_to_die;
    int time_to_eat;
    int must_eat;
    long first_timestamp;
    long current_timestamp;
} t_philo;

typedef struct s_data
{
    
    
  
} t_data;

#endif
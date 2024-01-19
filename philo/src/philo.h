/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxmakagonov <maxmakagonov@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 15:14:34 by mmakagon          #+#    #+#             */
/*   Updated: 2024/01/19 14:54:37 by maxmakagono      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# define DEAD -1
# define ALL_FINE 0
# define EATING 1
# define SLEEPING 2
# define THINKING 3
# define HUNGRY 4
# define ATE_ENOUGH 5
# define TAKING_FORK 6
# define TAKEN 7
# define NOT_TAKEN	8

# define ERROR 9
# define ERR_WRONG_INPUT 10
# define ERR_FORKS_INIT_FAILED 11
# define ERR_PHILOS_INIT_FAILED 12
# define STOP 42

# define STR_DEAD "died\n"
# define STR_EATING "is eating\n"
# define STR_SLEEPING "is sleeping\n"
# define STR_THINKING "is thinking\n"
# define STR_FORK "has taken a fork\n"

# include <string.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>
# include <pthread.h>
# include <stdbool.h>
# include <limits.h>

typedef struct s_fork {
	int				id;
	pthread_mutex_t	mutex;
	int				is_taken;
}				t_fork;

typedef struct s_rules {
	int				philos_total;
	long			mcsec_to_die;
	long			mcsec_to_eat;
	long			mcsec_to_sleep;
	long			mcsec_start;
	int				times_must_eat;
}				t_rules;

typedef struct s_common {
	pthread_mutex_t	state_change;
	int				philos_ate_enough;
	bool			someone_died;
}				t_common;

typedef struct s_philsopher {
	int				id;
	int				state;
	int				times_ate;
	long			last_meal;
	long			next_meal_before;
	long			mcsec_current;
	t_fork			*left_fork;
	t_fork			*right_fork;
	t_rules			rules;
	t_common		*common_data;
	pthread_t		thread;
}				t_philosopher;

typedef struct s_data {
	t_fork			forks[200];
	t_philosopher	philos[200];
	t_rules			rules;
	t_common		common_data;
}					t_data;

// initialize
void		ph_initialize(char **argv, t_data *data);

// philo process
void		*ph_process(void *arg);
int			ph_eat(t_philosopher *philo, t_fork *first_fork, t_fork *second_fork);
int			ph_state_change(t_philosopher *philo, int new_state);
void		ph_die(long mcsec_current, t_philosopher *philo);

// forks
void		ph_fork_assign(t_philosopher *philo, t_fork *first_fork, t_fork *second_fork);
int			ph_fork_take(t_philosopher *philo, t_fork *fork);
void		ph_fork_put(t_fork *fork);

// atoi
long		ph_atol(const char *str);

// utils
long		ph_get_current_mcsec(long *mcsec_current);
void		ph_exit(int code, t_data *data);

#endif

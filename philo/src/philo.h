/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxmakagonov <maxmakagonov@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 15:14:34 by mmakagon          #+#    #+#             */
/*   Updated: 2024/01/17 13:40:07 by maxmakagono      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# define DEAD 0
# define EATING 1
# define SLEEPING 2
# define THINKING 3
# define ATE_ENOUGH 4
# define TAKING_FORK 5

# define ALL_FINE 6
# define ERROR 7
# define ERR_WRONG_INPUT 8
# define ERR_FORKS_INIT_FAILED 9
# define ERR_PHILOS_INIT_FAILED 10
# define TAKEN 11
# define NOT_TAKEN	12
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
	long long		mcsec_to_die;
	long long		mcsec_to_eat;
	long long		mcsec_to_sleep;
	long long		mcsec_start;
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
	long long		last_meal;
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

// atoi
long long	ph_atoll(const char *str);

// utils
void		ph_get_current_mcsec(long long *mcsec_current);
long long 	ph_timeval_to_mcsec(struct timeval t);
void		ph_exit(int code, t_data *data);

#endif

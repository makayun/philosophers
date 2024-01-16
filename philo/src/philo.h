/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxmakagonov <maxmakagonov@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 15:14:34 by mmakagon          #+#    #+#             */
/*   Updated: 2024/01/15 18:38:26 by maxmakagono      ###   ########.fr       */
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

# define STR_DEAD "died\n"
# define STR_EATING "is eating\n"
# define STR_SLEEPING "is sleeping\n"
# define STR_THINKING "is thinking\n"
# define STR_FORK "has taken a fork\n"

# define ALL_FINE 0
# define ERROR 1
# define ERR_WRONG_INPUT 2
# define ERR_FORKS_INIT_FAILED 3
# define ERR_PHILOS_INIT_FAILED 4
# define STOP 42

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
	bool			is_taken;
}				t_fork;

typedef struct s_rules {
	int				philos_total;
	suseconds_t		microsec_to_die;
	suseconds_t		microsec_to_eat;
	suseconds_t		microsec_to_sleep;
	struct timeval	mcsec_start;
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
	struct timeval	last_state_change;
	t_fork			*left_fork;
	t_fork			*right_fork;
	pthread_t		thread;
	t_rules			rules;
	t_common		*common_data;
	int				times_ate;
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
time_t		mcsec_to_mlsec(time_t input);
void		ph_exit(int code, t_data *data);

#endif

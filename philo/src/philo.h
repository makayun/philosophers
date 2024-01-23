/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxmakagonov <maxmakagonov@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 15:14:34 by mmakagon          #+#    #+#             */
/*   Updated: 2024/01/23 09:26:14 by maxmakagono      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# define DEAD 0
# define ALL_FINE 1
# define EATING 2
# define SLEEPING 3
# define THINKING 4
# define HUNGRY 5
# define ATE_ENOUGH 6
# define TAKING_FORK 7

# define ERROR 8
# define ERR_WRONG_INPUT 9
# define ERR_FORKS_INIT_FAILED 10
# define ERR_PHILOS_INIT_FAILED 11
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
	pthread_mutex_t	mutex;
	bool			is_taken;
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
int			ph_eat(t_philosopher *philo, t_fork *first_fork, t_fork *second_fork, long offset);
int			ph_state_change(t_philosopher *philo, int new_state);
void		ph_die(long mcsec_current, t_philosopher *philo);

// forks
int			ph_fork_take(t_philosopher *philo, t_fork *fork);
void		ph_fork_put(t_fork *fork);

// atoi
long		ph_atol(const char *str);

// utils
void		ph_wait_until(t_philosopher *philo, long timestamp);
void		ph_print_message(t_philosopher *philo, char *str);
long		ph_get_current_mcsec(long *mcsec_current);
void		ph_exit(int code, t_data *data);

#endif

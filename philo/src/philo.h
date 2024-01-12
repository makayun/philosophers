/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmakagon <mmakagon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 15:14:34 by mmakagon          #+#    #+#             */
/*   Updated: 2024/01/12 15:05:51 by mmakagon         ###   ########.fr       */
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

typedef struct s_fork {
	int				id;
	pthread_mutex_t	mutex;
	bool			is_taken;
}				t_fork;

typedef struct s_rules {
	int				philos_total;
	time_t			microsec_to_die;
	time_t			microsec_to_eat;
	time_t			microsec_to_sleep;
	int				times_must_eat;
	int				philos_ate_enough;
	bool			someone_died;
	pthread_mutex_t	state_change;
}				t_rules;

typedef struct s_philsopher {
	int			id;
	int			state;
	time_t		last_state_change;
	t_fork		*left_fork;
	t_fork		*right_fork;
	pthread_t	thread;
	t_rules		*rules;
	int			times_ate;
}				t_philosopher;

typedef struct s_data {
	t_fork			forks[200];
	t_philosopher	philos[200];
	t_rules			rules;
	time_t			mcsec_start;
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

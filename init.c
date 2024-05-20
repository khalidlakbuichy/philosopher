/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klakbuic <klakbuic@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 16:45:54 by klakbuic          #+#    #+#             */
/*   Updated: 2024/05/20 12:14:22 by klakbuic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	assign_forks(t_philo *philo, int philo_pos)
{
	size_t nb_philos;
	
	nb_philos = philo->data->nb_philos;
	philo->first_fork = philo->data->forks[philo_pos];
	philo->second_fork = philo->data->forks[(philo_pos + 1) % nb_philos];
	if (philo->id % 2)
	{
		philo->first_fork = philo->data->forks[(philo_pos + 1) % nb_philos];
		philo->second_fork = philo->data->forks[philo_pos];
	}
}

t_forks	**init_forks(t_data *data)
{
	int		i;
	t_forks	**forks;

	forks = (t_forks **)malloc(sizeof(t_forks *) * data->nb_philos);
	if (!forks)
		ft_error("Error: malloc failed\n");
	i = -1;
	while (++i < data->nb_philos)
	{
		forks[i] = (t_forks *)malloc(sizeof(t_forks));
		if (!forks[i])
			ft_error("Error: malloc failed\n");
		forks[i]->id = i;
		pthread_mutex_init(&forks[i]->mutex, NULL);
	}
	return (forks);
}

t_philo	*init_philos(t_data *data)
{
	t_philo	**philos;

	philos = (t_philo **)malloc(sizeof(t_philo *) * data->nb_philos);
	if (!philos)
		ft_error("Error: malloc failed\n");
	for (int i = 0; i < data->nb_philos; i++)
	{
		philos[i] = (t_philo *)malloc(sizeof(t_philo));
		if (!philos[i])
			ft_error("Error: malloc failed\n");
		philos[i]->id = i + 1;
		// philos[i]->print = &data->print;
		// philos[i]->stop = &data->stop;
		assign_forks(philos[i], i);
	}
	return (philos);
}

t_data	*init(int ac, char **av)
{
	t_data	*data;

	data = malloc(sizeof(t_data));
	if (!data)
		ft_error("Error: malloc failed\n");
	data->nb_philos = ft_atoi(av[1]);
	data->time_to_die = ft_atoi(av[2]);
	data->time_to_eat = ft_atoi(av[3]);
	data->time_to_sleep = ft_atoi(av[4]);
	if (ac == 6)
		data->max_meals = ft_atoi(av[5]);
	else
		data->max_meals = -1;
	data->forks = init_forks(data);
	data->philos = init_philos(data);
	assing_forks(data);
	return (data);
}

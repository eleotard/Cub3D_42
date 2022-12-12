/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_destroy.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eleotard <eleotard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/12 23:57:40 by eleotard          #+#    #+#             */
/*   Updated: 2022/12/12 23:57:57 by eleotard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub.h"

void	ft_print_error_exit(char *error)
{
	ft_putstr_fd(error, 2);
	exit (-1);
}

void	ft_destroy_all(char **map, void *mlx, void *win)
{
	if (map)
		ft_destroy_map(map);
	if (win)
		mlx_destroy_window(mlx, win);
	if (mlx)
	{
		mlx_destroy_display(mlx);
		free(mlx);
	}	
}

void	ft_destroy_map(char **map)
{
	int	k;

	k = 0;
	while (map[k])
		k++;
	while (k >= 0)
	{
		free(map[k]);
		k--;
	}
	free(map);
}

void	ft_destroy_all_message(char **map, void	*mlx, char *message)
{
	ft_destroy_all(map, mlx, NULL);
	ft_print_error_exit(message);
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_destroy.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eleotard <eleotard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/12 23:57:40 by eleotard          #+#    #+#             */
/*   Updated: 2023/01/13 18:21:59 by eleotard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub.h"

void	destroyIntTab(int **pixTab)
{
	int	k;

	k = 3;
	while (k >= 0)
	{
		free(pixTab[k]);
		k--;
	}
	free(pixTab);
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

void	ft_print_error_exit(char *error)
{
	ft_putstr_fd(error, 2);
	exit (-1);
}

void	destroyAllImgs(t_vars *vars)
{
	if (vars->textures[0].ptr)
		mlx_destroy_image(vars->mlx, vars->textures[0].ptr);
	if (vars->textures[1].ptr)
		mlx_destroy_image(vars->mlx, vars->textures[1].ptr);
	if (vars->textures[2].ptr)
		mlx_destroy_image(vars->mlx, vars->textures[2].ptr);
	if (vars->textures[3].ptr)
		mlx_destroy_image(vars->mlx, vars->textures[3].ptr);
	if (vars->game_img.ptr)
		mlx_destroy_image(vars->mlx, vars->game_img.ptr);
}

void	destroyAllIntTabs(t_vars *vars)
{
	if (vars->north)
		destroyIntTab(vars->north);
	if (vars->south)
		destroyIntTab(vars->south);
	if (vars->east)
		destroyIntTab(vars->east);
	if (vars->west)
		destroyIntTab(vars->west);
}

void	ft_destroy_all(char **map, void *mlx, void *win, t_vars *vars)
{
	if (vars)
	{
		destroyAllImgs(vars);
		destroyAllIntTabs(vars);
	}
	if (map)
		ft_destroy_map(map);
	if (win)
		mlx_destroy_window(mlx, win);
	if (mlx)
	{
		mlx_destroy_display(mlx);
		free(mlx);
	}
	exit(-1);
}


void	ft_destroy_all_message(char **map, void	*mlx, char *message)
{
	ft_destroy_all(map, mlx, NULL, NULL);
	ft_print_error_exit(message);
}
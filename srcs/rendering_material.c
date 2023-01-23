/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering_material.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eleotard <eleotard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 20:45:19 by eleotard          #+#    #+#             */
/*   Updated: 2023/01/23 14:45:31 by eleotard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub.h"

void	define_projplan_dist(t_vars *vars)
{
	vars->projplan_dist = (vars->game_win_height / 2)
		/ tan(FOV_ANGLE / 2);
}

void	find_wall_strip_heights(t_vars *vars)
{
	int	i;

	i = -1;
	while (++i < vars->ray_nb)
		vars->rays[i].wall_strip_height = (vars->tile_sz * vars->projplan_dist)
			/ vars->rays[i].no_fisheye_dist;
}

int	**create_pixel_tab(t_vars *vars, t_img *texture)
{
	int	i;
	int	j;
	int	k;
	int	**tab;

	tab = malloc(sizeof(int *) * (vars->tile_sz));
	if (!tab)
	{
		ft_destroy_all(vars->map, vars->mlx, vars->game_win, vars);
		exit (-1);
	}
	i = -1;
	k = 0;
	while (++i < vars->tile_sz)
	{
		tab[i] = malloc(sizeof(int) * (vars->tile_sz));
		if (!tab[i])
			ft_destroy_all(vars->map, vars->mlx, vars->game_win, vars);
		j = -1;
		while (++j < vars->tile_sz)
			tab[i][j] = *((unsigned int *)texture->addr + k++);
	}
	return (tab);
}

void	init_pixel_tabs(t_vars *vars)
{
	vars->north = create_pixel_tab(vars, &vars->textures[0]);
	vars->south = create_pixel_tab(vars, &vars->textures[1]);
	vars->west = create_pixel_tab(vars, &vars->textures[2]);
	vars->east = create_pixel_tab(vars, &vars->textures[3]);
}

void	init_wall_top_bottom_pixels(t_vars *vars, t_ray *ray)
{
	ray->wall_top_pixel = (vars->game_win_height / 2)
		- (ray->wall_strip_height / 2);
	if (ray->wall_top_pixel < 0)
		ray->wall_top_pixel = 0;
	ray->wall_bottom_pixel = (vars->game_win_height / 2)
		+ (ray->wall_strip_height / 2);
	if (ray->wall_bottom_pixel > vars->game_win_height)
		ray->wall_bottom_pixel = vars->game_win_height;
}

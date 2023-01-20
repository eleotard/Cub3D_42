/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rays_material.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eleotard <eleotard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 18:34:40 by eleotard          #+#    #+#             */
/*   Updated: 2023/01/20 18:02:14 by eleotard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub.h"

void	update_rays_angles(t_vars *vars)
{
	int			i;
	static int	status;

	if (status == 0)
	{
		vars->ray_nb = vars->game_win_wide;
		vars->angle_step = FOV_ANGLE / vars->ray_nb;
		vars->rays = malloc(sizeof(t_ray) * vars->ray_nb);
		if (!vars->rays)
		{
			ft_destroy_all(vars->map, vars->mlx, vars->minimap.win, vars);
			exit(-1);
		}
		status++;
	}
	vars->rays[0].ray_angle = vars->player.rotation.y - (FOV_ANGLE / 2);
	i = 0;
	while (i < vars->ray_nb)
	{
		i++;
		if (i < vars->ray_nb && vars->ray_nb > 0)
			vars->rays[i].ray_angle = vars->rays[i - 1].ray_angle \
				+ vars->angle_step;
	}
}

void	update_rays_orientation(t_vars *vars)
{
	int	i;

	i = -1;
	while (++i < vars->ray_nb)
	{
		vars->rays[i].is_ray_facing_up = 0;
		vars->rays[i].is_ray_facing_down = 0;
		vars->rays[i].is_ray_facing_left = 0;
		vars->rays[i].is_ray_facing_right = 0;
		if (sin(vars->rays[i].ray_angle) < 0)
			vars->rays[i].is_ray_facing_up = 1;
		else
			vars->rays[i].is_ray_facing_down = 1;
		if (cos(vars->rays[i].ray_angle) < 0)
			vars->rays[i].is_ray_facing_left = 1;
		else
			vars->rays[i].is_ray_facing_right = 1;
	}
}

void	find_ray_texture(t_vars *vars, t_ray *ray)
{
	ray->texture = 0;
	if (ray->was_hit_horizontal == 1
		&& vars->player.pos.y <= ray->goodcoll_y)
		ray->texture = 1;
	else if (ray->was_hit_horizontal == 1
		&& vars->player.pos.y > ray->goodcoll_y)
		ray->texture = 0;
	else if (ray->was_hit_vertical == 1
		&& vars->player.pos.x > ray->goodcoll_x)
		ray->texture = 2;
	else if (ray->was_hit_vertical == 1
		&& vars->player.pos.x <= ray->goodcoll_x)
		ray->texture = 3;
}

void	set_good_distance(t_vars *vars, t_ray *ray)
{
	ray->was_hit_horizontal = 0;
	ray->was_hit_vertical = 0;
	if (ray->dist_coll_horiz == -1)
		ray->was_hit_vertical = 1;
	else if (ray->dist_coll_vert == -1)
		ray->was_hit_horizontal = 1;
	else if (ray->dist_coll_vert <= ray->dist_coll_horiz)
		ray->was_hit_vertical = 1;
	else if (ray->dist_coll_horiz <= ray->dist_coll_vert)
		ray->was_hit_horizontal = 1;
	if (ray->was_hit_vertical)
	{
		ray->goodcoll_x = ray->collptvert_x;
		ray->goodcoll_y = ray->collptvert_y;
		ray->good_dist = ray->dist_coll_vert;
	}
	else
	{
		ray->goodcoll_x = ray->collpthoriz_x;
		ray->goodcoll_y = ray->collpthoriz_y;
		ray->good_dist = ray->dist_coll_horiz;
	}
	ray->no_fisheye_dist = ray->good_dist
		* cos(ray->ray_angle - vars->player.rotation.y);
}

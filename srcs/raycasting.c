/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eleotard <eleotard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/01 17:16:54 by eleotard          #+#    #+#             */
/*   Updated: 2023/01/16 20:25:55 by eleotard         ###   ########.fr       */
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

void	find_coll_vert(t_vars *vars, t_ray *ray, t_rc rc)
{
	int		found;

	found = 0;
	if (rc.yintercept <= 0 || rc.yintercept
		>= (ft_map_height(vars->map)) * vars->tile_sz)
	{
		ray->dist_coll_vert = -1;
		return ;
	}
	if (vars->map[(int)rc.yintercept / vars->tile_sz]
		[(int)rc.xintercept / vars->tile_sz] == '1')
	{
		ray->collptvert_y = rc.yintercept;
		ray->collptvert_x = rc.xintercept;
		ray->dist_coll_vert = sqrt(fabs(vars->player.pos.x - rc.xintercept) \
			* fabs(vars->player.pos.x - rc.xintercept) \
			+ fabs(vars->player.pos.y - rc.yintercept) \
			* fabs(vars->player.pos.y - rc.yintercept));
		found = 1;
		return ;
	}
	ray->collptvert_x = rc.xintercept;
	ray->collptvert_y = rc.yintercept;
	while (found == 0)
	{
		ray->collptvert_x += rc.xstep;
		ray->collptvert_y += rc.ystep;
		if (ray->collptvert_y <= 0 || ray->collptvert_y
			>= (ft_map_height(vars->map) * vars->tile_sz))
		{
			ray->dist_coll_vert = -1;
			break ;
		}
		if (vars->map[(int)ray->collptvert_y / vars->tile_sz]
			[(int)ray->collptvert_x / vars->tile_sz] == '1')
		{
			ray->dist_coll_vert = sqrt(fabs(vars->player.pos.x
						- ray->collptvert_x)
					* fabs(vars->player.pos.x - ray->collptvert_x) \
					+ fabs(vars->player.pos.y - ray->collptvert_y) \
					* fabs(vars->player.pos.y - ray->collptvert_y));
			found = 1;
		}
	}
}

void	cast_vert_ray(t_vars *vars, t_ray *ray)
{
	t_rc	rc;

	rc.xintercept = floor(vars->player.pos.x / vars->tile_sz)
		* vars->tile_sz - 0.1;
	if (ray->is_ray_facing_right)
		rc.xintercept += vars->tile_sz + 0.1;
	rc.yintercept = vars->player.pos.y + (rc.xintercept - vars->player.pos.x)
		* tan(ray->ray_angle);
	rc.xstep = vars->tile_sz;
	if (ray->is_ray_facing_left)
		rc.xstep *= -1;
	rc.ystep = vars->tile_sz * tan(ray->ray_angle);
	if (ray->is_ray_facing_up && rc.ystep > 0)
		rc.ystep *= -1;
	if (ray->is_ray_facing_down && rc.ystep < 0)
		rc.ystep *= -1;
	find_coll_vert(vars, ray, rc);
}

void	find_coll_horiz(t_vars *vars, t_ray *ray, t_rc rc)
{
	int		found;

	found = 0;
	if (rc.xintercept <= 0 || rc.xintercept
		>= (ft_map_wide(vars->map)) * vars->tile_sz)
	{
		ray->dist_coll_horiz = -1;
		return ;
	}
	if (vars->map[(int)rc.yintercept / vars->tile_sz]
		[(int)rc.xintercept / vars->tile_sz] == '1')
	{
		ray->collpthoriz_y = rc.yintercept;
		ray->collpthoriz_x = rc.xintercept;
		ray->dist_coll_horiz = sqrt(fabs(vars->player.pos.x - rc.xintercept) \
			* fabs(vars->player.pos.x - rc.xintercept) \
			+ fabs(vars->player.pos.y - rc.yintercept) \
			* fabs(vars->player.pos.y - rc.yintercept));
		found = 1;
		return ;
	}
	ray->collpthoriz_x = rc.xintercept;
	ray->collpthoriz_y = rc.yintercept;
	while (found == 0)
	{
		ray->collpthoriz_x += rc.xstep;
		ray->collpthoriz_y += rc.ystep;
		if (ray->collpthoriz_x <= 0 || ray->collpthoriz_x
			>= (ft_map_wide(vars->map) * vars->tile_sz))
		{
			ray->dist_coll_horiz = -1;
			break ;
		}
		if (vars->map[(int)ray->collpthoriz_y / vars->tile_sz]
			[(int)ray->collpthoriz_x / vars->tile_sz] == '1')
		{
			ray->dist_coll_horiz = sqrt(fabs(vars->player.pos.x
						- ray->collpthoriz_x)
					* fabs(vars->player.pos.x - ray->collpthoriz_x)
					+ fabs(vars->player.pos.y - ray->collpthoriz_y)
					* fabs(vars->player.pos.y - ray->collpthoriz_y));
			found = 1;
		}
	}
}

void	cast_horiz_ray(t_vars *vars, t_ray *ray)
{
	t_rc	rc;

	rc.yintercept = floor(vars->player.pos.y / vars->tile_sz)
		* vars->tile_sz - 0.1;
	if (ray->is_ray_facing_down)
		rc.yintercept += vars->tile_sz + 0.1;
	rc.xintercept = vars->player.pos.x + (rc.yintercept - vars->player.pos.y)
		/ tan(ray->ray_angle);
	rc.ystep = vars->tile_sz;
	if (ray->is_ray_facing_up)
		rc.ystep *= -1;
	rc.xstep = vars->tile_sz / tan(ray->ray_angle);
	if (ray->is_ray_facing_left && rc.xstep > 0)
		rc.xstep *= -1;
	if (ray->is_ray_facing_right && rc.xstep < 0)
		rc.xstep *= -1;
	find_coll_horiz(vars, ray, rc);
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

void	cast_all_rays(t_vars *vars)
{
	int	i;

	update_rays_angles(vars);
	update_rays_orientation(vars);
	i = -1;
	while (++i < vars->ray_nb)
	{
		cast_horiz_ray(vars, &(vars->rays[i]));
		cast_vert_ray(vars, &(vars->rays[i]));
		set_good_distance(vars, &(vars->rays[i]));
		find_ray_texture(vars, &(vars->rays[i]));
	}
}

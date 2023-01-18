/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eleotard <eleotard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/01 17:16:54 by eleotard          #+#    #+#             */
/*   Updated: 2023/01/18 18:39:04 by eleotard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub.h"

int	precheck_coll_horiz(t_vars *vars, t_ray *ray, t_rc *rc, int *found)
{
	*found = 0;
	if (rc->xintercept <= 0 || rc->xintercept
		>= (ft_map_wide(vars->map)) * vars->tile_sz)
	{
		ray->dist_coll_horiz = -1;
		return (1);
	}
	ray->collpthoriz_x = rc->xintercept;
	ray->collpthoriz_y = rc->yintercept;
	if (vars->map[(int)rc->yintercept / vars->tile_sz]
		[(int)rc->xintercept / vars->tile_sz] == '1')
	{
		ray->dist_coll_horiz = sqrt(fabs(vars->player.pos.x - rc->xintercept) \
			* fabs(vars->player.pos.x - rc->xintercept) \
			+ fabs(vars->player.pos.y - rc->yintercept) \
			* fabs(vars->player.pos.y - rc->yintercept));
		return (1);
	}
	return (0);
}

void	find_coll_horiz(t_vars *vars, t_ray *ray, t_rc *rc)
{
	int		found;

	if (precheck_coll_horiz(vars, ray, rc, &found))
		return ;
	while (found == 0)
	{
		ray->collpthoriz_x += rc->xstep;
		ray->collpthoriz_y += rc->ystep;
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
	find_coll_horiz(vars, ray, &rc);
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

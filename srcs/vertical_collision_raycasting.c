/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vertical_collision_raycasting.c                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eleotard <eleotard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 18:37:40 by eleotard          #+#    #+#             */
/*   Updated: 2023/01/18 18:38:19 by eleotard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub.h"

int	precheck_coll_vert(t_vars *vars, t_ray *ray, t_rc *rc, int *found)
{
	*found = 0;
	if (rc->yintercept <= 0 || rc->yintercept
		>= (ft_map_height(vars->map)) * vars->tile_sz)
	{
		ray->dist_coll_vert = -1;
		return (1);
	}
	ray->collptvert_x = rc->xintercept;
	ray->collptvert_y = rc->yintercept;
	if (vars->map[(int)rc->yintercept / vars->tile_sz]
		[(int)rc->xintercept / vars->tile_sz] == '1')
	{
		ray->collptvert_y = rc->yintercept;
		ray->collptvert_x = rc->xintercept;
		ray->dist_coll_vert = sqrt(fabs(vars->player.pos.x - rc->xintercept) \
			* fabs(vars->player.pos.x - rc->xintercept) \
			+ fabs(vars->player.pos.y - rc->yintercept) \
			* fabs(vars->player.pos.y - rc->yintercept));
		return (1);
	}
	return (0);
}

void	find_coll_vert(t_vars *vars, t_ray *ray, t_rc *rc)
{
	int		found;

	if (precheck_coll_vert(vars, ray, rc, &found))
		return ;
	while (found == 0)
	{
		ray->collptvert_x += rc->xstep;
		ray->collptvert_y += rc->ystep;
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
	find_coll_vert(vars, ray, &rc);
}

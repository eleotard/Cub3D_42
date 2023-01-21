/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eleotard <eleotard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/05 15:07:38 by eleotard          #+#    #+#             */
/*   Updated: 2023/01/21 22:23:58 by eleotard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub.h"

void	draw_ceiling_and_floor(t_vars *vars, t_ray *ray, int x)
{
	int	y;

	y = -1;
	while (++y < ray->wall_top_pixel)
		my_mlx_pixel_put(vars, x, y, vars->ceiling);
	y = vars->game_win_height;
	while (y > ray->wall_bottom_pixel)
	{
		my_mlx_pixel_put(vars, x, y, vars->floor);
		y--;
	}
}

void	chose_good_texture(t_vars *vars, t_ray *ray, int x, int y)
{
	if (ray->texture == 0)
		my_mlx_pixel_put(vars, x, y,
			vars->north[ray->textureoffset_y][ray->textureoffset_x]);
	else if (ray->texture == 1)
		my_mlx_pixel_put(vars, x, y,
			vars->south[ray->textureoffset_y][ray->textureoffset_x]);
	else if (ray->texture == 2)
		my_mlx_pixel_put(vars, x, y,
			vars->west[ray->textureoffset_y][ray->textureoffset_x]);
	else if (ray->texture == 3)
		my_mlx_pixel_put(vars, x, y,
			vars->east[ray->textureoffset_y][ray->textureoffset_x]);
}

void	draw_wall_texture(t_vars *vars, t_ray *ray, int x)
{
	int	y;
	int	dist_from_top;

	ray->textureoffset_x = 0;
	ray->textureoffset_y = 0;
	if (ray->was_hit_vertical)
		ray->textureoffset_x = (int)ray->goodcoll_y % vars->tile_sz;
	else
		ray->textureoffset_x = (int)ray->goodcoll_x % vars->tile_sz;
	y = ray->wall_top_pixel;
	while (y <= ray->wall_bottom_pixel)
	{
		dist_from_top = y + (ray->wall_strip_height / 2)
			- (vars->game_win_height / 2);
		ray->textureoffset_y = dist_from_top
			* ((float)vars->tile_sz / ray->wall_strip_height);
		if (ray->textureoffset_x >= vars->tile_sz || ray->textureoffset_y
			>= vars->tile_sz || ray->textureoffset_y < 0)
			break ;
		chose_good_texture(vars, ray, x, y);
		y++;
	}
}

void	draw_stripes(t_vars *vars, t_ray *ray, int x)
{
	init_wall_top_bottom_pixels(vars, ray);
	draw_ceiling_and_floor(vars, ray, x);
	draw_wall_texture(vars, ray, x);
}

void	render(t_vars *vars)
{
	int	x;

	cast_all_rays(vars);
	define_projplan_dist(vars);
	find_wall_strip_heights(vars);
	x = -1;
	while (++x < vars->ray_nb - 1)
		draw_stripes(vars, &vars->rays[x], x);
	pixelize_ground(vars, 0x999999);
	pixelize_walls(vars, 0x333333);
	pixelize_player(vars, 0xFFFF00);
	draw_rays(vars, vars->floor);
	pixelize_dir_vector(vars, 0xFF0000);
	mlx_put_image_to_window(vars->mlx, vars->game_win,
		vars->game_img.ptr, 0, 0);
}

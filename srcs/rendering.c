/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eleotard <eleotard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/05 15:07:38 by eleotard          #+#    #+#             */
/*   Updated: 2023/01/16 20:52:04 by eleotard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub.h"

void	draw_ceiling_and_floor(t_vars *vars, t_ray *ray, int x)
{
	int	y;

	y = -1;
	while (++y < ray->wall_top_pixel)
		my_mlx_pixel_put(&vars->game_img, x, y, vars->ceiling);
	y = vars->game_win_height;
	while (y > ray->wall_bottom_pixel)
	{
		my_mlx_pixel_put(&vars->game_img, x, y, vars->floor);
		y--;
	}
}

void	draw_wall_texture(t_vars *vars, t_ray *ray, int x)
{
	int	y;
	int	dist_from_top;
	int	textureoffset_x;
	int	textureoffset_y;

	if (ray->was_hit_vertical)
		textureoffset_x = (int)ray->goodcoll_y % vars->tile_sz;
	else
		textureoffset_x = (int)ray->goodcoll_x % vars->tile_sz;
	y = ray->wall_top_pixel;
	while (y <= ray->wall_bottom_pixel)
	{
		dist_from_top = y + (ray->wall_strip_height / 2)
			- (vars->game_win_height / 2);
		textureoffset_y = dist_from_top
			* ((float)vars->tile_sz / ray->wall_strip_height);
		if (textureoffset_x >= vars->tile_sz || textureoffset_y >= vars->tile_sz
			|| textureoffset_y < 0)
			break ;
		if (ray->texture == 0)
			my_mlx_pixel_put(&vars->game_img, x, y,
				vars->north[textureoffset_y][textureoffset_x]);
		if (ray->texture == 1)
			my_mlx_pixel_put(&vars->game_img, x, y,
				vars->south[textureoffset_y][textureoffset_x]);
		if (ray->texture == 2)
			my_mlx_pixel_put(&vars->game_img, x, y,
				vars->west[textureoffset_y][textureoffset_x]);
		if (ray->texture == 3)
			my_mlx_pixel_put(&vars->game_img, x, y,
				vars->east[textureoffset_y][textureoffset_x]);
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
	while (++x < vars->ray_nb)
		draw_stripes(vars, &vars->rays[x], x);
	pixelize_ground(vars, &(vars->game_img), 0x0011000);
	pixelize_walls(vars, &(vars->game_img), 0xFFFFFF);
	pixelize_player(vars, &(vars->game_img), 0xFFFF00);
	draw_rays(vars, &(vars->game_img), 0x00FFFF);
	pixelize_dir_vector(vars, &(vars->game_img), 0xFF0000);
	mlx_put_image_to_window(vars->mlx, vars->game_win,
		vars->game_img.ptr, 0, 0);
}

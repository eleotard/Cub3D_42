/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pixelize_minimap.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eleotard <eleotard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 20:48:45 by eleotard          #+#    #+#             */
/*   Updated: 2023/01/16 20:50:50 by eleotard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub.h"

void	pixelize_dir_vector(t_vars *vars, t_img *img, int color)
{
	int		i;
	float	tmp_x;
	float	tmp_y;

	i = 0;
	tmp_x = vars->player.pos.x * MSF;
	tmp_y = vars->player.pos.y * MSF;
	my_mlx_pixel_put(img, tmp_x, tmp_y, 0x0000FF);
	while (i < (50 * MSF))
	{
		tmp_x = tmp_x + vars->player.direction.x * MSF;
		tmp_y = tmp_y + vars->player.direction.y * MSF;
		my_mlx_pixel_put(img, tmp_x, tmp_y, color);
		i++;
	}
}

void	pixelize_player(t_vars *vars, t_img *img, int color)
{
	int	i;
	int	j;

	j = 0;
	while (j < 5 * MSF)
	{
		i = -5 * MSF;
		while (++i < 5 * MSF)
			my_mlx_pixel_put(img, vars->player.pos.x * MSF + i,
				vars->player.pos.y * MSF + j, color);
		j++;
	}
	j = 0;
	while (j > -5 * MSF)
	{
		i = -5 * MSF;
		while (++i < 5 * MSF)
			my_mlx_pixel_put(img, vars->player.pos.x * MSF + i,
				vars->player.pos.y * MSF + j, color);
		j--;
	}
}

void	pixelize_grid(t_vars *vars, t_img *img, int color)
{
	t_line_cd	cd;

	cd.x0 = 0;
	cd.y0 = 0;
	cd.x1 = cd.x0;
	cd.y1 = ((vars->tile_sz * MSF) * ft_map_height(vars->map)) - 1;
	while (cd.x0 < ((vars->tile_sz * MSF) * ft_map_wide(vars->map)))
	{
		if (cd.x0 != 0)
			line(img, cd, color);
		cd.x0 = cd.x0 + (vars->tile_sz * MSF);
		cd.x1 = cd.x0;
	}
	cd.x0 = 0;
	cd.y0 = 0;
	cd.x1 = ((vars->tile_sz * MSF) * ft_map_wide(vars->map)) - 1;
	cd.y1 = cd.y0;
	while (cd.y0 < ((vars->tile_sz * MSF) * ft_map_height(vars->map)))
	{
		if (cd.y0 != 0)
			line(img, cd, color);
		cd.y0 = cd.y0 + (vars->tile_sz * MSF);
		cd.y1 = cd.y0;
	}
}

void	pixelize_walls(t_vars *vars, t_img *img, int color)
{
	int	i;
	int	j;
	int	x;
	int	y;

	i = -1;
	while (vars->map[++i])
	{
		j = -1;
		while (vars->map[i][++j])
		{
			if (vars->map[i][j] == '1')
			{
				y = (i * (vars->tile_sz * MSF)) - 1;
				while (++y < (i * (vars->tile_sz * MSF)
						+ (vars->tile_sz * MSF)))
				{
					x = (j * (vars->tile_sz * MSF)) - 1;
					while (++x < ((j * (vars->tile_sz * MSF))
							+ (vars->tile_sz * MSF)))
						my_mlx_pixel_put(img, x, y, color);
				}
			}
		}
	}
}

void	pixelize_ground(t_vars *vars, t_img *img, int color)
{
	int	i;
	int	j;
	int	x;
	int	y;

	i = -1;
	while (vars->map[++i])
	{
		j = -1;
		while (vars->map[i][++j])
		{
			if (vars->map[i][j] == '0' || vars->map[i][j] == 'N' || vars->map[i]
				[j] == 'E' || vars->map[i][j] == 'W' || vars->map[i][j] == 'S')
			{
				y = (i * (vars->tile_sz * MSF)) - 1;
				while (++y < i * (vars->tile_sz * MSF) + (vars->tile_sz * MSF))
				{
					x = (j * (vars->tile_sz * MSF)) - 1;
					while (++x < ((j * (vars->tile_sz * MSF))
							+ (vars->tile_sz * MSF)))
						my_mlx_pixel_put(img, x, y, color);
				}
			}
		}
	}
}

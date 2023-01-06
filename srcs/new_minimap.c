/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_minimap.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eleotard <eleotard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 16:40:53 by eleotard          #+#    #+#             */
/*   Updated: 2023/01/06 01:08:43 by eleotard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub.h"

void	display_img(t_vars *vars, t_img *img)
{
	mlx_put_image_to_window(vars->mlx, vars->game_win,
		img->ptr, 0, 0);
}

void	drawRays(t_vars *vars, t_img *img, int color)
{
	float	tmpX;
	float	tmpY;
	int		i;
	int		j;

	i = 0;
	while (i < vars->rayNb) // un i par rayon //vars->rayNb
	{
		j = 0;
		tmpX = vars->player.pos.x * MSF;
		tmpY = vars->player.pos.y * MSF;
		while (j < vars->rays[i].goodDist * MSF)
		{
			tmpX = tmpX + cos(vars->rays[i].rayAngle) ;
			tmpY = tmpY + sin(vars->rays[i].rayAngle) ;
			my_mlx_pixel_put(img, tmpX, tmpY, color);
			j++;
		}
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

void	pixelize_fill(t_vars * vars, t_img *img, int color)
{
	int	x;
	int	y;

	x = 0;
	y = 0;
	while (y < vars->gameWinHeight)
	{
		x = 0;
		while (x < vars->gameWinWide)
		{
			my_mlx_pixel_put(img, x, y, color);
			x++;
		}
		y++;
	}
}

void	pixelize_grid(t_vars *vars, t_img *img, int color)
{
	t_line_cd	cd;

	cd.x0 = 0;
	cd.y0 = 0;
	cd.x1 = cd.x0;
	cd.y1 = ((TILE_SIZE * MSF) * ft_map_height(vars->map)) - 1;
	while (cd.x0 < ((TILE_SIZE * MSF) * ft_map_wide(vars->map)))
	{
		if (cd.x0 != 0)
			line(img, cd, color);
		cd.x0 = cd.x0 + (TILE_SIZE * MSF);
		cd.x1 = cd.x0;
	}
	cd.x0 = 0;
	cd.y0 = 0;
	cd.x1 = ((TILE_SIZE * MSF) * ft_map_wide(vars->map)) - 1;
	cd.y1 = cd.y0;
	while (cd.y0 < ((TILE_SIZE * MSF) * ft_map_height(vars->map)))
	{
		if (cd.y0 != 0)
			line(img, cd, color);
		cd.y0 = cd.y0 + (TILE_SIZE * MSF);
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
				y = (i * (TILE_SIZE * MSF)) - 1;
				while (++y < (i * (TILE_SIZE * MSF) + (TILE_SIZE * MSF)))
				{
					x = (j * (TILE_SIZE * MSF)) - 1;
					while (++x < ((j * (TILE_SIZE * MSF)) + (TILE_SIZE * MSF)))
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
				y = (i * (TILE_SIZE * MSF)) - 1;
				while (++y < (i * (TILE_SIZE * MSF) + (TILE_SIZE * MSF)))
				{
					x = (j * (TILE_SIZE * MSF)) - 1;
					while (++x < ((j * (TILE_SIZE * MSF)) + (TILE_SIZE * MSF)))
						my_mlx_pixel_put(img, x, y, color);
				}
			}
		}
	}
}

void    pixelize_dir_vector(t_vars *vars, t_img *img, int color)
{
    int    i;
    float tmpX;
    float tmpY;    

    i = 0;
    tmpX = vars->player.pos.x * MSF;
    tmpY = vars->player.pos.y * MSF;
	my_mlx_pixel_put(img, tmpX, tmpY, 0x0000FF);
    while (i < (50 * MSF))
    {
        tmpX = tmpX + vars->player.direction.x * MSF;
        tmpY = tmpY + vars->player.direction.y * MSF;
        my_mlx_pixel_put(img, tmpX, tmpY, color);
        i++;
    }
}

void	my_mlx_pixel_put(t_img *img, int x, int y, int color)
{
	char	*dst;

	dst = img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

void	create_img(t_vars *vars, t_img *img, int x, int y)
{
	img->px_length = x;
	img->px_height = y;
	img->ptr = mlx_new_image(vars->mlx, x, y);
	img->addr = mlx_get_data_addr(img->ptr, &(img->bits_per_pixel),
			&(img->line_length), &img->endian);
}



void	set_minimap(t_vars *vars)
{
	create_img(vars, &(vars->minimap.mini_img),
		(TILE_SIZE * MSF) * ft_map_wide(vars->map), (TILE_SIZE * MSF) * ft_map_height(vars->map));
	if (!vars->minimap.mini_img.ptr || !vars->minimap.mini_img.addr)
	{
		ft_destroy_all(vars->map, vars->mlx, vars->game_win, NULL);
		exit (-1);
	}
	create_img(vars, &(vars->game_img), vars->gameWinWide, vars->gameWinHeight);
	if (!vars->game_img.ptr || !vars->game_img.addr)
	{
		ft_destroy_all(vars->map, vars->mlx, vars->game_win, vars);
		exit (-1);
	}
	//pixelize_fill(&(vars->minimap.mini_img), 0x000000);
	pixelize_ground(vars, &(vars->minimap.mini_img), 0x0011000);
	pixelize_walls(vars, &(vars->minimap.mini_img), 0x00000FF);
	//pixelize_grid(vars, &(vars->minimap.mini_img), 0x005555);
	pixelize_player(vars, &(vars->minimap.mini_img), 0xFFFF00);
	castAllRays(vars);
	drawRays(vars, &(vars->minimap.mini_img), 0x00FFFF);
	pixelize_dir_vector(vars, &(vars->minimap.mini_img), 0xFF0000);
	render(vars);
	display_img(vars, &(vars->minimap.mini_img));
}


void	re_display_minimap(t_vars *vars)
{
	//piyelize_fill(&(vars->minimap.mini_img), 0x000000);
	pixelize_ground(vars, &(vars->minimap.mini_img), 0x0011000);
	pixelize_walls(vars, &(vars->minimap.mini_img), 0x00000FF);
	//pixelize_grid(vars, &(vars->minimap.mini_img), 0x005555);
	pixelize_player(vars, &(vars->minimap.mini_img), 16776960);
	drawRays(vars, &(vars->minimap.mini_img), 0x00FFFF);
	pixelize_dir_vector(vars, &(vars->minimap.mini_img), 0xFF0000);
	render(vars);
	display_img(vars, &(vars->minimap.mini_img));
}
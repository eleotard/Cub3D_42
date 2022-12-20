/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_minimap.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elsie <elsie@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 16:40:53 by eleotard          #+#    #+#             */
/*   Updated: 2022/12/20 23:09:45 by elsie            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub.h"

void	display_minimap_img(t_vars *vars)
{
	mlx_put_image_to_window(vars->mlx, vars->minimap.win,
		vars->minimap.mini_img.ptr, 0, 0);
}

void	pixelize_player(t_vars *vars, t_img *img, int color)
{
	int	i;
	int	j;

	j = 0;
	while (j < 5)
	{
		i = -5;
		while (++i < 5)
			my_mlx_pixel_put(img, vars->player.position.x * SIZEPIC + i,
				vars->player.position.y * SIZEPIC + j, color);
		j++;
		display_minimap_img(vars);
	}
	j = 0;
	while (j > -5)
	{
		i = -5;
		while (++i < 5)
			my_mlx_pixel_put(img, vars->player.position.x * SIZEPIC + i,
				vars->player.position.y * SIZEPIC + j, color);
		display_minimap_img(vars);
		j--;
	}
	
	/*
	
	my_mlx_pixel_put(img, vars->player.position.x * SIZEPIC + 1,
		vars->player.position.y * SIZEPIC, color);
	my_mlx_pixel_put(img, vars->player.position.x * SIZEPIC - 1,
		vars->player.position.y * SIZEPIC, color);
	//my_mlx_pixel_put(img, vars->player.position.x * SIZEPIC,
	//	vars->player.position.y * SIZEPIC + 1, color);
	my_mlx_pixel_put(img, (vars->player.position.x - 1) * SIZEPIC,
		vars->player.position.y * SIZEPIC - 1, color);*/
}

void	pixelize_fill(t_img *img, int color)
{
	int	x;
	int	y;

	x = 0;
	y = 0;
	while (y < img->px_height)
	{
		x = 0;
		while (x < img->px_length)
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
	cd.y1 = (SIZEPIC * ft_map_height(vars->map)) - 1;
	while (cd.x0 < (SIZEPIC * ft_map_wide(vars->map)))
	{
		if (cd.x0 != 0)
			line(img, cd, color);
		cd.x0 = cd.x0 + SIZEPIC;
		cd.x1 = cd.x0;
	}
	cd.x0 = 0;
	cd.y0 = 0;
	cd.x1 = (SIZEPIC * ft_map_wide(vars->map)) - 1;
	cd.y1 = cd.y0;
	while (cd.y0 < (SIZEPIC * ft_map_height(vars->map)))
	{
		if (cd.y0 != 0)
			line(img, cd, color);
		cd.y0 = cd.y0 + SIZEPIC;
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
				y = (i * SIZEPIC) - 1;
				while (++y < (i * SIZEPIC + SIZEPIC))
				{
					x = (j * SIZEPIC) - 1;
					while (++x < ((j * SIZEPIC) + SIZEPIC))
						my_mlx_pixel_put(img, x, y, color);
				}
			}
		}
	}
}

/*void	pixelize_dir_vector(t_vars *vars, t_img *img, int color)
{
	t_line_cd cd;

	cd.x0 = vars->player.position.x; * SIZEPIC;
	cd.y0 = vars->player.position.y; * SIZEPIC;
	cd.x1 = cd.x0 + cos(vars->player.rotation.y) * 20;
	cd.y1 = cd.y0 + cos(vars->player.rotation.y) * 20;
	line(img, cd, color);
}*/

void    pixelize_dir_vector(t_vars *vars, t_img *img, int color)
{
    int    i;
    float tmpX;
    float tmpY;    

    i = 0;
    tmpX = vars->player.position.x * SIZEPIC;
    tmpY = vars->player.position.y * SIZEPIC;

    while (i < 50)
    {
		printf("tmpX = %f\n", tmpX);
		fflush(stdout);
		printf("tmpY = %f\n", tmpY);
		fflush(stdout);
        my_mlx_pixel_put(img, tmpX, tmpY, color);
        tmpX = tmpX + vars->player.direction.x;
        tmpY = tmpY + vars->player.direction.y;
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
		SIZEPIC * ft_map_wide(vars->map), SIZEPIC * ft_map_height(vars->map));
	if (!vars->minimap.mini_img.ptr || !vars->minimap.mini_img.addr)
	{
		ft_destroy_all(vars->map, vars->mlx, vars->minimap.win, vars);
		exit (-1);
	}
	pixelize_fill(&(vars->minimap.mini_img), 0x002200);
	pixelize_walls(vars, &(vars->minimap.mini_img), 0x00000FF);
	pixelize_grid(vars, &(vars->minimap.mini_img), 0x005555);
	pixelize_player(vars, &(vars->minimap.mini_img), 0xFFFF00);
	pixelize_dir_vector(vars, &(vars->minimap.mini_img), 0xFF0000);
	display_minimap_img(vars);
}


void	re_display_minimap(t_vars *vars)
{
	pixelize_fill(&(vars->minimap.mini_img), 0x002200);
	pixelize_walls(vars, &(vars->minimap.mini_img), 0x00000FF);
	pixelize_grid(vars, &(vars->minimap.mini_img), 0x005555);
	pixelize_player(vars, &(vars->minimap.mini_img), 0xFFFF00);
	pixelize_dir_vector(vars, &(vars->minimap.mini_img), 0xFF0000);
	display_minimap_img(vars);
}
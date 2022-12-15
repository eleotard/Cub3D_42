/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_minimap.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eleotard <eleotard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 16:40:53 by eleotard          #+#    #+#             */
/*   Updated: 2022/12/15 17:35:56 by eleotard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub.h"

void	init_perso_pos_x(t_vars *vars)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (vars->map[i])
	{
		j = 0;
		while (vars->map[i][j])
		{
			if (vars->map[i][j] == 'N' || vars->map[i][j] == 'S'
				|| vars->map[i][j] == 'E' || vars->map[i][j] == 'W')
				vars->perso.position.x = j + 0.5;
			j++;
		}
		i++;
	}
	printf("perso x = %f\n", vars->perso.position.x);
}

void	init_perso_pos_y(t_vars *vars)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (vars->map[i])
	{
		j = 0;
		while (vars->map[i][j])
		{
			if (vars->map[i][j] == 'N' || vars->map[i][j] == 'S'
				|| vars->map[i][j] == 'E' || vars->map[i][j] == 'W')
				vars->perso.position.y = i + 0.5;
			j++;
		}
		i++;
	}
	printf("perso y = %f\n", vars->perso.position.y);
}


void	pixelize_perso(t_vars *vars, t_img *img, int color)
{
	my_mlx_pixel_put(img, vars->perso.position.x * SIZEPIC,
		vars->perso.position.y * SIZEPIC, color);
}

void	display_minimap_img(t_vars *vars)
{
	mlx_put_image_to_window(vars->mlx, vars->minimap.win,
		vars->minimap.mini_img.ptr, 0, 0);
}


void	pixelize_minimap_base(t_vars *vars)
{
	int	x;
	int y;
	int	i;
	int	j;
	
	x = 0;
	y = 0;
	i = 0;
	while (vars->map[i])
	{
		j = 0;
		x = 0;
		while (vars->map[i][j])
		{
			if (vars->map[i][j] == '0' || vars->map[i][j] == 'N' || vars->map[i][j] == 'S'
				|| vars->map[i][j] == 'E' || vars->map[i][j] == 'W')
			{
				//pixelize_square(&(vars->minimap.mini_img), x, y, 0xFFFF00);
			}
			else if (vars->map[i][j] == '1')
			{
				
			}
			x = x + SIZEPIC;
			j++;
		}
		y = y + SIZEPIC;
		i++;
	}
}


void	pixelize_grid(t_vars *vars, t_img *img)
{
	int	x0;
	int	y0;
	int x1;
	int	y1;



	x0 = 0;
	y0 = 0;
	x1 = x0;
	y1 = (SIZEPIC * ft_map_height(vars->map)) - 1;
	while (x0 < (SIZEPIC * ft_map_wide(vars->map)))
	{
		if (x0 != 0)
		{
			printf("%d %d\n", x0, x1);
			line(img, x0, y0, x1, y1);
		}
		x0 = x0 + SIZEPIC;
		x1 = x0;
	}
	x0 = 0;
	y0 = 0;
	x1 = (SIZEPIC * ft_map_wide(vars->map)) -1;
	y1 = y0;
	while (y0 < (SIZEPIC * ft_map_height(vars->map)))
	{
		if (y0 != 0)
			line(img, x0, y0, x1, y1);
		y0 = y0 + SIZEPIC;
		y1 = y0;
	}
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

void	pixelize_square(t_img *img, int x, int y, int color)
{
	while (x < x + SIZEPIC)
	{
		my_mlx_pixel_put(img, x, y, color);
		x++;
	}
	while (y < y + SIZEPIC)
	{
		my_mlx_pixel_put(img, (img->px_length - 1), y, color);
		my_mlx_pixel_put(img, 0, y, color);
		y++;
	}
	x = 0;
	while (x < x + SIZEPIC)
	{
		my_mlx_pixel_put(img, x, y + SIZEPIC, color);
		x++;
	}
}

void	my_mlx_pixel_put(t_img *img, int x, int y, int color)
{
	char	*dst;

	dst = img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

void	create_img(t_vars *vars, t_img *img, int x, int y)
{
	img->px_length = x;
	img->px_height = y;
	img->ptr = mlx_new_image(vars->mlx, x, y);
	img->addr = mlx_get_data_addr(img->ptr, &(img->bits_per_pixel),
		&(img->line_length), &img->endian);
}

void	set_good_minimap(t_vars *vars)
{
	create_img(vars, &(vars->minimap.mini_img), SIZEPIC * ft_map_wide(vars->map),
		SIZEPIC * ft_map_height(vars->map));
	if (!vars->minimap.mini_img.ptr || !vars->minimap.mini_img.addr)
	{
		ft_destroy_all(vars->map, vars->mlx, vars->minimap.win, vars);
		exit (-1);
	}
	//pixelize_minimap_base(vars);
	pixelize_fill(&(vars->minimap.mini_img), 0xFFFFFF);
	pixelize_grid(vars, &(vars->minimap.mini_img));
	pixelize_perso(vars, &(vars->minimap.mini_img), 0xFFFF00);
	display_minimap_img(vars);
}

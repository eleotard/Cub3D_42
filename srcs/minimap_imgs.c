/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_imgs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eleotard <eleotard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/13 19:45:33 by eleotard          #+#    #+#             */
/*   Updated: 2022/12/13 23:24:34 by eleotard         ###   ########.fr       */
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

void	display_minimap_base(t_vars *vars)
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
				mlx_put_image_to_window(vars->mlx, vars->minimap.win,
					vars->minimap.ground.ptr, x, y);
			}
			else if (vars->map[i][j] == '1')
				mlx_put_image_to_window(vars->mlx, vars->minimap.win,
					vars->minimap.wall.ptr, x, y);
			x = x + SIZEPIC;
			j++;
		}
		y = y + SIZEPIC;
		i++;
	}
}

void	my_mlx_pixel_put(t_img *img, int x, int y, int color)
{
	char	*dst;

	dst = img->addr + (y * img->line_length + 
		x * (img->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}


void	pixelize_borders(t_img *img, int color)
{
	int	x;
	int	y;

	x = 0;
	y = 0;
	while (x < img->px_length)
	{
		my_mlx_pixel_put(img, x, y, color);
		x++;
	}
	while (y < img->px_height)
	{
		my_mlx_pixel_put(img, (img->px_length - 1), y, color);
		my_mlx_pixel_put(img, 0, y, color);
		y++;
	}
	x = 0;
	while (x < img->px_length)
	{
		my_mlx_pixel_put(img, x, (img->px_height - 1), color);
		x++;
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


void	pixelize_perso(t_vars *vars, t_img *img, int color)
{
	my_mlx_pixel_put(img, vars->perso.position.x * SIZEPIC, vars->perso.position.y * SIZEPIC, color);
}

void	create_img(t_vars *vars, t_img *img, int x, int y)
{
	img->px_length = x;
	img->px_height = y;
	img->ptr = mlx_new_image(vars->mlx, x, y);
	img->addr = mlx_get_data_addr(img->ptr, &(img->bits_per_pixel),
		&(img->line_length), &img->endian);
}

void	display_perso(t_vars *vars)
{
	mlx_put_image_to_window(vars->mlx, vars->minimap.win,
		vars->minimap.p_point.ptr, 0, 0);
}

void	set_minimap(t_vars *vars)
{
	create_img(vars, &(vars->minimap.ground), SIZEPIC, SIZEPIC);
	create_img(vars, &(vars->minimap.wall), SIZEPIC, SIZEPIC);
	create_img(vars, &(vars->minimap.p_point), SIZEPIC * ft_map_wide(vars->map), 
		SIZEPIC * ft_map_height(vars->map));
	pixelize_fill(&(vars->minimap.ground), 0x000000FF);
	pixelize_borders(&(vars->minimap.ground), 0x581845 );
	pixelize_fill(&(vars->minimap.wall), 0x9F2B68);
	pixelize_borders(&(vars->minimap.wall), 0x581845 );
	pixelize_perso(vars, &(vars->minimap.p_point), 0xFFFF00);
}
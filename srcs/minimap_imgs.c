/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_imgs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eleotard <eleotard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/13 19:45:33 by eleotard          #+#    #+#             */
/*   Updated: 2022/12/15 17:36:36 by eleotard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub.h"


void line(t_img *img, int x0, int y0, int x1, int y1)
{
	int	dx;
	int dy; //distance
	int sx; //sign
	int	sy;
	int err;
	int e2;
	
	dx = abs(x1-x0); //retourne la valeur absolue de la difference
	if (x0 < x1)
		sx = 1;
	else
		sx = -1;
	dy = abs(y1-y0);
	if (y0 < y1)
		sy = 1;
	else
		sy = -1;
	if (dx > dy)
		err = dx / 2;
	else
		err = -dy / 2;
	
	while (1)
	{
		my_mlx_pixel_put(img, x0, y0, 0x00000FF);
		if (x0 == x1 && y0 == y1)
			break;
		e2 = err;
		if (e2 > -dx)
		{
			err -= dy;
			x0 += sx;
		}
		if (e2 < dy)
		{
			err += dx;
			y0 += sy;
		}
	}
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

/*void	pixelize_fill(t_img *img, int color)
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
}*/








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
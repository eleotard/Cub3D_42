/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_minimap.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eleotard <eleotard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 16:40:53 by eleotard          #+#    #+#             */
/*   Updated: 2023/01/16 20:52:57 by eleotard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub.h"

void	draw_rays(t_vars *vars, t_img *img, int color)
{
	float	tmp_x;
	float	tmp_y;
	int		i;
	int		j;

	i = 0;
	while (i < vars->ray_nb)
	{
		j = 0;
		tmp_x = vars->player.pos.x * MSF;
		tmp_y = vars->player.pos.y * MSF;
		while (j < vars->rays[i].good_dist * MSF)
		{
			tmp_x = tmp_x + cos(vars->rays[i].ray_angle);
			tmp_y = tmp_y + sin(vars->rays[i].ray_angle);
			my_mlx_pixel_put(img, tmp_x, tmp_y, color);
			j++;
		}
		i = i + 400 * MSF;
	}
}

void	my_mlx_pixel_put(t_img *img, int x, int y, int color)
{
	char	*dst;

	if (x < 0 || y < 0)
		return ;
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

void	set_img(t_vars *vars)
{
	create_img(vars, &(vars->game_img), vars->game_win_wide,
		vars->game_win_height);
	if (!vars->game_img.ptr || !vars->game_img.addr)
	{
		ft_destroy_all(vars->map, vars->mlx, vars->game_win, vars);
		exit (-1);
	}
	render(vars);
}

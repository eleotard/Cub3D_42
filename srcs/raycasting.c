/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eleotard <eleotard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/01 17:16:54 by eleotard          #+#    #+#             */
/*   Updated: 2023/01/01 18:26:52 by eleotard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub.h"

void    actualizeRaysInfos(t_vars *vars)
{
	int			i;
	static int	status;
	
	//cb de rayons veut-on tirer sur l'ensemble des pixels
	if (status == 0)
	{
		vars->rayNb = (TILE_SIZE * ft_map_wide(vars->map) / 40); //un rayon pour tous les 40 px
		vars->angleStep = FOV_ANGLE / vars->rayNb;
		vars->rays = malloc(sizeof(t_ray) * vars->rayNb);
		if (!vars->rays)
		{
			ft_destroy_all(vars->map, vars->mlx, vars->minimap.win, vars);
			exit(-1);
		}
		status++;
	}
	vars->rays[0].rayAngle = vars->player.rotation.y - (FOV_ANGLE / 2);
	i = 0;
	while (i < vars->rayNb)
	{
		i++;
		if (i < vars->rayNb && vars->rayNb > 0)
			vars->rays[i].rayAngle = vars->rays[i - 1].rayAngle + vars->angleStep;
    }
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
		tmpX = vars->player.position.x;
		tmpY = vars->player.position.y;
		while (j < 100)
		{
			tmpX = tmpX + cos(vars->rays[i].rayAngle);
			tmpY = tmpY + sin(vars->rays[i].rayAngle);;
			my_mlx_pixel_put(img, tmpX, tmpY, color);
			j++;
		}
		i++;
	}
}

// void    findDistX(t_vars *vars)
// {
//     float   dx;
//     float   dy;

//     dx = cos(vars->rays[0].rayAngle)
// }
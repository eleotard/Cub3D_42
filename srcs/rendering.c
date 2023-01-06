/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eleotard <eleotard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/05 15:07:38 by eleotard          #+#    #+#             */
/*   Updated: 2023/01/06 01:47:29 by eleotard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub.h"

	//mlx_get_screen_size(vars->mlx, &x, &y);

void	defineProjPlanDist(t_vars *vars)
{
	vars->projPlanDist = (vars->gameWinWide / 2) / tan(FOV_ANGLE / 2);
	//printf(RED "distance plan de projection = %f\n" RESET, vars->projPlanDist);
}

//WallStripHeight = hauteur totale de la bande du mur en pixel
//hauteur du mur qui est aussi egale a TILE_SIZE

void	findWallStripHeights(t_vars *vars)
{
	int	i;

	i = -1;
	while (++i < vars->rayNb)
		vars->rays[i].wallStripHeight = (TILE_SIZE * vars->projPlanDist) / vars->rays[i].noFishEyeDist;
}

void	drawWalls(t_vars *vars, t_img *img)
{
	int	x;
	int y;
	int a;
	int color;

	x = -1;
	y = vars->gameWinHeight / 2;
	color = 0xFFFF00;
	while (++x < vars->gameWinWide)
	{
		a = -1;
		while (++a < vars->rays[x].wallStripHeight / 2)
		{
			if ((y + a) < vars->gameWinHeight)
				my_mlx_pixel_put(img, x, y + a, color);
			else
				break ;
		}
		a = -1;
		while (++a < vars->rays[x].wallStripHeight / 2)
		{
			if ((y - a) >= 0)
				my_mlx_pixel_put(img, x, y - a, color);
			else
				break ;
		}
	}
}

void	render(t_vars *vars)
{
	defineProjPlanDist(vars);
	findWallStripHeights(vars);
	pixelize_fill(vars, &(vars->game_img), 0x000000);
	drawWalls(vars, &(vars->game_img));
	display_img(vars, &(vars->game_img));
}
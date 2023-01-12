/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eleotard <eleotard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/05 15:07:38 by eleotard          #+#    #+#             */
/*   Updated: 2023/01/12 17:52:16 by eleotard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub.h"

	//mlx_get_screen_size(vars->mlx, &x, &y);

void	defineProjPlanDist(t_vars *vars)
{
	vars->projPlanDist = (vars->tileSize * ft_map_wide(vars->map) / 2) / tan(FOV_ANGLE / 2);
	//printf(RED "distance plan de projection = %f\n" RESET, vars->projPlanDist);
}

void	findWallStripHeights(t_vars *vars)
{
	int	i;

	i = -1;
	while (++i < vars->rayNb)
		vars->rays[i].wallStripHeight = (vars->tileSize * vars->projPlanDist) / vars->rays[i].noFishEyeDist;
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

void	drawWalls(t_vars *vars, t_img *img)
{
	int	x;
	int y;
	int a;
	int color;

	x = -1;
	y = vars->gameWinHeight / 2;
	color = 0x000000;
	while (++x < vars->rayNb)
	{
		a = -1;
		while (++a < vars->rays[x].wallStripHeight / 2)
		{
			if ((y + a) < vars->gameWinHeight)
				my_mlx_pixel_put(img, x, y + a, color);
			else
				break ;
		}
		while ((y + a) < vars->gameWinHeight)
		{
			if ((y + a) < vars->gameWinHeight)
				my_mlx_pixel_put(img, x, y + a, 0xFFFFFF);
			else
				break ;
			a++;
		}
		a = -1;
		while (++a < vars->rays[x].wallStripHeight / 2)
		{
			if ((y - a) > 0)
				my_mlx_pixel_put(img, x, y - a, color);
			else
				break ;
		}
		while ((y - a) > 0)
		{
			if ((y - a) > 0)
				my_mlx_pixel_put(img, x, y - a, 0x00FFFF);
			else
				break ;
			a++;
		}
	}
}

void	render(t_vars *vars)
{
	
	//castAllRays(vars);
	defineProjPlanDist(vars);
	findWallStripHeights(vars);
	drawWalls(vars, &(vars->game_img));
	//display_img(vars, &(vars->game_img));
	
	pixelize_ground(vars, &(vars->game_img), 0x0011000);
	pixelize_walls(vars, &(vars->game_img), 0xFFFFFF);
	pixelize_player(vars, &(vars->game_img), 0xFFFF00);
	drawRays(vars, &(vars->game_img), 0x00FFFF);
	pixelize_dir_vector(vars, &(vars->game_img), 0xFF0000);
}

	// if (ray->distCollHoriz == -1 || ray->distCollVert <= ray->distCollHoriz)
	// {
	// 	ray->wasHitVerticaly = 1;
	// 	ray->goodCollX = ray->collPtVertX;
	// 	ray->goodCollY = ray->collPtVertY;
	// 	ray->goodDist = ray->distCollVert;
	// }
	// else if (ray->distCollVert == -1 || ray->distCollHoriz <= ray->distCollVert)
	// {
	// 	ray->wasHitHorizontaly = 1;
	// 	ray->goodCollX = ray->collPtHorizX;
	// 	ray->goodCollY = ray->collPtHorizY;
	// 	ray->goodDist = ray->distCollHoriz;
	// }
// 	ray->noFishEyeDist = ray->goodDist * cos(ray->rayAngle - vars->player.rotation.y);
	
// 	//printf(RED "\tDISSSSSSSSSSSST = %f\n" RESET, ray->goodDist);
// }

// void	findRayTexture(t_vars *vars,  *ray)
// {
// 	ray->texture = '0';
// 	if (ray->wasHitHorizontaly == 1 && vars->player.pos.y <= ray->goodCollY)
// 		ray->texture = 'S';
// 	else if (ray->wasHitHorizontaly == 1 && vars->player.pos.y > ray->goodCollY)
// 		ray->texture = 'N';
// 	else if (ray->wasHitVerticaly == 1 && vars->player.pos.x > ray->goodCollX)
// 		ray->texture = 'E';
// 	else if (ray->wasHitVerticaly == 1 && vars->player.pos.x <= ray->goodCollX)
// 		ray->texture = 'W';
// }





	// if (ray->distCollHoriz == -1)
	// 	ray->wasHitVerticaly = 1;
	// else if (ray->distCollVert == -1)
	// 	ray->wasHitHorizontaly = 1;
	// else if (ray->distCollVert <= ray->distCollHoriz)
	// 	ray->wasHitVerticaly = 1;
	// else if (ray->distCollHoriz <= ray->distCollVert)
	// 	ray->wasHitHorizontaly = 1;
	// if (ray->wasHitVerticaly)
	// {
	// 	ray->goodCollX = ray->collPtVertX;
	// 	ray->goodCollY = ray->collPtVertY;
	// 	ray->goodDist = ray->distCollVert;
	// }
	// else
	// {
	// 	ray->goodCollX = ray->collPtHorizX;
	// 	ray->goodCollY = ray->collPtHorizY;
	// 	ray->goodDist = ray->distCollHoriz;
	// }




	// 	if (ray->distCollHoriz == -1)
	// {
	// 	ray->wasHitVerticaly = 1;
	// 	ray->goodCollX = ray->collPtVertX;
	// 	ray->goodCollY = ray->collPtVertY;
	// 	ray->goodDist = ray->distCollVert;
	// }
	// else if (ray->distCollVert == -1)
	// {
	// 	ray->wasHitHorizontaly = 1;
	// 	ray->goodCollX = ray->collPtHorizX;
	// 	ray->goodCollY = ray->collPtHorizY;
	// 	ray->goodDist = ray->distCollHoriz;
	// }
	// else if (ray->distCollVert <= ray->distCollHoriz)
	// {
	// 	ray->wasHitVerticaly = 1;
	// 	ray->goodCollX = ray->collPtVertX;
	// 	ray->goodCollY = ray->collPtVertY;
	// 	ray->goodDist = ray->distCollVert;
	// }
	// else if (ray->distCollHoriz <= ray->distCollVert)
	// {
	// 	ray->wasHitHorizontaly = 1;
	// 	ray->goodCollX = ray->collPtHorizX;
	// 	ray->goodCollY = ray->collPtHorizY;
	// 	ray->goodDist = ray->distCollHoriz;
	// }
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eleotard <eleotard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/05 15:07:38 by eleotard          #+#    #+#             */
/*   Updated: 2023/01/15 18:18:41 by eleotard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub.h"

void	defineProjPlanDist(t_vars *vars)
{
	vars->projPlanDist = (vars->tileSize * ft_map_wide(vars->map) / 2)
		/ tan(FOV_ANGLE / 2);
}

void	findWallStripHeights(t_vars *vars)
{
	int	i;

	i = -1;
	while (++i < vars->rayNb)
		vars->rays[i].wallStripHeight = (vars->tileSize * vars->projPlanDist)
			/ vars->rays[i].noFishEyeDist;
}

int	**createPixelTab(t_vars *vars, t_img *texture)
{
	int	i;
	int	j;
	int k;
	int	**tab;
	
	tab = malloc(sizeof(int *) * (vars->tileSize));
	if (!tab)
		ft_destroy_all(vars->map, vars->mlx, vars->game_win, vars);
	i = 0;
	k = 0;
	while (i < vars->tileSize)
	{
		tab[i] = malloc(sizeof(int) * (vars->tileSize));
		if (!tab[i])
			ft_destroy_all(vars->map, vars->mlx, vars->game_win, vars);
		j = 0;
		while (j < vars->tileSize)
		{
			tab[i][j] = *((unsigned int *)texture->addr + k);
			j++;
			k++;
		}
		i++;
	}
	return (tab);
}

void	initPixelTabs(t_vars *vars)
{
	vars->north = createPixelTab(vars, &vars->textures[0]);
	vars->south = createPixelTab(vars, &vars->textures[1]);
	vars->west = createPixelTab(vars, &vars->textures[2]);
	vars->east = createPixelTab(vars, &vars->textures[3]);
}

void	initWallTopBottomPixels(t_vars *vars, t_ray *ray)
{
	ray->wallTopPixel = (vars->gameWinHeight / 2) - (ray->wallStripHeight / 2);
	if (ray->wallTopPixel < 0)
		ray->wallTopPixel = 0;
	ray->wallBottomPixel = (vars->gameWinHeight / 2) + (ray->wallStripHeight / 2);
	if (ray->wallBottomPixel > vars->gameWinHeight)
		ray->wallBottomPixel = vars->gameWinHeight;
}

void	drawCeilingAndFloor(t_vars *vars, t_ray *ray, int x)
{
	int	y;

	y = -1;
	while (++y < ray->wallTopPixel)
		my_mlx_pixel_put(&vars->game_img, x, y, vars->ceiling);
	y = vars->gameWinHeight;
	while (y > ray->wallBottomPixel)
	{
		my_mlx_pixel_put(&vars->game_img, x, y, vars->floor);
		y--;
	}
}

void	drawWallTexture(t_vars *vars, t_ray *ray, int x)
{
	int	y;
	int	distanceFromTop;
	int	textureOffsetX;
	int textureOffsetY;

	if (ray->wasHitVerticaly)
		textureOffsetX = (int)ray->goodCollY % vars->tileSize;
	else
		textureOffsetX = (int)ray->goodCollX % vars->tileSize;
	y = ray->wallTopPixel;
	while (y <= ray->wallBottomPixel)
	{
		distanceFromTop = y + (ray->wallStripHeight / 2) - (vars->gameWinHeight / 2);
		textureOffsetY = distanceFromTop * ((float)vars->tileSize / ray->wallStripHeight);
		if (textureOffsetX >= vars->tileSize || textureOffsetY >= vars->tileSize
			|| textureOffsetY < 0)
			break ;
		if (ray->texture == 0)
			my_mlx_pixel_put(&vars->game_img, x, y, vars->north[textureOffsetY][textureOffsetX]);
		if (ray->texture == 1)
			my_mlx_pixel_put(&vars->game_img, x, y, vars->south[textureOffsetY][textureOffsetX]);
		if (ray->texture == 2)
			my_mlx_pixel_put(&vars->game_img, x, y, vars->west[textureOffsetY][textureOffsetX]);
		if (ray->texture == 3)
			my_mlx_pixel_put(&vars->game_img, x, y, vars->east[textureOffsetY][textureOffsetX]);
		y++;
	}
}

void	drawStripes(t_vars *vars, t_ray *ray, int x)
{
	initWallTopBottomPixels(vars, ray);
	drawCeilingAndFloor(vars, ray, x);
	drawWallTexture(vars, ray, x);
}

void	render(t_vars *vars)
{
	int	x;

	defineProjPlanDist(vars);
	findWallStripHeights(vars);
	x = -1;
	while (++x < vars->rayNb)
		drawStripes(vars, &vars->rays[x], x);
	
	pixelize_ground(vars, &(vars->game_img), 0x0011000);
	pixelize_walls(vars, &(vars->game_img), 0xFFFFFF);
	pixelize_player(vars, &(vars->game_img), 0xFFFF00);
	drawRays(vars, &(vars->game_img), 0x00FFFF);
	pixelize_dir_vector(vars, &(vars->game_img), 0xFF0000);
}

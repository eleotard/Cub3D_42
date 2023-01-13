/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eleotard <eleotard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/05 15:07:38 by eleotard          #+#    #+#             */
/*   Updated: 2023/01/13 19:08:49 by eleotard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub.h"

	//mlx_get_screen_size(vars->mlx, &x, &y);

void	defineProjPlanDist(t_vars *vars)
{
	vars->projPlanDist = (vars->tileSize * ft_map_wide(vars->map) / 2)
		/ tan(FOV_ANGLE / 2);
	//printf(RED "distance plan de projection = %f\n" RESET, vars->projPlanDist);
}

void	findWallStripHeights(t_vars *vars)
{
	int	i;

	i = -1;
	while (++i < vars->rayNb)
		vars->rays[i].wallStripHeight = (vars->tileSize * vars->projPlanDist)
			/ vars->rays[i].noFishEyeDist;
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

// int	my_mlx_pixel_reach(t_img *img, int x, int y)
// {
// 	char	*dst;
	
// 	// if (x < 0 || y < 0)
// 	// 	return ;
// 	dst = img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8));
// 	return (*(unsigned int *)dst);
// }

void	initPixelTabs(t_vars *vars)
{
	vars->north = createPixelTab(vars, &vars->textures[0]);
	vars->south = createPixelTab(vars, &vars->textures[1]);
	vars->west = createPixelTab(vars, &vars->textures[2]);
	vars->east = createPixelTab(vars, &vars->textures[3]);
}

void	drawWalls(t_vars *vars, t_img *img)
{
	int	x;
	int y;
	int a;
	

	x = -1;
	y = vars->gameWinHeight / 2;
	while (++x < vars->rayNb)
	{
		a = -1;
		while (++a < vars->rays[x].wallStripHeight / 2)
		{
			if ((y + a) < vars->gameWinHeight)
			{
				if (vars->rays[x].wasHitHorizontaly)
					my_mlx_pixel_put(img, x, y + a, 
						vars->north[(int)vars->rays[x].goodCollX % vars->tileSize]
							[(vars->tileSize / 2) + a]);
				else
					my_mlx_pixel_put(img, x, y + a, 
						vars->north[(int)vars->rays[x].goodCollY % vars->tileSize]
							[(vars->tileSize / 2) + a]);
				
			}
			else
				break ;
		}
		while ((y + a) < vars->gameWinHeight)
		{
			if ((y + a) < vars->gameWinHeight)
				my_mlx_pixel_put(img, x, y + a, vars->floor);
			else
				break ;
			a++;
		}
		a = -1;
		while (++a < vars->rays[x].wallStripHeight / 2)
		{
			if ((y - a) > 0)
			{
				if (vars->rays[x].wasHitHorizontaly)
					my_mlx_pixel_put(img, x, y - a, 
						vars->north[(int)vars->rays[x].goodCollX % vars->tileSize]
							[(vars->tileSize / 2) - a]);
				else
					my_mlx_pixel_put(img, x, y - a, 
						vars->north[(int)vars->rays[x].goodCollY % vars->tileSize]
							[(vars->tileSize / 2) - a]);
			}
			else
				break ;
		}
		while ((y - a) > 0)
		{
			if ((y - a) > 0)
				my_mlx_pixel_put(img, x, y - a, vars->ceiling);
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

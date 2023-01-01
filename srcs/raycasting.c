/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eleotard <eleotard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/01 17:16:54 by eleotard          #+#    #+#             */
/*   Updated: 2023/01/01 20:32:00 by eleotard         ###   ########.fr       */
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
		while (j < 300)
		{
			tmpX = tmpX + cos(vars->rays[0].rayAngle);
			tmpY = tmpY + sin(vars->rays[0].rayAngle);;
			my_mlx_pixel_put(img, tmpX, tmpY, color);
			j++;
		}
		i++;
	}
}

void    findDistX(t_vars *vars)
{
    float   dx;
    float   dy;
	float	dxp;
	float	dyp;
	float	collPtXX;
	float	collPtXY;
	int		found;
	int i;
	
	float	collPtYX;
	float	collPtYY;

    //dx = cos(vars->rays[vars->rayNb - 1].rayAngle);
	//dy = sin(vars->rays[vars->rayNb - 1].rayAngle);
	i = 0;
	found = 0;
	dx = cos(vars->rays[0].rayAngle);
	dy = sin(vars->rays[0].rayAngle);

	while (found == 0)
	{
		dxp = (dx * TILE_SIZE) / (dx * TILE_SIZE); // = 1
		dyp = ((dy * TILE_SIZE) * (dy * TILE_SIZE)) / ((dx * TILE_SIZE) * (dx * TILE_SIZE));
		vars->rays[0].collDistX = sqrt(dxp + dyp);
		if (i == 0)
		{
			collPtXX = (vars->player.position.x / TILE_SIZE) + dxp;
			collPtXY = (vars->player.position.y / TILE_SIZE) + (dy / dx);
			i++;
		}
		else
		{
			collPtXX = collPtXX + dxp;
			collPtXY = collPtXY + (dy / dx);
		}
		if (collPtXX < 0 || collPtXY < 0 || collPtXX > ft_map_wide(vars->map)
			|| collPtXY > ft_map_wide(vars->map) || collPtXX > ft_map_height(vars->map)
			|| collPtXY > ft_map_height(vars->map))
		{
			vars->rays[0].collDistX = 0;
			break ;	
		}
		if (vars->map[(int)collPtXY][(int)collPtXX] == '1')
			found = 1;
	}

	printf("dx = %f\n", dx);
	printf("dy = %f\n", dy);
	printf("dxp = %f\n", dxp);
	printf("dyp = %f\n", dyp);
	printf("perso x = %f\n", vars->player.position.x / TILE_SIZE);
	printf("perso y = %f\n", vars->player.position.y / TILE_SIZE);
	printf("HYPOTHENUSE X= %f\n", vars->rays[0].collDistX); //le resultat me parait assez ok
	printf("HYPOTHENUSE Y= %f\n", vars->rays[0].collDistY);
	printf("collPtXX = %f\n", collPtXX);
	printf("collPtXY = %f\n\n\n", collPtXY);

	found = 0;
	i = 0; 
	while (found == 0)
	{
		dxp = ((dx * TILE_SIZE) * (dx * TILE_SIZE)) / ((dy * TILE_SIZE) * (dy * TILE_SIZE));
		dyp = (dy * TILE_SIZE) / (dy * TILE_SIZE); // = 1
		vars->rays[0].collDistY = sqrt(dxp + dyp);
		if (i == 0)
		{
			collPtYX = (vars->player.position.x / TILE_SIZE) - (dx / dy);
			collPtYY = (vars->player.position.y / TILE_SIZE) - dyp;
			printf("collptyy = %f\n", collPtYY);
			i++;
		}
		else
		{
			collPtYX = collPtYX - (dx / dy);
			collPtYY = collPtYY - dyp;
		}
		if (collPtYX < 0 || collPtYY < 0 || collPtYX > ft_map_wide(vars->map)
			|| collPtYY > ft_map_wide(vars->map) || collPtYX > ft_map_height(vars->map)
			|| collPtYY > ft_map_height(vars->map))
		{
			vars->rays[0].collDistX = 0;
			break ;	
		}
		printf("collptyy = %f\n", collPtYY);
		printf("testing map[%d][%d]\n", (int)(collPtYY), (int)(collPtYX));
		if (vars->map[(int)collPtYY - 1][(int)collPtYX] == '1')
			found = 1;
	}
	printf("dx = %f\n", dx);
	printf("dy = %f\n", dy);
	printf("dxp = %f\n", dxp);
	printf("dyp = %f\n", dyp);
	printf("collptyx = %f\n", collPtYX);
	printf("collptyy = %f\n", collPtYY);
	printf("dx/dy = %f\n", dx/dy);
	printf("perso x = %f\n", vars->player.position.x / TILE_SIZE);
	printf("perso y = %f\n", vars->player.position.y / TILE_SIZE);
	printf("HYPOTHENUSE X= %f\n", vars->rays[0].collDistX); //le resultat me parait assez ok
	printf("HYPOTHENUSE Y= %f\n", vars->rays[0].collDistY);
	printf("collPtYX = %f\n", collPtYX);
	printf("collPtYY = %f\n\n\n", collPtYY);
}
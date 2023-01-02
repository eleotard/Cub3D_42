/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eleotard <eleotard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/01 17:16:54 by eleotard          #+#    #+#             */
/*   Updated: 2023/01/02 20:54:57 by eleotard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub.h"

/*void    findDistX(t_vars *vars)
{
    float   dx;
    float   dy;
	float	dxp;
	float	dyp;
	float	collPtXX;
	float	collPtXY;
	int		found;
	int i;
	
	float	rc.yintercept;
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
}*/

void    updateRaysAngles(t_vars *vars)
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
		tmpX = vars->player.pos.x;
		tmpY = vars->player.pos.y;
		while (j < vars->rays[0].distCollHoriz)
		{
			tmpX = tmpX + cos(vars->rays[0].rayAngle);
			tmpY = tmpY + sin(vars->rays[0].rayAngle);;
			my_mlx_pixel_put(img, tmpX, tmpY, color);
			j++;
		}
		i++;
	}
}

void	updateRaysOrientation(t_vars *vars)
{
	int	i;

	i = -1;
	while (++i < vars->rayNb)
	{
		vars->rays[i].isRayFacingUp = 0;
		vars->rays[i].isRayFacingDown = 0;
		vars->rays[i].isRayFacingLeft = 0;
		vars->rays[i].isRayFacingRight = 0;
		if (sin(vars->rays[i].rayAngle) < 0)
			vars->rays[i].isRayFacingUp = 1;
		else
			vars->rays[i].isRayFacingDown = 1;
		if (cos(vars->rays[i].rayAngle) < 0)
			vars->rays[i].isRayFacingLeft = 1;
		else
			vars->rays[i].isRayFacingRight = 1;
	}
}



void	findCollHoriz(t_vars *vars, t_ray *ray, t_rc rc)
{
	int		found;

	found = 0;
	if (rc.xintercept <= 0 || rc.xintercept - vars->player.pos.x
		>= (ft_map_wide(vars->map) - 1) * TILE_SIZE)
	{
		ray->distCollHoriz = -1;
		found = 1;
		printf("PAAAASSSEEEE\n");
		return;
	}
	if (vars->map[(int)rc.yintercept / TILE_SIZE][(int)rc.xintercept / TILE_SIZE] == '1')
	{
		printf(YELLOW "testing map[%d][%d]\n" RESET, 
			(int)(rc.yintercept / TILE_SIZE), (int)rc.xintercept / TILE_SIZE);
		ray->collPtHorizY = rc.yintercept;
		ray->collPtHorizX = rc.xintercept;
		ray->distCollHoriz = sqrt(fabs(vars->player.pos.x - rc.xintercept)
			* fabs(vars->player.pos.x - rc.xintercept)
			+ fabs(vars->player.pos.y - rc.yintercept)
			* fabs(vars->player.pos.y - rc.yintercept));
		found = 1;
		printf(RED "\tDISSSSSSSSSSSST = %f\n" RESET, ray->distCollHoriz);
		return ;
	}
	ray->collPtHorizX = rc.xintercept;
	ray->collPtHorizY = rc.yintercept;
	while (found == 0)
	{
		ray->collPtHorizX += rc.xstep;
		ray->collPtHorizY += rc.ystep;
		if (ray->collPtHorizX <= 0 || ray->collPtHorizX
			>= (ft_map_wide(vars->map) - 1) * TILE_SIZE)
		{
			ray->distCollHoriz = -1;
			found = 1;
		}
		if (vars->map[(int)ray->collPtHorizY / TILE_SIZE][(int)ray->collPtHorizY / TILE_SIZE] == '1')
		{
			ray->distCollHoriz = sqrt(fabs(vars->player.pos.x - ray->collPtHorizX)
				* fabs(vars->player.pos.x - ray->collPtHorizX)
				+ fabs(vars->player.pos.y - ray->collPtHorizY)
				* fabs(vars->player.pos.y - ray->collPtHorizY));
			found = 1;
			printf(RED "\tDISSSSSSSSSSSST = %f\n" RESET, ray->distCollHoriz);
		}
	}
			printf(YELLOW "testing map[%d][%d]\n" RESET, 
			(int)(ray->collPtHorizY / TILE_SIZE), (int)ray->collPtHorizX / TILE_SIZE);
}

void	castHorizRay(t_vars *vars, t_ray *ray)
{
	t_rc rc;
	
	rc.yintercept = floor(vars->player.pos.y / TILE_SIZE) * TILE_SIZE -1;
	if (ray->isRayFacingDown)
		rc.yintercept += TILE_SIZE + 1;
	rc.xintercept = vars->player.pos.x + (rc.yintercept - vars->player.pos.y) / tan(ray->rayAngle); //adj = opp / tan
	//adj = opp / tan
	rc.ystep = TILE_SIZE;
	if (ray->isRayFacingUp)
		rc.ystep *= -1;
	rc.xstep = TILE_SIZE / tan(ray->rayAngle);
	if (ray->isRayFacingLeft && rc.xstep > 0)
		rc.xstep *= -1;
	if (ray->isRayFacingRight && rc.xstep < 0)
		rc.xstep *= -1;
	findCollHoriz(vars, ray, rc);
	
	printf("\tx intercept = %f\n", rc.xintercept);
	printf("\ty intercept = %f\n", rc.yintercept);
	printf("\tx intercept = %f\n", rc.xintercept/TILE_SIZE);
	printf("\ty intercept = %f\n", rc.yintercept/TILE_SIZE);
}

void	castAllRays(t_vars *vars)
{
	//int i;
	
	updateRaysAngles(vars);
	updateRaysOrientation(vars);
	// i = -1;
	// while (++i < vars->rayNb)
		//casthori
		//castvert
		//find goodDist
	// 	castRay(vars, &(vars->rays[i]));
	// i = -1;
	// while (++i < vars->rayNb)
	// 	printf("essai= %d\n", vars->rays[i].isRayFacingDown);
	castHorizRay(vars, &(vars->rays[0]));
	printf(GREEN "dxray= %f\n" RESET, cos(vars->rays[0].rayAngle));
	printf(GREEN "dyray= %f\n" RESET, sin(vars->rays[0].rayAngle));
}
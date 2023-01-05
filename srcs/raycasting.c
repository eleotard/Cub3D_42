/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eleotard <eleotard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/01 17:16:54 by eleotard          #+#    #+#             */
/*   Updated: 2023/01/05 19:51:02 by eleotard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub.h"

void    updateRaysAngles(t_vars *vars)
{
	int			i;
	static int	status;
	
	//cb de rayons veut-on tirer sur l'ensemble des pixels
	if (status == 0)
	{
		vars->rayNb = (TILE_SIZE * ft_map_wide(vars->map)); //un rayon pour tous les 40 px
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

void	findCollVert(t_vars *vars, t_ray *ray, t_rc rc)
{
	int		found;

	found = 0;
	if (rc.yintercept <= 0 || rc.yintercept
		>= (ft_map_height(vars->map)) * TILE_SIZE)
	{
		ray->distCollVert = -1;
		return;
	}
	if (vars->map[(int)rc.yintercept / TILE_SIZE][(int)rc.xintercept / TILE_SIZE] == '1')
	{
		// printf(YELLOW "testing map[%d][%d]\n" RESET, 
		// 	(int)(rc.yintercept / TILE_SIZE), (int)rc.xintercept / TILE_SIZE);
		ray->collPtVertY = rc.yintercept;
		ray->collPtVertX = rc.xintercept;
		ray->distCollVert = sqrt(fabs(vars->player.pos.x - rc.xintercept)
			* fabs(vars->player.pos.x - rc.xintercept)
			+ fabs(vars->player.pos.y - rc.yintercept)
			* fabs(vars->player.pos.y - rc.yintercept));
		found = 1;
		//printf(RED "\tDISSSSSSSSSSSST X= %f\n" RESET, ray->distCollVert);
		return ;
	}
	ray->collPtVertX = rc.xintercept;
	ray->collPtVertY = rc.yintercept;
	while (found == 0)
	{
		ray->collPtVertX += rc.xstep;
		ray->collPtVertY += rc.ystep;
		if (ray->collPtVertY <= 0 || ray->collPtVertY
			>= (ft_map_height(vars->map) * TILE_SIZE))
		{
			ray->distCollVert = -1;
			break ;
		}
		if (vars->map[(int)ray->collPtVertY / TILE_SIZE]
			[(int)ray->collPtVertX / TILE_SIZE] == '1')
		{
			ray->distCollVert = sqrt(fabs(vars->player.pos.x - ray->collPtVertX)
				* fabs(vars->player.pos.x - ray->collPtVertX)
				+ fabs(vars->player.pos.y - ray->collPtVertY)
				* fabs(vars->player.pos.y - ray->collPtVertY));
			found = 1;
			// printf(RED "\tDISSSSSSSSSSSST X = %f\n" RESET, ray->distCollVert);
			// printf(YELLOW "find wall at map[%d][%d]\n" RESET, 
			// 	(int)(ray->collPtVertY / TILE_SIZE), (int)ray->collPtVertX / TILE_SIZE);
			// printf("\tCPHX = %f\n", ray->collPtVertX);
			// printf("\tCPHY = %f\n", ray->collPtVertY);
		}
	}
}


void	castVertRay(t_vars *vars, t_ray *ray)
{
	t_rc rc;
	
	rc.xintercept = floor(vars->player.pos.x / TILE_SIZE) * TILE_SIZE - 1;
	if (ray->isRayFacingRight)
		rc.xintercept += TILE_SIZE + 1;
	rc.yintercept = vars->player.pos.y + (rc.xintercept - vars->player.pos.x) * tan(ray->rayAngle); //adj = opp / tan

	rc.xstep = TILE_SIZE;
	if (ray->isRayFacingLeft)
		rc.xstep *= -1;
	rc.ystep = TILE_SIZE * tan(ray->rayAngle);
	if (ray->isRayFacingUp && rc.ystep > 0)
		rc.ystep *= -1;
	if (ray->isRayFacingDown && rc.ystep < 0)
		rc.ystep *= -1;
	
	// printf("\tx intercept = %f\n", rc.xintercept);
	// printf("\ty intercept = %f\n", rc.yintercept);
	// printf("\txstep = %f\n", rc.xstep);
	// printf("\tystep = %f\n", rc.ystep);
	// printf("\tx intercept = %f\n", rc.xintercept/TILE_SIZE);
	// printf("\ty intercept = %f\n", rc.yintercept/TILE_SIZE);
	findCollVert(vars, ray, rc);
}




void	findCollHoriz(t_vars *vars, t_ray *ray, t_rc rc)
{
	int		found;

	found = 0;
	if (rc.xintercept <= 0 || rc.xintercept
		>= (ft_map_wide(vars->map)) * TILE_SIZE)
	{
		ray->distCollHoriz = -1;
		return;
	}
	if (vars->map[(int)rc.yintercept / TILE_SIZE][(int)rc.xintercept / TILE_SIZE] == '1')
	{
		// printf(YELLOW "testing map[%d][%d]\n" RESET, 
		// 	(int)(rc.yintercept / TILE_SIZE), (int)rc.xintercept / TILE_SIZE);
		ray->collPtHorizY = rc.yintercept;
		ray->collPtHorizX = rc.xintercept;
		ray->distCollHoriz = sqrt(fabs(vars->player.pos.x - rc.xintercept)
			* fabs(vars->player.pos.x - rc.xintercept)
			+ fabs(vars->player.pos.y - rc.yintercept)
			* fabs(vars->player.pos.y - rc.yintercept));
		found = 1;
		//printf(RED "\tDISSSSSSSSSSSST Y= %f\n" RESET, ray->distCollHoriz);
		return ;
	}
	ray->collPtHorizX = rc.xintercept;
	ray->collPtHorizY = rc.yintercept;
	while (found == 0)
	{
		ray->collPtHorizX += rc.xstep;
		ray->collPtHorizY += rc.ystep;
		if (ray->collPtHorizX <= 0 || ray->collPtHorizX
			>= (ft_map_wide(vars->map) * TILE_SIZE))
		{
			ray->distCollHoriz = -1;
			break ;
		}
		if (vars->map[(int)ray->collPtHorizY / TILE_SIZE]
			[(int)ray->collPtHorizX / TILE_SIZE] == '1')
		{
			ray->distCollHoriz = sqrt(fabs(vars->player.pos.x - ray->collPtHorizX)
				* fabs(vars->player.pos.x - ray->collPtHorizX)
				+ fabs(vars->player.pos.y - ray->collPtHorizY)
				* fabs(vars->player.pos.y - ray->collPtHorizY));
			found = 1;
			// printf(RED "\tDISSSSSSSSSSSST Y = %f\n" RESET, ray->distCollHoriz);
			// printf(YELLOW "find wall at map[%d][%d]\n" RESET, 
			// 	(int)(ray->collPtHorizY / TILE_SIZE), (int)ray->collPtHorizX / TILE_SIZE);
			// printf("\tCPHX = %f\n", ray->collPtHorizX);
			// printf("\tCPHY = %f\n", ray->collPtHorizY);
		}
	}
}

void	castHorizRay(t_vars *vars, t_ray *ray)
{
	t_rc rc;
	
	rc.yintercept = floor(vars->player.pos.y / TILE_SIZE) * TILE_SIZE -1;
	if (ray->isRayFacingDown)
		rc.yintercept += TILE_SIZE + 1;
	rc.xintercept = vars->player.pos.x + (rc.yintercept - vars->player.pos.y) / tan(ray->rayAngle); //adj = opp / tan
	rc.ystep = TILE_SIZE;
	if (ray->isRayFacingUp)
		rc.ystep *= -1;
	rc.xstep = TILE_SIZE / tan(ray->rayAngle);
	if (ray->isRayFacingLeft && rc.xstep > 0)
		rc.xstep *= -1;
	if (ray->isRayFacingRight && rc.xstep < 0)
		rc.xstep *= -1;
	
	// printf("\tx intercept = %f\n", rc.xintercept);
	// printf("\ty intercept = %f\n", rc.yintercept);
	// printf("\txstep = %f\n", rc.xstep);
	// printf("\tystep = %f\n", rc.ystep);
	// printf("\tx intercept = %f\n", rc.xintercept/TILE_SIZE);
	// printf("\ty intercept = %f\n", rc.yintercept/TILE_SIZE);
	findCollHoriz(vars, ray, rc);
}

void	setGoodDistance(t_ray *ray)
{
	if (ray->distCollHoriz == -1)
		ray->goodDist = ray->distCollVert;
	else if (ray->distCollVert == -1)
		ray->goodDist = ray->distCollHoriz;
	else if (ray->distCollHoriz <= ray->distCollVert)
		ray->goodDist = ray->distCollHoriz;
	else if (ray->distCollVert <= ray->distCollHoriz)
		ray->goodDist = ray->distCollVert;
	//printf(RED "\tDISSSSSSSSSSSST = %f\n" RESET, ray->goodDist);
}

void	castAllRays(t_vars *vars)
{
	int i;
	
	updateRaysAngles(vars);
	updateRaysOrientation(vars);
	i = -1;
	while (++i < vars->rayNb)
	{
		castHorizRay(vars, &(vars->rays[i]));
		castVertRay(vars, &(vars->rays[i]));
	}
	i = -1;
	while (++i < vars->rayNb)
		setGoodDistance(&(vars->rays[i]));
	
	// printf(GREEN "dxray= %f\n" RESET, cos(vars->rays[0].rayAngle));
	// printf(GREEN "dyray= %f\n" RESET, sin(vars->rays[0].rayAngle));
}
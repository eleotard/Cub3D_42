/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eleotard <eleotard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/01 17:16:54 by eleotard          #+#    #+#             */
/*   Updated: 2023/01/06 18:23:43 by eleotard         ###   ########.fr       */
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
		vars->rayNb = vars->gameWinWide; //un rayon pour tous les px
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
		>= (ft_map_height(vars->map)) * vars->tileSize)
	{
		ray->distCollVert = -1;
		return;
	}
	if (vars->map[(int)rc.yintercept / vars->tileSize][(int)rc.xintercept / vars->tileSize] == '1')
	{
		// printf(YELLOW "testing map[%d][%d]\n" RESET, 
		// 	(int)(rc.yintercept / vars->tileSize), (int)rc.xintercept / vars->tileSize);
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
			>= (ft_map_height(vars->map) * vars->tileSize))
		{
			ray->distCollVert = -1;
			break ;
		}
		if (vars->map[(int)ray->collPtVertY / vars->tileSize]
			[(int)ray->collPtVertX / vars->tileSize] == '1')
		{
			ray->distCollVert = sqrt(fabs(vars->player.pos.x - ray->collPtVertX)
				* fabs(vars->player.pos.x - ray->collPtVertX)
				+ fabs(vars->player.pos.y - ray->collPtVertY)
				* fabs(vars->player.pos.y - ray->collPtVertY));
			found = 1;
		}
	}
}


void	castVertRay(t_vars *vars, t_ray *ray)
{
	t_rc rc;
	
	rc.xintercept = floor(vars->player.pos.x / vars->tileSize) * vars->tileSize - 0.1;
	if (ray->isRayFacingRight)
		rc.xintercept += vars->tileSize + 0.1;
	rc.yintercept = vars->player.pos.y + (rc.xintercept - vars->player.pos.x) * tan(ray->rayAngle); //adj = opp / tan

	rc.xstep = vars->tileSize;
	if (ray->isRayFacingLeft)
		rc.xstep *= -1;
	rc.ystep = vars->tileSize * tan(ray->rayAngle);
	if (ray->isRayFacingUp && rc.ystep > 0)
		rc.ystep *= -1;
	if (ray->isRayFacingDown && rc.ystep < 0)
		rc.ystep *= -1;
	
	// printf("\tx intercept = %f\n", rc.xintercept);
	// printf("\ty intercept = %f\n", rc.yintercept);
	// printf("\txstep = %f\n", rc.xstep);
	// printf("\tystep = %f\n", rc.ystep);
	// printf("\tx intercept = %f\n", rc.xintercept/vars->tileSize);
	// printf("\ty intercept = %f\n", rc.yintercept/vars->tileSize);
	findCollVert(vars, ray, rc);
}




void	findCollHoriz(t_vars *vars, t_ray *ray, t_rc rc)
{
	int		found;

	found = 0;
	if (rc.xintercept <= 0 || rc.xintercept
		>= (ft_map_wide(vars->map)) * vars->tileSize)
	{
		ray->distCollHoriz = -1;
		return;
	}
	if (vars->map[(int)rc.yintercept / vars->tileSize][(int)rc.xintercept / vars->tileSize] == '1')
	{
		// printf(YELLOW "testing map[%d][%d]\n" RESET, 
		// 	(int)(rc.yintercept / vars->tileSize), (int)rc.xintercept / vars->tileSize);
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
			>= (ft_map_wide(vars->map) * vars->tileSize))
		{
			ray->distCollHoriz = -1;
			break ;
		}
		if (vars->map[(int)ray->collPtHorizY / vars->tileSize]
			[(int)ray->collPtHorizX / vars->tileSize] == '1')
		{
			ray->distCollHoriz = sqrt(fabs(vars->player.pos.x - ray->collPtHorizX)
				* fabs(vars->player.pos.x - ray->collPtHorizX)
				+ fabs(vars->player.pos.y - ray->collPtHorizY)
				* fabs(vars->player.pos.y - ray->collPtHorizY));
			found = 1;
		}
	}
}

void	castHorizRay(t_vars *vars, t_ray *ray)
{
	t_rc rc;
	
	rc.yintercept = floor(vars->player.pos.y / vars->tileSize) * vars->tileSize -0.1;
	if (ray->isRayFacingDown)
		rc.yintercept += vars->tileSize + 0.1;
	rc.xintercept = vars->player.pos.x + (rc.yintercept - vars->player.pos.y) / tan(ray->rayAngle); //adj = opp / tan
	rc.ystep = vars->tileSize;
	if (ray->isRayFacingUp)
		rc.ystep *= -1;
	rc.xstep = vars->tileSize / tan(ray->rayAngle);
	if (ray->isRayFacingLeft && rc.xstep > 0)
		rc.xstep *= -1;
	if (ray->isRayFacingRight && rc.xstep < 0)
		rc.xstep *= -1;
	
	// printf("\tx intercept = %f\n", rc.xintercept);
	// printf("\ty intercept = %f\n", rc.yintercept);
	// printf("\txstep = %f\n", rc.xstep);
	// printf("\tystep = %f\n", rc.ystep);
	// printf("\tx intercept = %f\n", rc.xintercept/vars->tileSize);
	// printf("\ty intercept = %f\n", rc.yintercept/vars->tileSize);
	findCollHoriz(vars, ray, rc);
}

void	setGoodDistance(t_vars *vars, t_ray *ray)
{
	if (ray->distCollHoriz == -1)
		ray->goodDist = ray->distCollVert;
	else if (ray->distCollVert == -1)
		ray->goodDist = ray->distCollHoriz;
	else if (ray->distCollHoriz <= ray->distCollVert)
		ray->goodDist = ray->distCollHoriz;
	else if (ray->distCollVert <= ray->distCollHoriz)
		ray->goodDist = ray->distCollVert;
	ray->noFishEyeDist = ray->goodDist * cos(ray->rayAngle - vars->player.rotation.y);
	// 	ray->goodDist -= 1;
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
		setGoodDistance(vars, &(vars->rays[i]));
	
	// printf(GREEN "dxray= %f\n" RESET, cos(vars->rays[0].rayAngle));
	// printf(GREEN "dyray= %f\n" RESET, sin(vars->rays[0].rayAngle));
}
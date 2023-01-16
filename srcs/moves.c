/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moves.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eleotard <eleotard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/13 18:31:17 by eleotard          #+#    #+#             */
/*   Updated: 2023/01/16 20:55:45 by eleotard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub.h"

void	move_foreward(t_vars *vars)
{
	float	move_step;
	float	next_x;
	float	next_y;

	move_step = vars->player.walk_direction * MOVE_SPEED;
	next_x = vars->player.pos.x + vars->player.direction.x * move_step;
	next_y = vars->player.pos.y + vars->player.direction.y * move_step;
	if (vars->map[(int)(next_y / vars->tile_sz)]
		[(int)vars->player.pos.x / vars->tile_sz] != '1')
		vars->player.pos.y = next_y;
	if (vars->map[(int)vars->player.pos.y / vars->tile_sz]
		[(int)(next_x / vars->tile_sz)] != '1')
		vars->player.pos.x = next_x;
	render(vars);
}

void	update_direction(t_vars *vars)
{
	vars->player.rotation.y += vars->player.turn_direction * ROTATION_SPEED;
	vars->player.direction.x = cos(vars->player.rotation.y);
	vars->player.direction.y = sin(vars->player.rotation.y);
}

void	move_backward(t_vars *vars)
{
	float	move_step;
	float	next_x;
	float	next_y;

	move_step = vars->player.walk_direction * MOVE_SPEED;
	next_x = vars->player.pos.x + vars->player.direction.x * move_step;
	next_y = vars->player.pos.y + vars->player.direction.y * move_step;
	if (vars->map[(int)(next_y / vars->tile_sz)]
		[(int)vars->player.pos.x / vars->tile_sz] != '1')
		vars->player.pos.y = next_y;
	if (vars->map[(int)vars->player.pos.y / vars->tile_sz]
		[(int)(next_x / vars->tile_sz)] != '1')
		vars->player.pos.x = next_x;
	render(vars);
}

void	move_left(t_vars *vars)
{
	float	next_x;
	float	next_y;

	next_x = vars->player.pos.x + vars->player.direction.y * MOVE_SPEED;
	next_y = vars->player.pos.y - vars->player.direction.x * MOVE_SPEED;
	if (vars->map[(int)(next_y / vars->tile_sz)]
		[(int)vars->player.pos.x / vars->tile_sz] != '1')
		vars->player.pos.y = next_y;
	if (vars->map[(int)vars->player.pos.y / vars->tile_sz]
		[(int)(next_x / vars->tile_sz)] != '1')
		vars->player.pos.x = next_x;
	render(vars);
}

void	move_right(t_vars *vars)
{
	float	next_x;
	float	next_y;

	next_x = vars->player.pos.x - vars->player.direction.y * MOVE_SPEED;
	next_y = vars->player.pos.y + vars->player.direction.x * MOVE_SPEED;
	if (vars->map[(int)(next_y / vars->tile_sz)]
		[(int)vars->player.pos.x / vars->tile_sz] != '1')
		vars->player.pos.y = next_y;
	if (vars->map[(int)vars->player.pos.y / vars->tile_sz]
		[(int)(next_x / vars->tile_sz)] != '1')
		vars->player.pos.x = next_x;
	render(vars);
}

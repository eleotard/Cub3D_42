/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   watch.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eleotard <eleotard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 20:40:43 by eleotard          #+#    #+#             */
/*   Updated: 2023/01/16 20:52:32 by eleotard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub.h"

void	watch_left(t_vars *vars)
{
	vars->player.rotation.y += vars->player.turn_direction * ROTATION_SPEED;
	update_direction(vars);
	render(vars);
}

void	watch_right(t_vars *vars)
{
	vars->player.rotation.y += vars->player.turn_direction * ROTATION_SPEED;
	update_direction(vars);
	render(vars);
}

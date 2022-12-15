/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eleotard <eleotard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/15 19:51:27 by eleotard          #+#    #+#             */
/*   Updated: 2022/12/15 19:53:50 by eleotard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub.h"

void	line_2(t_img *img, t_line_cd *cd, t_line_params *pa, int color)
{
	int	err;
	int	e2;

	if (pa->dx > pa->dy)
		err = pa->dx / 2;
	else
		err = -pa->dy / 2;
	while (1)
	{
		my_mlx_pixel_put(img, cd->x0, cd->y0, color);
		if (cd->x0 == cd->x1 && cd->y0 == cd->y1)
			break ;
		e2 = err;
		if (e2 > -pa->dx)
		{
			err -= pa->dy;
			cd->x0 += pa->sx;
		}
		if (e2 < pa->dy)
		{
			err += pa->dx;
			cd->y0 += pa->sy;
		}
	}
}

void	line(t_img *img, t_line_cd cd, int color)
{
	t_line_params	pa;

	pa.dx = abs(cd.x1 - cd.x0); //retourne la valeur absolue de la difference
	if (cd.x0 < cd.x1)
		pa.sx = 1;
	else
		pa.sx = -1;
	pa.dy = abs(cd.y1 - cd.y0);
	if (cd.y0 < cd.y1)
		pa.sy = 1;
	else
		pa.sy = -1;
	line_2(img, &cd, &pa, color);
}

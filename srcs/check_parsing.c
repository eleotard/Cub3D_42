/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_parsing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eleotard <eleotard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/12 23:20:30 by eleotard          #+#    #+#             */
/*   Updated: 2022/12/12 23:24:49 by eleotard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub.h"

int	ft_parsing_check(char *map_str)
{
	int	i;

	i = 0;
	while (map_str[i])
	{
		if (map_str[i] != '1' && map_str[i] != '0' && map_str[i] != 'N'
			&& map_str[i] != 'S' && map_str[i] != 'E' && map_str[i] != 'W'
			&& map_str[i] != '\n' && map_str[i] != ' ')
		{
			free(map_str);
			ft_putstr_fd("Error\nCaractere incorect\n", 2);
			return (ERROR);
		}
		i++;
	}
	return (0);
}
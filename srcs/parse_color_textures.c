/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_color_textures.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elpastor <elpastor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 19:11:14 by elpastor          #+#    #+#             */
/*   Updated: 2023/01/20 19:03:24 by elpastor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

int	check_color(char *s)
{
	int	i;

	i = 1;
	if (s[i++] != ' ')
		return (0);
	while (s[i] && ft_isdigit(s[i]))
		i++;
	if (s[i++] != ',')
		return (0);
	while (s[i] && ft_isdigit(s[i]))
		i++;
	if (s[i++] != ',')
		return (0);
	if (!s[i] || !ft_isdigit(s[i]))
		return (0);
	while (s[i] && ft_isdigit(s[i]))
		i++;
	if (s[i] != '\n')
		return (0);
	return (1);
}

int	get_color(char *s, t_vars *vars, char *to_free)
{
	int	i;
	int	red;
	int	green;
	int	blue;

	if (!check_color(s) || (s[0] == 'F' && vars->floor != -1)
		|| (s[0] == 'C' && vars->ceiling != -1))
		destroy_all_msg(vars, "Error\nInvalid color syntax\n", to_free, NULL);
	i = 1;
	red = 0;
	green = 0;
	blue = 0;
	while (ft_isdigit(s[++i]))
		red = red * 10 + (s[i] - '0');
	while (ft_isdigit(s[++i]))
		green = green * 10 + (s[i] - '0');
	while (ft_isdigit(s[++i]))
		blue = blue * 10 + (s[i] - '0');
	if (red > 255 || green > 255 || blue > 255)
		destroy_all_msg(vars, "Error\nInvalid color values\n", to_free, NULL);
	if (s[0] == 'F')
		vars->floor = (red << 16 | green << 8 | blue);
	else
		vars->ceiling = (red << 16 | green << 8 | blue);
	return (i + 1);
}

void	path2img(char *path, t_img *texture, t_vars *vars, char *to_free)
{
	texture->ptr = mlx_xpm_file_to_image(vars->mlx, path,
			&(texture->px_length), &(texture->px_height));
	if (texture->ptr == NULL)
	{
		free(path);
		destroy_all_msg(vars, "Error\nMlx File_to_image failed\n", to_free, NULL);
	}
	texture->addr = mlx_get_data_addr(texture->ptr, &texture->bits_per_pixel,
			&texture->line_length, &texture->endian);
	free(path);
}

char	*get_path_texture(char *s, int *count, t_vars *vars, char *to_free)
{
	int		i;
	int		j;
	char	*path_texture;

	i = 0;
	while (s[i] && s[i] != '\n')
		i++;
	path_texture = (char *)malloc(sizeof(char) * (i + 1));
	if (!path_texture)
		destroy_all_msg(vars, "Error\nMalloc failed\n", to_free, NULL);
	j = 0;
	while (j < i)
	{
		path_texture[j] = s[j];
		j++;
	}
	path_texture[j] = 0;
	*count += i;
	return (path_texture);
}

int	get_texture(char *s, t_vars *vars, int texture_type, char *to_free)
{
	int		i;

	if (vars->textures[texture_type].ptr != NULL)
		destroy_all_msg(vars, "Error\nFile '.cub' invalid, too much textures\n",
			to_free, NULL);
	if (!find_char(s, '.') || !find_char(s, '/'))
		destroy_all_msg(vars, "Error\nWrong texture format\n", to_free, NULL);
	i = 2;
	while (s[i] && s[i] != '.' && s[i] != '\n')
	{
		if (s[i] != ' ')
			destroy_all_msg(vars, "Error\nWrong texture format\n", to_free, NULL);
		i++;
	}
	if (s[i] == '\n')
		destroy_all_msg(vars, "Error\nNo texture\n", to_free, NULL);
	path2img(get_path_texture(&s[i], &i, vars, s),
		&vars->textures[texture_type], vars, to_free);
	return (i + 1);
}

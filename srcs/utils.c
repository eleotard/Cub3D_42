/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elpastor <elpastor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/12 23:30:03 by eleotard          #+#    #+#             */
/*   Updated: 2023/01/19 19:02:22 by elpastor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub.h"

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	if (!s1 || !s2)
		return (0);
	i = 0;
	while (s1[i] || s2[i])
	{
		if (s1[i] != s2[i])
			break ;
		i++;
	}
	return (s1[i] - s2[i]);
}

char	*ft_strjoin_s(char *base, char *read)
{
	char	*line;
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (!base || !read)
		return (NULL);
	line = malloc(sizeof(char) * (ft_strlen(base) + ft_strlen(read) + 2));
	if (!line)
		return (NULL);
	while (base[i])
	{
		line[i] = base[i];
		i++;
	}
	while (read[j])
	{
		line[i] = read[j];
		i++;
		j++;
	}
	line[i] = '\0';
	free(base);
	return (line);
}

char	*join(char *base, char *read)
{
	char	*new_read;

	if (!read)
	{
		read = malloc(sizeof(char));
		if (!read)
			return (free(base), NULL);
		read[0] = '\0';
	}
	new_read = ft_strjoin_s(base, read);
	if (!new_read)
		return (free(read), free(base), NULL);
	free(read);
	return (new_read);
}

int	find_char(char *s, char c)
{
	int	i;

	if (!s)
		return (0);
	i = -1;
	while (s[++i] && s[i] != '\n')
		if (s[i] == c)
			return (1);
	return (0);
}

char	*ft_strjoinspe(char *s1, char *s2)
{
	size_t	i;
	size_t	j;
	char	*dst;

	if (!s2)
		return (NULL);
	dst = (char *)malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	if (dst == NULL)
		return (NULL);
	i = 0;
	if (s1)
	{
		while (s1[i])
		{
			dst[i] = s1[i];
			i++;
		}
		free(s1);
	}
	j = -1;
	while (s2[++j])
		dst[i + j] = s2[j];
	dst[i + j] = 0;
	return (dst);
}

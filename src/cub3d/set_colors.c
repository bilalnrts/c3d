/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_colors.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderviso <aderviso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/14 19:42:31 by aderviso          #+#    #+#             */
/*   Updated: 2023/09/14 19:49:53 by aderviso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3.h"

void	ft_set_colors(t_map *map, char **buffer, char **colors)
{
	if (buffer[0][0] == 'F')
		map->f_color_rgb = ft_atoi(colors[0]) << 16
			| ft_atoi(colors[1]) << 8 | ft_atoi(colors[2]);
	else if (buffer[0][0] == 'C')
		map->c_color_rgb = ft_atoi(colors[0]) << 16
			| ft_atoi(colors[1]) << 8 | ft_atoi(colors[2]);
}

void	ft_is_rgb(char *str, t_map *map)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] >= '0' && str[i] <= '9')
			i++;
		else
			ft_free_all_msg(map, "Error !\nColors must be numbers !\n");
	}
	i = ft_atoi(str);
	if (i > 255 || i < 0)
		ft_free_all_msg(map, "Error !\nColors must be in the range 0-255 !\n");
}

void	ft_get_color(char *line, t_map *map, int i)
{
	char	**buffer;
	char	**colors;
	char	*newline;

	newline = ft_strtrim(line, " \n\t");
	buffer = ft_texture_split(newline, ft_find_seperator(newline, map));
	free(newline);
	if (buffer && buffer[1])
	{
		newline = ft_strtrim(buffer[1], " \t");
		colors = ft_split(newline, ',');
		while (colors[++i])
			ft_is_rgb(colors[i], map);
		if (i != 3)
			ft_free_all_msg(map, "Error !\nColors must be rgb formatting !\n");
		ft_set_colors(map, buffer, colors);
		while (--i >= 0 && colors[i])
			free(colors[i]);
		free(colors);
		free(newline);
	}
	while (buffer[++i])
		free(buffer[i]);
	free(buffer);
}

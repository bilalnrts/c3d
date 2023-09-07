#include "../../inc/cub3.h"

void	ft_free_textures(t_map *map)
{
	if (map -> no_texture)
		free(map -> no_texture);
	if (map -> so_texture)
		free(map -> so_texture);
	if (map -> we_texture)
		free(map -> we_texture);
	if (map -> ea_texture)
		free(map -> ea_texture);
	if (map -> f_color_rgb)
		free(map -> f_color_rgb);
	if (map -> c_color_rgb)
		free(map -> c_color_rgb);
	if (map -> fd && map -> fd != -1)
		close(map -> fd);
}


void	ft_free_map_buffer(t_map *map)
{
	int	i;

	i = 0;
	if (map -> map)
	{
		if (map -> map[i])
		{
			while (map -> map[i])
			{
				free(map -> map[i]);
				i++;
			}
		}
		free(map -> map);
	}
	i = 0;
	if (map -> buffer)
	{
		if (map -> buffer[i])
		{
			while (map -> buffer[i])
			{
				free(map -> buffer[i]);
				i++;
			}
		}
		free(map -> buffer);
	}
	ft_free_textures(map);
}
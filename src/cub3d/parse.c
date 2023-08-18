#include "../../inc/cub3.h"

void	ft_init_map(t_map *map)
{
	map->map = NULL;
	map->map_width = 0;
	map->map_height = 0;
}

void	ft_parse_map(t_map *map, char *line)
{

}

void	ft_read_map(t_map *map, char *path)
{
	char	*buffer;
	char	**map;
	int		fd;

	fd = open(path, O_RDONLY);
	if (fd < 0)
	{
		ft_printf("Error\nCan't open file");
		exit(1);
	}
	buffer = ft_get_map(fd);
}

char	*ft_join(char *line, char c)
{
	int		i;
	char	*str;

	i = 0;
	while (line[i])
		i++;
	str = malloc(i + 2);
	i = 0;
	while (line[i])
	{
		str[i] = line[i];
		i++;
	}
	str[i] = c;
	str[i + 1] = '\0';
	free(line);
	return (str);
}

char	*ft_get_map(int fd)
{
	char	buffer;
	char	*line;
	int		rd_bytes;

	rd_bytes = 1;
	line = malloc(1);
	line[0] = '\0';
	while (rd_bytes > 0)
	{
		rd_bytes = read(fd, &buffer, 1);
		if ((rd_bytes == 0 && line[0] == '\0') || rd_bytes < 0)
		{
			free(line);
			return (0);
		}
		if (rd_bytes == 0 && line[0] != '\0')
			return (line);
		line = ft_join(line, buffer);
	}
	return (line);
}

void	ft_join_map(t_map *map, char *line)
{
	int		i;
	char	**new_map;

	i = 0;
	if (!map->map)
	{
		map->map = malloc(sizeof(char *) * 2);
		map->map[0] = line;
		map->map[1] = NULL;
		return ;
	}
	while (map->map[i])
		i++;
	new_map = malloc(sizeof(char *) * (i + 2));
	i = 0;
	while (map->map[i])
	{
		new_map[i] = map->map[i];
		i++;
	}
	new_map[i] = line;
	new_map[i + 1] = NULL;
	free(map->map);
	map->map = new_map;
}

int main() {
	ft_printf("Hello World!");
	return (0);
}

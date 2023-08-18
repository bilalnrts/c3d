#include "../../inc/cub3.h"

void	ft_init_map(t_map *map, char *path)
{
	map->map = NULL;
	map->fd = open(path, O_RDONLY);
	map->map_width = 0;
	map->map_height = 0;
	map->no_texture = NULL;
	map->so_texture = NULL;
	map->we_texture = NULL;
	map->ea_texture = NULL;
	map->f_color_rgb = NULL;
	map->c_color_rgb = NULL;
}

// void	ft_parse_map(t_map *map, char *line)
// {

// }

// void	ft_read_map(t_map *map, char *path)
// {
// 	char	*buffer;
// 	char	**map;
// 	int		fd;

// 	fd = open(path, O_RDONLY);
// 	if (fd < 0)
// 	{
// 		ft_printf("Error\nCan't open file");
// 		exit(1);
// 	}
// 	buffer = ft_get_map(fd);
// }

// char	*ft_join(char *line, char c)
// {
// 	int		i;
// 	char	*str;

// 	i = 0;
// 	while (line[i])
// 		i++;
// 	str = malloc(i + 2);
// 	i = 0;
// 	while (line[i])
// 	{
// 		str[i] = line[i];
// 		i++;
// 	}
// 	str[i] = c;
// 	str[i + 1] = '\0';
// 	free(line);
// 	return (str);
// }

// char	*ft_get_map(int fd)
// {
// 	char	buffer;
// 	char	*line;
// 	int		rd_bytes;

// 	rd_bytes = 1;
// 	line = malloc(1);
// 	line[0] = '\0';
// 	while (rd_bytes > 0)
// 	{
// 		rd_bytes = read(fd, &buffer, 1);
// 		if ((rd_bytes == 0 && line[0] == '\0') || rd_bytes < 0)
// 		{
// 			free(line);
// 			return (0);
// 		}
// 		if (rd_bytes == 0 && line[0] != '\0')
// 			return (line);
// 		line = ft_join(line, buffer);
// 	}
// 	return (line);
// }

// void	ft_join_map(t_map *map, char *line)
// {
// 	int		i;
// 	char	**new_map;

// 	i = 0;
// 	if (!map->map)
// 	{
// 		map->map = malloc(sizeof(char *) * 2);
// 		map->map[0] = line;
// 		map->map[1] = NULL;
// 		return ;
// 	}
// 	while (map->map[i])
// 		i++;
// 	new_map = malloc(sizeof(char *) * (i + 2));
// 	i = 0;
// 	while (map->map[i])
// 	{
// 		new_map[i] = map->map[i];
// 		i++;
// 	}
// 	new_map[i] = line;
// 	new_map[i + 1] = NULL;
// 	free(map->map);
// 	map->map = new_map;
// }

int	ft_line_lenght(char *line)
{
	int	i;
	int total;

	i = 0;
	total = 0;
	while (line[i])
	{
		if (line[i] == '\t')
			total += 4;
		else
			total++;
		i++;
	}
	return (total);
}

char	*modificate_line(char *line)
{
	int		i;
	int		j;
	int		limit;
	char	*new_line;

	i = 0;
	j = 0;
	new_line = malloc(ft_line_lenght(line) + 1);
	while (line[i])
	{
		if (line[i] == '\t')
		{
			limit = 4;
			while (limit)
			{
				new_line[j] = '2';
				limit--;
				j++;
			}
		}
		else if (line[i] == ' ')
		{
			new_line[j] = '2';
			j++;
		}
		else
		{
			new_line[j] = line[i];
			j++;
		}
		i++;
	}
	new_line[j] = '\0';
	free(line);
	return (new_line);
}

int main(int ac, char **av) {
	t_map	*map;
	char	*line;
	int		fd;

	if (ac != 2)
	{
		printf("Error\nWrong number of arguments");
		exit(1);
	}
	map = malloc(sizeof(t_map));
	ft_init_map(map, av[1]);
	fd = open(av[1], O_RDONLY);
	while(1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		line = modificate_line(line);
		printf("%s", line);
		free(line);
	}
	return (0);
}

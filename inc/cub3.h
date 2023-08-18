#ifndef CUB3_H
# define CUB3_H

# include "../lib/libft/inc/libft.h"
# include "../lib/libft/inc/ft_printf.h"
# include "../lib/libft/inc/get_next_line.h"
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <stdio.h>
# include <math.h>

enum	e_direction
{
	NORTH,
	SOUTH,
	WEST,
	EAST
};

typedef struct s_map
{
	char	**map;
	char	**buffer;
	char	*no_texture;
	char	*so_texture;
	char	*we_texture;
	char	*ea_texture;
	char	*f_color_rgb;
	char	*c_color_rgb;
	enum e_direction	start_position;
	int		map_width;
	int		map_height;
	int		fd;
}				t_map;

//map_creation
void	ft_create_map(t_map *map);
void	ft_join_buffer(t_map *map, char *line);
void	ft_set_directions(t_map *map, int i, int checker);

#endif

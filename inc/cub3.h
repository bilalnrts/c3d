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
	UNKNOWN,
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
	int		*f_color_rgb; // check valid color
	int		*c_color_rgb; // check valid color
	enum e_direction	start_position;
	int		map_width;
	int		map_height;
	int		max_width;
	int		max_index;
	int		buffer_height;
	int		player_x;
	int		player_y;
	int		fd;
}				t_map;

//map_creation
void	ft_create_map(t_map *map);
void	ft_join_buffer(t_map *map, char *line);
void	ft_set_directions(t_map *map, int i, int checker);
void	ft_get_map(t_map *map, int i);
void	ft_find_start_map(t_map *map, int i, int checker);
void	ft_set_player_position(t_map *map, char c, int x, int y);
void	ft_check_player(t_map *map);
void	ft_is_rgb(char *str, t_map *map);
void	ft_get_color(char *line, t_map *map);
void	ft_set_colors(t_map *map, char **buffer, char **colors);

//map_validation
int		**ft_give_directions(int i, t_map *map);
void	ft_check_walls(t_map *map, int i, int j);
void	ft_check_valid_map(t_map *map);
void	ft_is_there_enter_in_map(t_map *map);
void	ft_is_map_letters(t_map *map);

//lines
int		ft_line_lenght(char *line);
char	*modificate_line(char *line);

//free
void	ft_free_map(t_map *map);
void	ft_free_buffer(t_map *map);
void	ft_free_all(t_map *map);
void	ft_free_all_msg(t_map *map, char *str);
void	ft_free_textures(t_map *map);

//parse
void	ft_init_map(t_map *map, char *path);

//set width
void	ft_set_width(t_map *map);

#endif

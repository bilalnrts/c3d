#ifndef CUB3_H
# define CUB3_H

# include "../lib/libft/inc/libft.h"
# include "../lib/libft/inc/ft_printf.h"
# include "../lib/libft/inc/get_next_line.h"
# include "../lib/mlx/mlx.h"
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <stdio.h>
# include <math.h>

# define WIDTH 960
# define HEIGHT 540

enum	e_direction
{
	UNKNOWN,
	NORTH,
	SOUTH,
	WEST,
	EAST,
	LEFT = -1,
	RIGHT = 1,
	NONE
};

typedef struct s_img{
	void	*window;
	int		*image;
	char	*data;
	int		bpp;
	int		sizeline;
	int		endian;
}	t_img;

typedef struct s_texture{
	void	*image;
	char	*path;
	char	*data;
	int		use;
	int		w;
	int		h;
	int		bpp;
	int		sizeline;
	int		endian;
}	t_texture;

typedef struct player
{
	double	x;
	double	y;
	double	dir_x;
	double	dir_y;
	double	plane_x;
	double	plane_y;
	double	camera_x;
	double	ray_dir_x;
	double	ray_dir_y;
	int		map_x;
	int		map_y;
	int		move_no;
	int		move_so;
	int		move_we;
	int		move_ea;
	int		turn;
	double 	speed;
}	t_player;

typedef struct s_map
{
	void	*mlx;
	t_img	img;
	t_texture	*no;
	t_texture	*so;
	t_texture	*we;
	t_texture	*ea;
	t_player	*player;
	double	side_dist_x;
	double	side_dist_y;
	double	delta_dist_x;
	double	delta_dist_y;
	double	perp_wall_dist;
	int		step_x;
	int		step_y;
	int		hit;
	int		side;
	int		line_height;
	int		draw_start;
	int		draw_end;
	double 	wall_x;
	double	step;
	unsigned int		color;
	double		tex_x;
	int		tex_y;
	int		tex_width;
	int		tex_height;
	double		tex_pos;
	int		tex_step;
	char	**map;
	char	**buffer;
	char	*no_texture;
	char	*so_texture;
	char	*we_texture;
	char	*ea_texture;
	int		f_color_rgb;
	int		c_color_rgb;
	enum e_direction	start_position;
	int		map_width;
	int		map_height;
	int		max_width;
	int		max_index;
	int		buffer_height;
	int		fd;
}				t_map;

//mlx_init
void	ft_mlx_init(t_map *map);
void	ft_texture_init(t_map *map);
void	ft_player_direction(t_map *map);

//keyboard_interaction
int		ft_press_key(int key, t_map *map);
int		ft_release_key(int key, t_map *map);
int		ft_close(int key, t_map *map);

//map_creation
void	ft_create_map(t_map *map);
void	ft_join_buffer(t_map *map, char *line);
void	ft_set_directions(t_map *map, int i, int checker);
void	ft_get_map(t_map *map, int i);
void	ft_find_start_map(t_map *map, int i, int checker);
void	ft_set_player_position(t_map *map, char c, int x, int y);
void	ft_check_player(t_map *map);
void	ft_is_rgb(char *str, t_map *map);
void	ft_set_colors(t_map *map, char **buffer, char **colors);

//set_textures
char	ft_find_seperator(char *str, t_map *map);

//set_colors
void	ft_get_color(char *line, t_map *map);


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
int		ft_render_next_frame(t_map *map);
void	ft_init_player(t_map *map);

//set width
void	ft_set_width(t_map *map);

//keyboard interaction
int		ft_press_key(int key, t_map *map);
int		ft_release_key(int key, t_map *map);
int		ft_close(int key, t_map *map);

//move
void	ft_move_east_west(t_map *map, int dir);
void	ft_move_north_south(t_map *map, int dir);
void	ft_turn(t_map *map, int direction);
void	ft_move(t_map *map);

//raycast
void    ft_init_raycast(t_map *map, int x);
void    ft_calculate_step(t_map *map);
void    ft_calculate_side_dist(t_map *map);
void    ft_calculate_draw_start_end(t_map *map);
void    ft_draw_texture(t_map *map, int x);
void    ft_raycast(t_map *map);

#endif

#include "../../inc/cub3.h"

void ft_mlx_init(t_map *map)
{
    map->mlx = mlx_init();
    map->img.window = mlx_new_window(map->mlx, WIDTH, HEIGHT, "Cub3D");
    map->img.image = (int *)mlx_new_image(map->mlx, WIDTH, HEIGHT);
    map->img.data = mlx_get_data_addr(map->img.image, &map->img.bpp, &map->img.sizeline, &map->img.endian);
    ft_texture_init(map);
    ft_player_direction(map);
    map->map[(int)map->player->y][(int)map->player->x] = '0';
}

void ft_texture_init(t_map *map)
{
    map->no = ft_calloc(sizeof(t_texture), 1);
    map->so = ft_calloc(sizeof(t_texture), 1);
    map->we = ft_calloc(sizeof(t_texture), 1);
    map->ea = ft_calloc(sizeof(t_texture), 1);
    map->no->image = mlx_xpm_file_to_image(map->mlx, "./textures/wall1.xpm", &map->no->w, &map->no->h);
    map->so->image = mlx_xpm_file_to_image(map->mlx, "./textures/wall2.xpm", &map->so->w, &map->so->h);
    map->we->image = mlx_xpm_file_to_image(map->mlx, "./textures/wall3.xpm", &map->we->w, &map->we->h);
    map->ea->image = mlx_xpm_file_to_image(map->mlx, "./textures/wall4.xpm", &map->ea->w, &map->ea->h);
	if (!map->no->image || !map->so->image || !map->we->image || !map->ea->image)
    {
        printf("wrong texture files!\n"); // leakleri bitir
		exit(1);
    }
    map->no->data = mlx_get_data_addr(map->no->image, &map->no->bpp, &map->no->sizeline, &map->no->endian);
    map->so->data = mlx_get_data_addr(map->so->image, &map->so->bpp, &map->so->sizeline, &map->so->endian);
    map->we->data = mlx_get_data_addr(map->we->image, &map->we->bpp, &map->we->sizeline, &map->we->endian);
    map->ea->data = mlx_get_data_addr(map->ea->image, &map->ea->bpp, &map->ea->sizeline, &map->ea->endian);
}

void ft_player_direction(t_map *map)
{
    if (map->start_position == NORTH)
        map->player->dir_x = -1;
    else if (map->start_position == SOUTH)
        map->player->dir_x = 1;
    else if (map->start_position == WEST)
        map->player->dir_y = -1;
    else if (map->start_position == EAST)
        map->player->dir_y = 1;
    map->player->plane_x = -map->player->dir_y * 0.66;
    map->player->plane_y = map->player->dir_x * 0.66;
}


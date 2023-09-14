#include "../../inc/cub3.h"

int ft_press_key(int key, t_map *map)
{
    if (key == 13)
        map->player->move_no = 1;
    else if (key == 1)
        map->player->move_so = 1;
    else if (key == 0)
        map->player->move_we = 1;
    else if (key == 2)
        map->player->move_ea = 1;
    else if (key == 123)
        map->player->turn = LEFT;
    else if (key == 124)
        map->player->turn = RIGHT;
    else if (key == 53)
        ft_close(key, map);
    return (0);
}

int ft_release_key(int key, t_map *map)
{
    if (key == 13)
        map->player->move_no = 0;
    else if (key == 1)
        map->player->move_so = 0;
    else if (key == 0)
        map->player->move_we = 0;
    else if (key == 2)
        map->player->move_ea = 0;
    else if (key == 123)
        map->player->turn = NONE;
    else if (key == 124)
        map->player->turn = NONE;
    return (0);
}

int ft_close(int key, t_map *map)
{
    (void)map;
    (void)key;
    printf("cub3d closed succesfully!!");
    exit(0);
    return (0);
}

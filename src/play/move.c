#include "../../inc/cub3.h"

// dir = 1 for east, -1 for west
void ft_move_east_west(t_map *map, int dir)
{
    if (map->map[(int)(map->player->y)][(int)(map->player->x - dir * map->player->dir_y * map->player->speed)] < '1')
        map->player->x -= dir * map->player->dir_y * map->player->speed;
    if (map->map[(int)(map->player->y + dir * map->player->dir_x * map->player->speed)][(int)(map->player->x)] < '1')
        map->player->y += dir * map->player->dir_x * map->player->speed;
}

// dir = 1 for north, -1 for south
void ft_move_north_south(t_map *map, int dir)
{
    if (map->map[(int)(map->player->y)][(int)(map->player->x + dir * map->player->dir_x * map->player->speed)] < '1')
        map->player->x += dir * map->player->dir_x * map->player->speed;
    if (map->map[(int)(map->player->y + dir * map->player->dir_y * map->player->speed)][(int)(map->player->x)] < '1')
        map->player->y += dir * map->player->dir_y * map->player->speed;
}

void ft_turn(t_map *map, int direction)
{
    double old_dir_x;
    double old_plane_x;

    map->player->speed /= 2;
    old_dir_x = map->player->dir_x;
    old_plane_x = map->player->plane_x;
    map->player->dir_x = map->player->dir_x * cos(direction * map->player->speed) - map->player->dir_y * sin(direction * map->player->speed);
    map->player->dir_y = old_dir_x * sin(direction * map->player->speed) + map->player->dir_y * cos(direction * map->player->speed);
    map->player->plane_x = map->player->plane_x * cos(direction * map->player->speed) - map->player->plane_y * sin(direction * map->player->speed);
    map->player->plane_y = old_plane_x * sin(direction * map->player->speed) + map->player->plane_y * cos(direction * map->player->speed);
    map->player->speed *= 2;
}

void ft_move(t_map *map)
{
    if (map->player->move_ea == 1)
        ft_move_east_west(map, 1);
    else if (map->player->move_we == 1)
        ft_move_east_west(map, -1);
    if (map->player->move_no == 1)
        ft_move_north_south(map, 1);
    else if (map->player->move_so == 1)
        ft_move_north_south(map, -1);
    if (map->player->turn == LEFT)
        ft_turn(map, LEFT);
    else if (map->player->turn == RIGHT)
        ft_turn(map, RIGHT);
}
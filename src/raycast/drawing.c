#include "../../inc/cub3.h"

void    ft_calculate_draw_start_end(t_map *map)
{
    map->draw_start = -map->line_height / 2 + HEIGHT / 2;
    if (map->draw_start < 0)
        map->draw_start = 0;
    map->draw_end = map->line_height / 2 + HEIGHT / 2;
    if (map->draw_end >= HEIGHT)
        map->draw_end = HEIGHT - 1;
	if (map->side == 0)
		map->wall_x = map->player->y + map->perp_wall_dist * map->player->ray_dir_y;
	else
		map->wall_x = map->player->x + map->perp_wall_dist * map->player->ray_dir_x;
	map->wall_x -= floor(map->wall_x);
}

void    ft_draw_texture(t_map *map, int x)
{
    int y;

    y = - 1;
    map->tex_height = 64;
    map->tex_width = 64;
    map->tex_x = (int)(map->wall_x * (double)map->tex_width);
	map->step = 1.0 * map->tex_height / map->line_height;
	map->tex_pos = (map->draw_start - HEIGHT / 2 + map->line_height / 2) * map->step;
    while (++y < map->draw_start)
        *(unsigned int*)(map->img.data + y * map->img.sizeline + x * map->img.bpp / 8) = map->c_color_rgb;
    while (++y < map->draw_end)
    {
        map->tex_y = (int)map->tex_pos & (map->tex_height - 1);
        map->tex_pos += map->step;
        if (map->side == 0 && map->player->ray_dir_x > 0)
            map->color = *(unsigned int*)(map->no->data + map->tex_y * map->no->sizeline + (int)map->tex_x * map->no->bpp / 8);
        else if (map->side == 0 && map->player->ray_dir_x < 0)
            map->color = *(unsigned int*)(map->so->data + map->tex_y * map->so->sizeline + (int)map->tex_x * map->so->bpp / 8);
        else if (map->side == 1 && map->player->ray_dir_y < 0)
            map->color = *(unsigned int*)(map->ea->data + map->tex_y * map->ea->sizeline + (int)map->tex_x * map->ea->bpp / 8);
        else if (map->side == 1 && map->player->ray_dir_y > 0)
            map->color = *(unsigned int*)(map->we->data + map->tex_y * map->we->sizeline + (int)map->tex_x * map->we->bpp / 8);
        *(unsigned int*)(map->img.data + y * map->img.sizeline + x * (map->img.bpp / 8)) = map->color;
    }
    while (++y < HEIGHT)
        *(unsigned int*)(map->img.data + y * map->img.sizeline + x * (map->img.bpp / 8)) = map->f_color_rgb;
}
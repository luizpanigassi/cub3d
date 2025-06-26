/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luinasci <luinasci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 19:09:48 by luinasci          #+#    #+#             */
/*   Updated: 2025/06/26 19:37:26 by luinasci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_line_on_minimap(t_mlx_data *mlx, t_line *line)
{
	t_line_state	s;

	s.dx = line->end_x - line->start_x;
	s.dy = line->end_y - line->start_y;
	s.sx = get_step_direction(line->start_x, line->end_x);
	s.sy = get_step_direction(line->start_y, line->end_y);
	s.dx = abs_int(s.dx);
	s.dy = abs_int(s.dy);
	s.err = s.dx - s.dy;
	s.x = line->start_x;
	s.y = line->start_y;
	while (1)
	{
		put_pixel_minimap(mlx, s.x, s.y, line->color);
		if (s.x == line->end_x && s.y == line->end_y)
			break ;
		update_line_state(&s);
	}
}

void	draw_minimap_tile(t_data *data, t_mlx_data *mlx,
	t_minimap_tile *tile_info)
{
	char				tile;
	int					color;
	t_square_draw_ctx	ctx;

	tile = data->map[tile_info->y][tile_info->x];
	color = 0x000000;
	if (tile == '1')
		color = 0xFFFFFF;
	else if (tile == '0' || ft_strchr("NSEW", tile))
		color = 0x808080;
	else if (tile == 'D')
	{
		if (is_door_open(data, tile_info->x, tile_info->y))
			color = 0x00FF00;
		else
			color = 0xFF0000;
	}
	ctx.mlx = mlx;
	ctx.x = tile_info->x * tile_info->tile_size;
	ctx.y = tile_info->y * tile_info->tile_size;
	ctx.tile_size = tile_info->tile_size;
	ctx.color = color;
	draw_square(&ctx);
}

int	get_minimap_tile_size(int map_width, int map_height)
{
	int	tile_w;
	int	tile_h;
	int	tile_size;

	tile_w = MINIMAP_MAX_W / map_width;
	tile_h = MINIMAP_MAX_H / map_height;
	if (tile_w < tile_h)
		tile_size = tile_w;
	else
		tile_size = tile_h;
	if (tile_size < 1)
		tile_size = 1;
	return (tile_size);
}

void	minimap(t_data *data, t_mlx_data *mlx)
{
	int				tile_size;
	int				y;
	int				x;
	t_minimap_tile	tile_info;

	tile_size = get_minimap_tile_size(data->map_width, data->map_height);
	y = 0;
	while (y < data->map_height)
	{
		x = 0;
		while (x < data->map_width)
		{
			tile_info.x = x;
			tile_info.y = y;
			tile_info.tile_size = tile_size;
			draw_minimap_tile(data, mlx, &tile_info);
			x++;
		}
		y++;
	}
	draw_player(mlx, tile_size);
	draw_vision(mlx, tile_size);
}

void	put_pixel_minimap(t_mlx_data *mlx, int x, int y, int color)
{
	int	offset;

	if (x >= 0 && x < W && y >= 0 && y < H)
	{
		offset = y * mlx->line_size + x * (mlx->bpp / 8);
		*(unsigned int *)(mlx->img_addr + offset) = color;
	}
}

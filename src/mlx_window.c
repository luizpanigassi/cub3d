/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_window.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luinasci <luinasci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 20:01:19 by jcologne          #+#    #+#             */
/*   Updated: 2025/06/24 18:59:24 by luinasci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void draw_vision(t_mlx_data *mlx, int tile_size)
{
	int line_length = tile_size * 2;
	int start_x = (int)(mlx->pos_x * tile_size);
	int start_y = (int)(mlx->pos_y * tile_size);
	int end_x = (int)(start_x + mlx->dir_x * line_length);
	int end_y = (int)(start_y + mlx->dir_y * line_length);
	int dx = end_x - start_x;
	int dy = end_y - start_y;
	int sx = -1;
	int sy = -1;
	int err;
	int e2;
	int x;
	int y;
	int offset;

	if (start_x < end_x)
		sx = 1;
	if (start_y < end_y)
		sy = 1;
	dx = (dx < 0) ? -dx : dx;
	dy = (dy < 0) ? -dy : dy;
	err = dx - dy;
	x = start_x;
	y = start_y;
	while (1)
	{
		if (x >= 0 && x < W && y >= 0 && y < H)
		{
			offset = y * mlx->line_size + x * (mlx->bpp / 8);
			*(unsigned int *)(mlx->img_addr + offset) = 0x00FF00;
		}
		if (x == end_x && y == end_y)
			break ;
		e2 = 2 * err;
		if (e2 > -dy)
		{
			err -= dy;
			x += sx;
		}
		if (e2 < dx)
		{
			err += dx;
			y += sy;
		}
	}
}


static void draw_square(t_mlx_data *mlx, int x, int y, int tile_size, int color)
{
	int dx;
	int dy;
	int px;
	int py;
	int offset;

	dy = 0;
	while (dy < tile_size)
	{
		dx = 0;
		while (dx < tile_size)
		{
			px = x + dx;
			py = y + dy;
			if (px >= 0 && px < W && py >= 0 && py < H)
			{
				offset = py * mlx->line_size + px * (mlx->bpp / 8);
				*(unsigned int *)(mlx->img_addr + offset) = color;
			}
			dx++;
		}
		dy++;
	}
}

static void draw_player(t_mlx_data *mlx, int tile_size)
{
	int center_x = (int)(mlx->pos_x * tile_size);
	int center_y = (int)(mlx->pos_y * tile_size);
	int half = tile_size / 4;
	int y = -half;
	int x;
	int px;
	int py;
	int offset;

	while (y < half)
	{
		x = -half;
		while (x < half)
		{
			px = center_x + x;
			py = center_y + y;
			if (px >= 0 && px < W && py >= 0 && py < H)
			{
				offset = py * mlx->line_size + px * (mlx->bpp / 8);
				*(unsigned int *)(mlx->img_addr + offset) = 0xFF0000;
			}
			x++;
		}
		y++;
	}
}

static void minimap(t_data *data, t_mlx_data *mlx)
{
	int tile_w = MINIMAP_MAX_W / data->map_width;
	int tile_h = MINIMAP_MAX_H / data->map_height;
	int tile_size;

	if (tile_w < tile_h)
		tile_size = tile_w;
	else
		tile_size = tile_h;
	if (tile_size < 1)
		tile_size = 1;

	int y = 0;
	int x;
	char tile;
	int color;

	while (y < data->map_height)
	{
		x = 0;
		while (data->map[y][x])
		{
			tile = data->map[y][x];
			color = 0x000000;
			if (tile == '1')
				color = 0xFFFFFF;
			else if (tile == '0' || ft_strchr("NSEW", tile))
				color = 0x808080;
			draw_square(mlx, x * tile_size, y * tile_size, tile_size, color);
			x++;
		}
		y++;
	}
	draw_player(mlx, tile_size);
	draw_vision(mlx, tile_size);
}

void redraw_minimap(t_data *data, t_mlx_data *mlx)
{
	ft_bzero(mlx->img_addr, H * mlx->line_size);
	draw_background(mlx, data->ceiling, data->floor);
	minimap(data, mlx);
	mlx_put_image_to_window(mlx->mlx, mlx->win, mlx->img, 0, 0);
}

static int game_loop(t_game *game)
{
	update_player_position(game);
	redraw_minimap(game->data, game->mlx);
	return (0);
}

void render_image(t_data *data)
{
	t_mlx_data *mlx;
	t_game *game;

	mlx = malloc(sizeof(t_mlx_data));
	game = malloc(sizeof(t_game));
	game->data = data;
	game->mlx = mlx;
	mlx->data = data;
	mlx->keys = &game->keys;
	init_window(mlx);
	init_player(game);
	//redraw_minimap(data, mlx);
	events(game);
	mlx_loop_hook(mlx->mlx, game_loop, game);
	mlx_loop(mlx->mlx);
}

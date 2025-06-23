/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_window.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luinasci <luinasci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 20:01:19 by jcologne          #+#    #+#             */
/*   Updated: 2025/06/23 17:33:36 by luinasci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void draw_square(t_mlx_data *mlx, int x, int y, int color)
{
	int dy;
	int dx;
	int offset;
	int px;
	int py;

	dy = 0;
	while (dy < TILE_SIZE)
	{
		dx = 0;
		while (dx < TILE_SIZE)
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

static void draw_player(t_mlx_data *mlx)
{
	int player_px = (int)(mlx->pos_x * TILE_SIZE);
	int player_py = (int)(mlx->pos_y * TILE_SIZE);
	int y = -(TILE_SIZE / 3) / 2;
	int x;
	int offset, px, py;

	while (y < (TILE_SIZE / 3) / 2)
	{
		x = -(TILE_SIZE / 3) / 2;
		while (x < (TILE_SIZE / 3) / 2)
		{
			px = player_px + x;
			py = player_py + y;
			if (px >= 0 && px < W && py >= 0 && py < H)
			{
				offset = (py * mlx->line_size) + (px * (mlx->bpp / 8));
				*(unsigned int *)(mlx->img_addr + offset) = 0xFF0000;
			}
			x++;
		}
		y++;
	}
}

static void minimap(t_data *data, t_mlx_data *mlx)
{
	int y;
	int x;
	int color;
	char tile;

	y = 0;
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


			draw_square(mlx, x * TILE_SIZE, y * TILE_SIZE, color);
			x++;
		}
		y++;
	}
	draw_player(mlx);
}

void redraw_minimap(t_data *data, t_mlx_data *mlx)
{
	ft_bzero(mlx->img_addr, H * mlx->line_size);
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
	redraw_minimap(data, mlx);
	events(game);
	mlx_loop_hook(mlx->mlx, game_loop, game);
	mlx_loop(mlx->mlx);
}

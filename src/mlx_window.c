/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_window.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcologne <jcologne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 20:01:19 by jcologne          #+#    #+#             */
/*   Updated: 2025/06/23 14:03:53 by jcologne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	draw_square(t_mlx_data *mlx, int x, int y, int color)
{
	int	dy;
	int	dx;
	int	offset;

	dy = 0;
	while (dy < TILE_SIZE)
	{
		dx = 0;
		while (dx < TILE_SIZE)
		{
			offset = (y + dy) * mlx->line_size + (x + dx) * (mlx->bpp / 8);
			*(unsigned int *)(mlx->img_addr + offset) = color;
			dx++;
		}
		dy++;
	}
}

static void	draw_player(t_mlx_data *mlx)
{
	int	player_px;
	int	player_py;
	int	y;
	int	x;
	int	offset;

	player_px = (int)(mlx->pos_x * TILE_SIZE);
	player_py = (int)(mlx->pos_y * TILE_SIZE);

	y = -(TILE_SIZE / 3) / 2;

	while (y < (TILE_SIZE / 3) / 2)
	{
		x = -(TILE_SIZE / 3) / 2;
		while (x < (TILE_SIZE / 3) / 2)
		{
			offset = ((player_py + y) * mlx->line_size) + ((player_px + x) * (mlx->bpp / 8));
			*(unsigned int *)(mlx->img_addr + offset) = 0xFF0000; // vermelho
			x++;
		}
		y++;
	}
}

static void	minimap(t_data *data, t_mlx_data *mlx)
{
	int		y;
	int		x;
	int		color;
	char	tile;

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
			else if (tile == '0' || tile == 'N' || tile == 'S' || tile == 'E' || tile == 'W')
				color = 0x808080;
			draw_square(mlx, x * TILE_SIZE, y * TILE_SIZE, color);
			x++;
		}
		y++;
	}
	draw_player(mlx);
}

void	redraw_minimap(t_data *data, t_mlx_data *mlx)
{
	ft_bzero(mlx->img_addr, H * mlx->line_size);
	minimap(data, mlx);
	mlx_put_image_to_window(mlx->mlx, mlx->win, mlx->img, 0, 0);
}

static int	game_loop(t_game *game)
{
	game->mlx->pos_x = game->mlx->pos_x +0.05;//HARDCODED MOVEMENT
	update_player_position(game);
	redraw_minimap(game->data, game->mlx);
	return (0);
}

void	render_image(t_data *data)
{
	t_mlx_data	*mlx;
	t_game		*game;

	mlx = malloc(sizeof(t_mlx_data));
	game = malloc(sizeof(t_game));
	game->data = data;
	game->mlx = mlx;
	mlx->data = data;
	init_window(mlx);
	printf("mlx->mlx: %p\n", mlx->mlx);
	printf("mlx->win: %p\n", mlx->win);
	printf("mlx->img: %p\n", mlx->img);
	printf("mlx->img_addr: %p\n", mlx->img_addr);
	init_player(game);
	redraw_minimap(data, mlx);
	events(mlx);
	mlx_loop_hook(mlx->mlx, game_loop, game);
	mlx_loop(mlx->mlx);
}

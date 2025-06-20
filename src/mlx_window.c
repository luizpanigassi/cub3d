/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_window.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcologne <jcologne@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 20:01:19 by jcologne          #+#    #+#             */
/*   Updated: 2025/06/20 20:56:58 by jcologne         ###   ########.fr       */
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

static void	draw_player(t_data *data, t_mlx_data *mlx)
{
	int	player_px;
	int	player_py;

	player_px = (int)(data->player_x * TILE_SIZE);
	player_py = (int)(data->player_y * TILE_SIZE);

	int size = TILE_SIZE / 3;
	int half = size / 2;
	int y = -half;

	while (y < half)
	{
		int x = -half;
		while (x < half)
		{
			int pixel_x = player_px + x;
			int pixel_y = player_py + y;
			int offset = (pixel_y * mlx->line_size) + (pixel_x * (mlx->bpp / 8));
			*(unsigned int *)(mlx->img_addr + offset) = 0xFF0000; // vermelho
			x++;
		}
		y++;
	}
}

static void	minimap(t_data *data, t_mlx_data *mlx)
{
	int	y;
	int	x;
	int	color;
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
	draw_player(data, mlx);
}

static void	init_window(t_mlx_data *mlx)
{
	mlx->mlx = mlx_init();
	mlx->win = mlx_new_window(mlx->mlx, W, H, "Cub3d");
	mlx->img = mlx_new_image(mlx->mlx, W, H);
	mlx->img_addr = mlx_get_data_addr(mlx->img, &mlx->bpp, &mlx->line_size, &mlx->endian);
}

void redraw_minimap(t_data *data, t_mlx_data *mlx)
{
	ft_bzero(mlx->img_addr, H * mlx->line_size);
	minimap(data, mlx);
	mlx_put_image_to_window(mlx->mlx, mlx->win, mlx->img, 0, 0);
}

void	render_image(t_data *data)
{
	t_mlx_data	*mlx;

	mlx = malloc(sizeof(t_mlx_data));
	init_window(mlx);
	redraw_minimap(data, mlx);
	events(mlx);
	mlx_loop(mlx->mlx);
}

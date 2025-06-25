/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_cast.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcologne <jcologne@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 18:15:33 by jcologne          #+#    #+#             */
/*   Updated: 2025/06/25 12:52:37 by jcologne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static double	*ray_direction(t_game *game, int x)
{
	double	camera_x;
	double	*ray;

	ray = malloc(sizeof(double) * 2);
	if (!ray)
		return (NULL);
	camera_x = 2 * x / (double)(W) - 1;
	ray[0] = game->mlx->dir_x + game->mlx->plane_x * camera_x;
	ray[1] = game->mlx->dir_y + game->mlx->plane_y * camera_x;
	return (ray);
}

#include <math.h>

static double	ray_distance(t_game *game, int x)
{
	double	*dir = ray_direction(game, x);
	if (!dir)
		return (-1); // erro de alocação

	int	map_x = (int)game->mlx->pos_x;
	int	map_y = (int)game->mlx->pos_y;

	double	delta_x = fabs(1 / dir[0]);
	double	delta_y = fabs(1 / dir[1]);

	int		step_x;
	int		step_y;
	double	side_dist_x;
	double	side_dist_y;

	int		hit = 0;
	int		side;

	// STEP E DISTÂNCIA INICIAL
	if (dir[0] < 0)
	{
		step_x = -1;
		side_dist_x = (game->mlx->pos_x - map_x) * delta_x;
	}
	else
	{
		step_x = 1;
		side_dist_x = (map_x + 1.0 - game->mlx->pos_x) * delta_x;
	}
	if (dir[1] < 0)
	{
		step_y = -1;
		side_dist_y = (game->mlx->pos_y - map_y) * delta_y;
	}
	else
	{
		step_y = 1;
		side_dist_y = (map_y + 1.0 - game->mlx->pos_y) * delta_y;
	}

	// LOOP DDA
	while (!hit)
	{
		if (side_dist_x < side_dist_y)
		{
			side_dist_x += delta_x;
			map_x += step_x;
			side = 0;
		}
		else
		{
			side_dist_y += delta_y;
			map_y += step_y;
			side = 1;
		}
		if (game->data->map[map_y][map_x] == '1')
			hit = 1;
	}

	free(dir);
	if (side == 0)
		return (side_dist_x - delta_x);
	else
		return (side_dist_y - delta_y);
}

void draw_wall(t_mlx_data *mlx, int x, double dist)
{
	int line_height;
	int draw_start;
	int draw_end;
	int y;

	if (dist <= 0)
		dist = 1;

	line_height = (int)(H / (double)dist); // quanto menor a distância, maior a parede

	draw_start = -line_height / 2 + (H / 2);
	if (draw_start < 0)
		draw_start = 0;

	draw_end = (line_height / 2) + (H / 2);
	if (draw_end >= H)
		draw_end = H - 1;

	y = draw_start;
	while (y < draw_end)
	{
		// Calculate shade: closer = brighter, farther = darker
		double shade = 1.0 / (1.0 + dist * 0.1);
		if (shade < 0.2)
			shade = 0.2;
		int color = ((int)(255 * shade) << 16) | ((int)(255 * shade) << 8) | (int)(255 * shade);
		draw_pixel(mlx, x, y, color);
		y++;
	}
}


void	render_view(t_game *game)
{
	int	x;
	double	dist;

	x = 0;
	while(x < W)
	{
		dist = ray_distance(game, x);
		draw_wall(game->mlx, x, dist);
		x++;
	}
}
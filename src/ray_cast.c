/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_cast.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luinasci <luinasci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 18:15:33 by jcologne          #+#    #+#             */
/*   Updated: 2025/06/25 17:07:19 by luinasci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static double *ray_direction(t_game *game, int x)
{
	double camera_x;
	double *ray;

	ray = malloc(sizeof(double) * 2);
	if (!ray)
		return (NULL);
	camera_x = 2 * x / (double)(W)-1;
	ray[0] = game->mlx->dir_x + game->mlx->plane_x * camera_x;
	ray[1] = game->mlx->dir_y + game->mlx->plane_y * camera_x;
	return (ray);
}

t_ray_hit ray_distance(t_game *game, int x)
{
	t_ray_hit hit;
	hit.tex_id = -1;
	double *dir = ray_direction(game, x);
	if (!dir)
		return ((t_ray_hit){-1, 0, 0, 0, 0, 0});

	hit.dir_x = dir[0];
	hit.dir_y = dir[1];

	int map_x = (int)game->mlx->pos_x;
	int map_y = (int)game->mlx->pos_y;

	double delta_x = fabs(1.0 / dir[0]);
	double delta_y = fabs(1.0 / dir[1]);

	int step_x, step_y;
	double side_dist_x, side_dist_y;

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

	int hit_wall = 0;
	while (!hit_wall)
	{
		if (side_dist_x < side_dist_y)
		{
			side_dist_x += delta_x;
			map_x += step_x;
			hit.side = 0; // vertical
		}
		else
		{
			side_dist_y += delta_y;
			map_y += step_y;
			hit.side = 1; // horizontal
		}
		if (game->data->map[map_y][map_x] == '1')
			hit_wall = 1;
		else if (game->data->map[map_y][map_x] == 'D' && !is_door_open(game->data, map_x, map_y))
		{
			hit_wall = 1;
			hit.tex_id = 4; //porta
		}
	}

	// Wall distance
	if (hit.side == 0)
		hit.dist = side_dist_x - delta_x;
	else
		hit.dist = side_dist_y - delta_y;

	// Wall orientation (texture ID)
	if (hit.tex_id != 4) // If not a door
	{
		if (hit.side == 0)
			hit.tex_id = (dir[0] > 0) ? 3 : 2; // west : east
		else
			hit.tex_id = (dir[1] > 0) ? 0 : 1; // north : south
	}

	// Wall X position for texture mapping
	if (hit.side == 0)
		hit.wall_x = game->mlx->pos_y + hit.dist * dir[1];
	else
		hit.wall_x = game->mlx->pos_x + hit.dist * dir[0];
	hit.wall_x -= floor(hit.wall_x);

	free(dir);
	return (hit);
}


void draw_wall(t_mlx_data *mlx, int x, t_ray_hit hit)
{
	if (hit.dist <= 0)
		hit.dist = 1.0;

	int line_height = (int)(H / hit.dist);
	int draw_start = -line_height / 2 + H / 2;
	int draw_end = line_height / 2 + H / 2;

	if (draw_start < 0)
		draw_start = 0;
	if (draw_end >= H)
		draw_end = H - 1;

	t_img *tex = mlx->textures[hit.tex_id];
	int tex_x = (int)(hit.wall_x * (double)tex->w);

	// Flip texture X coord for correct facing direction
	if ((hit.side == 0 && hit.dir_x > 0) || (hit.side == 1 && hit.dir_y < 0))
		tex_x = tex->w - tex_x - 1;

	for (int y = draw_start; y < draw_end; y++)
	{
		int d = y * 256 - H * 128 + line_height * 128;
		int tex_y = (d * tex->h) / line_height / 256;

		int color = *(int *)(tex->addr + (tex_y * tex->line_len + tex_x * (tex->bpp / 8)));
		draw_pixel(mlx, x, y, color);
	}
}


void render_view(t_game *game)
{
	int x = 0;
	while (x < W)
	{
		t_ray_hit hit = ray_distance(game, x);
		draw_wall(game->mlx, x, hit);
		x++;
	}
}

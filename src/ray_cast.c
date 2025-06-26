/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_cast.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luinasci <luinasci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 18:15:33 by jcologne          #+#    #+#             */
/*   Updated: 2025/06/26 19:27:31 by luinasci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

double	*ray_direction(t_game *game, int x)
{
	double	camera_x;
	double	*ray;

	ray = malloc(sizeof(double) * 2);
	if (!ray)
		return (NULL);
	camera_x = 2 * x / (double)(W)-1;
	ray[0] = game->mlx->dir_x + game->mlx->plane_x * camera_x;
	ray[1] = game->mlx->dir_y + game->mlx->plane_y * camera_x;
	return (ray);
}

void	perform_dda(t_game *game, t_dda_ctx *ctx)
{
	ctx->hit_wall = 0;
	while (!ctx->hit_wall)
	{
		if (ctx->side_dist_x < ctx->side_dist_y)
		{
			ctx->side_dist_x += ctx->delta_x;
			ctx->map_x += ctx->step_x;
			ctx->side = 0;
		}
		else
		{
			ctx->side_dist_y += ctx->delta_y;
			ctx->map_y += ctx->step_y;
			ctx->side = 1;
		}
		if (game->data->map[ctx->map_y][ctx->map_x] == '1')
			ctx->hit_wall = 1;
		else if (game->data->map[ctx->map_y][ctx->map_x] == 'D'
			&& !is_door_open(game->data, ctx->map_x, ctx->map_y))
		{
			ctx->hit_wall = 1;
			ctx->tex_id = 4;
		}
	}
}

void	init_dda_ctx(t_game *game, double *dir, t_dda_ctx *ctx)
{
	ctx->map_x = (int)game->mlx->pos_x;
	ctx->map_y = (int)game->mlx->pos_y;
	ctx->delta_x = fabs(1.0 / dir[0]);
	ctx->delta_y = fabs(1.0 / dir[1]);
	if (dir[0] < 0)
	{
		ctx->step_x = -1;
		ctx->side_dist_x = (game->mlx->pos_x - ctx->map_x) * ctx->delta_x;
	}
	else
	{
		ctx->step_x = 1;
		ctx->side_dist_x = (ctx->map_x + 1.0 - game->mlx->pos_x) * ctx->delta_x;
	}
	if (dir[1] < 0)
	{
		ctx->step_y = -1;
		ctx->side_dist_y = (game->mlx->pos_y - ctx->map_y) * ctx->delta_y;
	}
	else
	{
		ctx->step_y = 1;
		ctx->side_dist_y = (ctx->map_y + 1.0 - game->mlx->pos_y) * ctx->delta_y;
	}
}

void	draw_wall_column(t_mlx_data *mlx, int x,
			t_wall_draw_ctx *ctx, double dist)
{
	while (ctx->y < ctx->draw_end)
	{
		ctx->d = ctx->y * 256 - H * 128 + ctx->line_height * 128;
		ctx->tex_y = (ctx->d * ctx->tex->h) / ctx->line_height / 256;
		ctx->color = *(int *)(ctx->tex->addr + (ctx->tex_y
					* ctx->tex->line_len + ctx->tex_x * (ctx->tex->bpp / 8)));
		ctx->color = apply_shade(ctx->color, dist);
		draw_pixel(mlx, x, ctx->y, ctx->color);
		ctx->y++;
	}
}

void	render_view(t_game *game)
{
	int			x;
	t_ray_hit	hit;

	x = 0;
	while (x < W)
	{
		hit = ray_distance(game, x);
		draw_wall(game->mlx, x, hit);
		x++;
	}
}

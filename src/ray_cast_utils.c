/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_cast_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luinasci <luinasci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 19:14:59 by luinasci          #+#    #+#             */
/*   Updated: 2025/06/26 19:15:57 by luinasci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	get_tex_id(t_dda_ctx *ctx, double *dir)
{
	if (ctx->tex_id == 4)
		return (4);
	if (ctx->side == 0)
	{
		if (dir[0] > 0)
			return (3);
		else
			return (2);
	}
	else
	{
		if (dir[1] > 0)
			return (0);
		else
			return (1);
	}
}

void	set_hit_texture_and_wallx(t_game *game, t_ray_hit *hit,
		t_dda_ctx *ctx, double *dir)
{
	double	wall_x;

	hit->tex_id = get_tex_id(ctx, dir);
	if (ctx->side == 0)
		wall_x = game->mlx->pos_y + hit->dist * dir[1];
	else
		wall_x = game->mlx->pos_x + hit->dist * dir[0];
	hit->wall_x = wall_x - floor(wall_x);
}

t_ray_hit	ray_distance(t_game *game, int x)
{
	t_ray_hit	hit;
	double		*dir;
	t_dda_ctx	ctx;

	hit.tex_id = -1;
	dir = ray_direction(game, x);
	if (!dir)
		return ((t_ray_hit){-1, 0, 0, 0, 0, 0});
	hit.dir_x = dir[0];
	hit.dir_y = dir[1];
	init_dda_ctx(game, dir, &ctx);
	ctx.tex_id = -1;
	perform_dda(game, &ctx);
	hit.side = ctx.side;
	if (ctx.side == 0)
		hit.dist = ctx.side_dist_x - ctx.delta_x;
	else
		hit.dist = ctx.side_dist_y - ctx.delta_y;
	set_hit_texture_and_wallx(game, &hit, &ctx, dir);
	free(dir);
	return (hit);
}

int	apply_shade(int color, double distance)
{
	double	shade;
	int		r;
	int		g;
	int		b;

	if (distance < 1.0)
		distance = 1.0;
	shade = 1 / (distance * 0.15 + 1);
	if (shade > 1.0)
		shade = 1.0;
	r = ((color >> 16) & 0xFF) * shade;
	g = ((color >> 8) & 0xFF) * shade;
	b = (color & 0xFF) * shade;
	return ((r << 16) | (g << 8) | b);
}

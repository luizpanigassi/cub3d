/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luinasci <luinasci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 19:11:24 by luinasci          #+#    #+#             */
/*   Updated: 2025/06/26 19:35:00 by luinasci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_vision(t_mlx_data *mlx, int tile_size)
{
	t_vision_line	v;
	t_line			line;

	v.line_length = tile_size * 2;
	v.start_x = (int)(mlx->pos_x * tile_size);
	v.start_y = (int)(mlx->pos_y * tile_size);
	v.end_x = (int)(v.start_x + mlx->dir_x * v.line_length);
	v.end_y = (int)(v.start_y + mlx->dir_y * v.line_length);
	line.start_x = v.start_x;
	line.start_y = v.start_y;
	line.end_x = v.end_x;
	line.end_y = v.end_y;
	line.color = 0x00FF00;
	draw_line_on_minimap(mlx, &line);
}

void	draw_square(t_square_draw_ctx *ctx)
{
	int	dx;
	int	dy;
	int	px;
	int	py;
	int	offset;

	dy = 0;
	while (dy < ctx->tile_size)
	{
		dx = 0;
		while (dx < ctx->tile_size)
		{
			px = ctx->x + dx;
			py = ctx->y + dy;
			if (px >= 0 && px < W && py >= 0 && py < H)
			{
				offset = py * ctx->mlx->line_size + px * (ctx->mlx->bpp / 8);
				*(unsigned int *)(ctx->mlx->img_addr + offset) = ctx->color;
			}
			dx++;
		}
		dy++;
	}
}

void	draw_player(t_mlx_data *mlx, int tile_size)
{
	t_player_draw	p;

	p.center_x = (int)(mlx->pos_x * tile_size);
	p.center_y = (int)(mlx->pos_y * tile_size);
	p.half = tile_size / 4;
	p.y = -p.half;
	while (p.y < p.half)
	{
		p.x = -p.half;
		while (p.x < p.half)
		{
			p.px = p.center_x + p.x;
			p.py = p.center_y + p.y;
			if (p.px >= 0 && p.px < W && p.py >= 0 && p.py < H)
			{
				p.offset = p.py * mlx->line_size + p.px * (mlx->bpp / 8);
				*(unsigned int *)(mlx->img_addr + p.offset) = 0xFF0000;
			}
			p.x++;
		}
		p.y++;
	}
}

void	draw_wall(t_mlx_data *mlx, int x, t_ray_hit hit)
{
	t_wall_draw_ctx	ctx;

	if (hit.dist <= 0)
		hit.dist = 1.0;
	ctx.line_height = (int)(H / hit.dist);
	ctx.draw_start = -ctx.line_height / 2 + H / 2;
	ctx.draw_end = ctx.line_height / 2 + H / 2;
	if (ctx.draw_start < 0)
		ctx.draw_start = 0;
	if (ctx.draw_end >= H)
		ctx.draw_end = H - 1;
	ctx.tex = mlx->textures[hit.tex_id];
	ctx.tex_x = (int)(hit.wall_x * (double)ctx.tex->w);
	if ((hit.side == 0 && hit.dir_x > 0) || (hit.side == 1 && hit.dir_y < 0))
		ctx.tex_x = ctx.tex->w - ctx.tex_x - 1;
	ctx.y = ctx.draw_start;
	draw_wall_column(mlx, x, &ctx, hit.dist);
}

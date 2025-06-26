/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fire.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luinasci <luinasci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 16:06:11 by luinasci          #+#    #+#             */
/*   Updated: 2025/06/26 19:07:39 by luinasci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	spawn_fireball(t_mlx_data *mlx)
{
	int	i;

	i = 0;
	while (i < MAX_FIREBALLS)
	{
		if (!mlx->fireballs[i].active)
		{
			mlx->fireballs[i].x = mlx->pos_x + mlx->dir_x * 1.5;
			mlx->fireballs[i].y = mlx->pos_y + mlx->dir_y * 1.5;
			mlx->fireballs[i].dir_x = mlx->dir_x;
			mlx->fireballs[i].dir_y = mlx->dir_y;
			mlx->fireballs[i].active = 1;
			mlx->fireballs[i].distance = 0;
			mlx->fireballs[i].frame = 0;
			mlx->fireballs[i].frame_count = 0;
			return ;
		}
		i++;
	}
}

void	update_fireballs(t_mlx_data *mlx)
{
	int	i;

	i = 0;
	while (i < MAX_FIREBALLS)
	{
		if (mlx->fireballs[i].active)
		{
			mlx->fireballs[i].x += mlx->fireballs[i].dir_x * FIREBALL_SPEED;
			mlx->fireballs[i].y += mlx->fireballs[i].dir_y * FIREBALL_SPEED;
			mlx->fireballs[i].distance++;
			mlx->fireballs[i].frame_count++;
			if (mlx->fireballs[i].frame_count >= FIREBALL_ANIM_SPEED)
			{
				mlx->fireballs[i].frame_count = 0;
				mlx->fireballs[i].frame = (mlx->fireballs[i].frame + 1)
					% FIREBALL_FRAMES;
			}
			if (!is_walkable(mlx->data, mlx->fireballs[i].x,
					mlx->fireballs[i].y) || mlx->fireballs[i].distance > 80)
				mlx->fireballs[i].active = 0;
		}
		i++;
	}
}

void	draw_fireball_pixels(t_mlx_data *mlx,
	t_img *tex, t_fireball_screen_params *params)
{
	int	y;
	int	x;
	int	tex_y;
	int	tex_x;
	int	color;

	y = params->draw_start_y;
	while (y < params->draw_end_y)
	{
		tex_y = ((y - params->draw_start_y) * tex->h) / params->sprite_height;
		x = params->draw_start_x;
		while (x < params->draw_end_x)
		{
			tex_x = ((x - params->draw_start_x)
					* tex->w) / params->sprite_width;
			color = *(int *)(tex->addr + (tex_y
						* tex->line_len + tex_x * (tex->bpp / 8)));
			if (color != 0x00FFFFFF)
				draw_pixel(mlx, x, y, color);
			x++;
		}
		y++;
	}
}

void	draw_fireball(t_mlx_data *mlx, t_fireball *fire)
{
	t_img						*tex;
	t_fireball_screen_params	params;

	if (!fire->active || !mlx->fire_tex[fire->frame])
		return ;
	if (!compute_fireball_screen_params(mlx, fire, &params))
		return ;
	tex = mlx->fire_tex[fire->frame];
	draw_fireball_pixels(mlx, tex, &params);
}

void	render_fireballs(t_mlx_data *mlx)
{
	int	i;

	i = 0;
	while (i < MAX_FIREBALLS)
	{
		if (mlx->fireballs[i].active)
			draw_fireball(mlx, &mlx->fireballs[i]);
		i++;
	}
}

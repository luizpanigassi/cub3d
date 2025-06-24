/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcologne <jcologne@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 12:23:16 by jcologne          #+#    #+#             */
/*   Updated: 2025/06/24 13:02:09 by jcologne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void draw_pixel(t_mlx_data *mlx, int x, int y, int color)
{
	int offset;

	if (x < 0 || x >= W || y < 0 || y >= H)
		return;
	offset = (y * mlx->line_size) + (x * (mlx->bpp / 8));
	*(int *)(mlx->img_addr + offset) = color;
}

void draw_h_line(t_mlx_data *mlx, int y, int color)
{
	int 	x;

	if (y >= H)
		return;
	x = 0;
	while (x < W)
		draw_pixel(mlx, x++, y, color);
}

void draw_background(t_mlx_data *mlx, int sky, int ground)
{
	int	y;

	y = 0;
	while (y < H)
	{
		if (y < H / 2)
			draw_h_line(mlx, y, sky);
		else
			draw_h_line(mlx, y, ground);
		y++;
	}
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fire.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcologne <jcologne@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 12:54:49 by jcologne          #+#    #+#             */
/*   Updated: 2025/06/26 13:50:36 by jcologne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	spawn_fireball(t_mlx_data *mlx)
{
	for (int i = 0; i < MAX_FIREBALLS; i++) {
		if (!mlx->fireballs[i].active)
		{
			// Start 1.5 units in front of player
			mlx->fireballs[i].x = mlx->pos_x + mlx->dir_x * 1.5;
			mlx->fireballs[i].y = mlx->pos_y + mlx->dir_y * 1.5;   
			// Use player's exact direction
			mlx->fireballs[i].dir_x = mlx->dir_x;
			mlx->fireballs[i].dir_y = mlx->dir_y;
			mlx->fireballs[i].active = 1;
			mlx->fireballs[i].distance = 0;
			mlx->fireballs[i].frame = 0;
			mlx->fireballs[i].frame_count = 0;   
			printf("Spawned fireball %d at (%.2f,%.2f) facing (%.2f,%.2f)\n",
						i, mlx->fireballs[i].x, mlx->fireballs[i].y,
						mlx->dir_x, mlx->dir_y);
			return;
		}
	}
	printf("Max fireballs reached!\n");
}

void update_fireballs(t_mlx_data *mlx)
{
	for (int i = 0; i < MAX_FIREBALLS; i++) {
		if (mlx->fireballs[i].active)
		{
			// Move in world space
			mlx->fireballs[i].x += mlx->fireballs[i].dir_x * FIREBALL_SPEED;
			mlx->fireballs[i].y += mlx->fireballs[i].dir_y * FIREBALL_SPEED;
			mlx->fireballs[i].distance++;   
			// Update animation frame
			mlx->fireballs[i].frame_count++;
			if (mlx->fireballs[i].frame_count >= FIREBALL_ANIM_SPEED)
			{
				mlx->fireballs[i].frame_count = 0;
				mlx->fireballs[i].frame = (mlx->fireballs[i].frame + 1) % FIREBALL_FRAMES;
			}
			printf("Fireball %d at (%.2f,%.2f) dist %d frame %d\n",
				i, mlx->fireballs[i].x, mlx->fireballs[i].y,
				mlx->fireballs[i].distance, mlx->fireballs[i].frame);
			// Collision check
			if (!is_walkable(mlx->data, mlx->fireballs[i].x, mlx->fireballs[i].y) || mlx->fireballs[i].distance > 80)
			{
				mlx->fireballs[i].active = 0;
				printf("Fireball %d deactivated\n", i);
			}
		}
	}
}

void draw_fireball(t_mlx_data *mlx, t_fireball *fire)
{
	if (!fire->active || !mlx->fire_tex[fire->frame]) 
		return;
	// Calculate relative position (no Y inversion)
	double rel_x = fire->x - mlx->pos_x;
	double rel_y = fire->y - mlx->pos_y;
	// Correct camera space transformation
	double inv_det = 1.0 / (mlx->plane_x * mlx->dir_y - mlx->dir_x * mlx->plane_y);
	double transform_x = inv_det * (mlx->dir_y * rel_x - mlx->dir_x * rel_y);
	double transform_y = inv_det * (-mlx->plane_y * rel_x + mlx->plane_x * rel_y);
	printf("Rel pos: (%.2f,%.2f) Transform: (%.2f,%.2f)\n", rel_x, rel_y, transform_x, transform_y);
	if (transform_y <= 0)  // Behind player
		return;
	// Calculate screen position
	int screen_x = (int)((W / 2) * (1 + transform_x / transform_y));
	int sprite_height = abs((int)(H / transform_y));
	int sprite_width = sprite_height;
	// Calculate drawing bounds
	int draw_start_x = screen_x - sprite_width / 2;
	int draw_end_x = screen_x + sprite_width / 2;
	int draw_start_y = (H / 2) - sprite_height / 2;
	int draw_end_y = (H / 2) + sprite_height / 2;
	// Clamp to screen dimensions
	if (draw_start_x < 0) draw_start_x = 0;
	if (draw_end_x >= W) draw_end_x = W - 1;
	if (draw_start_y < 0) draw_start_y = 0;
	if (draw_end_y >= H) draw_end_y = H - 1;
	// Get current texture
	t_img *tex = mlx->fire_tex[fire->frame];
	// Draw the sprite
	int y = draw_start_y;
	while (y < draw_end_y)
	{
		int tex_y = ((y - draw_start_y) * tex->h) / sprite_height;
		int x = draw_start_x;
		while (x < draw_end_x)
		{
			int tex_x = ((x - draw_start_x) * tex->w) / sprite_width;
			int color = *(int *)(tex->addr + (tex_y * tex->line_len + tex_x * (tex->bpp / 8)));
			// Skip white (transparent) pixels
			if (color != 0x00FFFFFF)
				draw_pixel(mlx, x, y, color);
			x++;
		}
	y++;
}

}

void render_fireballs(t_mlx_data *mlx)
{
	for (int i = 0; i < MAX_FIREBALLS; i++)
	{
		if (mlx->fireballs[i].active)
			draw_fireball(mlx, &mlx->fireballs[i]);
	}
}
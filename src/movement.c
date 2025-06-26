/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcologne <jcologne@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 11:20:47 by luinasci          #+#    #+#             */
/*   Updated: 2025/06/26 13:04:08 by jcologne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int key_press(int keycode, t_game *game)
{
	if (keycode == W_KEY)
	{
		game->keys.w = 1;
	}
	else if (keycode == A_KEY)
	{
		game->keys.a = 1;
	}
	else if (keycode == S_KEY)
	{
		game->keys.s = 1;
	}
	else if (keycode == D_KEY)
	{
		game->keys.d = 1;
	}
	else if (keycode == LEFT_KEY)
	{
		game->keys.left = 1;
	}
	else if (keycode == RIGHT_KEY)
	{
		game->keys.right = 1;
	}
	else if (keycode == E_KEY)
	{
		toggle_door(game);
	}
	else if (keycode == ESC_KEY)
	{
		close_event(game);
	}
	else if (keycode == F_KEY)
	{
		spawn_fireball(game->mlx);
	}
	return (0);
}

int key_release(int keycode, t_game *game)
{
	if (keycode == W_KEY)
		game->keys.w = 0;
	else if (keycode == A_KEY)
		game->keys.a = 0;
	else if (keycode == S_KEY)
		game->keys.s = 0;
	else if (keycode == D_KEY)
		game->keys.d = 0;
	else if (keycode == LEFT_KEY)
		game->keys.left = 0;
	else if (keycode == RIGHT_KEY)
		game->keys.right = 0;
	else if (keycode == ESC_KEY)
		game->keys.esc = 0;
	return (0);
}

void rotate_player(t_mlx_data *mlx)
{
	double old_dir_x;
	double old_plane_x;
	double angle;

	old_dir_x = mlx->dir_x;
	old_plane_x = mlx->plane_x;
	angle = 0;
	if (mlx->keys->left)
		angle -= ROTATION_SPEED;
	if (mlx->keys->right)
		angle += ROTATION_SPEED;
	if (angle != 0)
	{
		mlx->dir_x = mlx->dir_x * cos(angle) - mlx->dir_y * sin(angle);
		mlx->dir_y = old_dir_x * sin(angle) + mlx->dir_y * cos(angle);
		mlx->plane_x = mlx->plane_x * cos(angle) - mlx->plane_y * sin(angle);
		mlx->plane_y = old_plane_x * sin(angle) + mlx->plane_y * cos(angle);
	}
}

void calculate_movement(t_mlx_data *mlx, double *move_x, double *move_y)
{
	*move_x = 0;
	*move_y = 0;

	if (mlx->keys->w)
	{
		*move_x += mlx->dir_x * MOVE_SPEED;
		*move_y += mlx->dir_y * MOVE_SPEED;
	}
	if (mlx->keys->s)
	{
		*move_x -= mlx->dir_x * MOVE_SPEED;
		*move_y -= mlx->dir_y * MOVE_SPEED;
	}
	if (mlx->keys->d)
	{
		*move_x += mlx->plane_x * MOVE_SPEED;
		*move_y += mlx->plane_y * MOVE_SPEED;
	}
	if (mlx->keys->a)
	{
		*move_x -= mlx->plane_x * MOVE_SPEED;
		*move_y -= mlx->plane_y * MOVE_SPEED;
	}
}

void update_player_position(t_game *game)
{
	double move_x;
	double move_y;

	calculate_movement(game->mlx, &move_x, &move_y);
	try_movement(game->mlx, move_x, move_y);
	rotate_player(game->mlx);
}

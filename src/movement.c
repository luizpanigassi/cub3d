/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luinasci <luinasci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 11:20:47 by luinasci          #+#    #+#             */
/*   Updated: 2025/06/20 12:33:54 by luinasci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	key_press(int keycode, t_game *game)
{
	if (keycode == W_KEY)
		game->keys.w = 1;
	else if (keycode == A_KEY)
		game->keys.a = 1;
	else if (keycode == S_KEY)
		game->keys.s = 1;
	else if (keycode == D_KEY)
		game->keys.d = 1;
	else if (keycode == LEFT_KEY)
		game->keys.left = 1;
	else if (keycode == RIGHT_KEY)
		game->keys.right = 1;
	else if (keycode == ESC_KEY)
		close_event((t_mlx_data *)game);
	return (0);
}

int	key_release(int keycode, t_game *game)
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

void	update_player_position(t_mlx_data *mlx)
{
	double	dir_x;
	double	dir_y;
	double	plane_x;
	double	plane_y;
	double	old_dir_x;
	double	old_plane_x;

	dir_x = mlx->dir_x;
	dir_y = mlx->dir_y;
	plane_x = mlx->plane_x;
	plane_y = mlx->plane_y;
	if (mlx->keys.w)
		try_movement(mlx, dir_x * MOVE_SPEED, dir_y * MOVE_SPEED);
	if (mlx->keys.s)
		try_movement(mlx, -dir_x * MOVE_SPEED, -dir_y * MOVE_SPEED);
	if (mlx->keys.a)
		try_movement(mlx, -plane_x * MOVE_SPEED, -plane_y * MOVE_SPEED);
	if (mlx->keys.d)
		try_movement(mlx, plane_x * MOVE_SPEED, plane_y * MOVE_SPEED);
	if (mlx->keys.left || mlx->keys.right)
	{
		old_dir_x = mlx->dir_x;
		old_plane_x = mlx->plane_x;
		if (mlx->keys.left)
		{
			mlx->dir_x = mlx->dir_x * cos(-ROTATION_SPEED) - mlx->dir_y * sin(-ROTATION_SPEED);
			mlx->dir_y = old_dir_x * sin(-ROTATION_SPEED) + mlx->dir_y * cos(-ROTATION_SPEED);
			mlx->plane_x = mlx->plane_x * cos(-ROTATION_SPEED) - mlx->plane_y * sin(-ROTATION_SPEED);
			mlx->plane_y = old_plane_x * sin(-ROTATION_SPEED) + mlx->plane_y * cos(-ROTATION_SPEED);
		}
		if (mlx->keys.right)
		{
			mlx->dir_x = mlx->dir_x * cos(ROTATION_SPEED) - mlx->dir_y * sin(ROTATION_SPEED);
			mlx->dir_y = old_dir_x * sin(ROTATION_SPEED) + mlx->dir_y * cos(ROTATION_SPEED);
			mlx->plane_x = mlx->plane_x * cos(ROTATION_SPEED) - mlx->plane_y * sin(ROTATION_SPEED);
			mlx->plane_y = old_plane_x * sin(ROTATION_SPEED) + mlx->plane_y * cos(ROTATION_SPEED);
		}
	}

}

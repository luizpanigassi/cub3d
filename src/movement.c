/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luinasci <luinasci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 11:20:47 by luinasci          #+#    #+#             */
/*   Updated: 2025/06/20 11:55:01 by luinasci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	key_press(int keycode, t_game *game)
{
	if (keycode == W_KEY) // W
		game->keys.w = 1;
	else if (keycode == A_KEY) // A
		game->keys.a = 1;
	else if (keycode == S_KEY) // S
		game->keys.s = 1;
	else if (keycode == D_KEY) // D
		game->keys.d = 1;
	else if (keycode == LEFT_KEY) // Left arrow
		game->keys.left = 1;
	else if (keycode == RIGHT_KEY) // Right arrow
		game->keys.right = 1;
	else if (keycode == ESC_KEY) // ESC
		game->keys.esc = 1;
	return (0);
}

int	key_release(int keycode, t_game *game)
{
	if (keycode == W_KEY) // W
		game->keys.w = 0;
	else if (keycode == A_KEY) // A
		game->keys.a = 0;
	else if (keycode == S_KEY) // S
		game->keys.s = 0;
	else if (keycode == D_KEY) // D
		game->keys.d = 0;
	else if (keycode == LEFT_KEY) // Left arrow
		game->keys.left = 0;
	else if (keycode == RIGHT_KEY) // Right arrow
		game->keys.right = 0;
	else if (keycode == ESC_KEY) // ESC
		game->keys.esc = 0;
	return (0);
}

void	update_player_position(t_game *game)
{
	double move_speed = 0.1;
	double rotation_speed = 0.05;

	if (game->keys.w)
	{
		// Move forward logic
	}
	if (game->keys.s)
	{
		// Move backward logic
	}
	if (game->keys.a)
	{
		// Move left logic
	}
	if (game->keys.d)
	{
		// Move right logic
	}
	if (game->keys.left)
	{
		// Rotate left logic
	}
	if (game->keys.right)
	{
		// Rotate right logic
	}
	if (game->keys.esc)
	{
		exit(0); // Exit the game
	}
}

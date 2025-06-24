/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luinasci <luinasci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 11:45:31 by luinasci          #+#    #+#             */
/*   Updated: 2025/06/24 20:28:56 by luinasci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int close_event(t_game *game)
{
	t_mlx_data *mlx = game->mlx;

	if (mlx->img)
		mlx_destroy_image(mlx->mlx, mlx->img);
	if (mlx->win)
		mlx_destroy_window(mlx->mlx, mlx->win);
	if (mlx->mlx)
	{
		mlx_destroy_display(mlx->mlx);
		free(mlx->mlx);
	}
	free(mlx);
	free_data(game->data);
	free(game);
	exit(0);
	return (0);
}

void events(t_game *game)
{
	mlx_hook(game->mlx->win, 2, 1L << 0, key_press, game);
	mlx_hook(game->mlx->win, 3, 1L << 1, key_release, game);
	mlx_hook(game->mlx->win, 17, 0, close_event, game);
	mlx_hook(game->mlx->win, 6, 1L << 6, mouse_move, game);
}

int mouse_move(int x, int y, t_game *game)
{
	static int last_x = -1;
	int center_x = W / 2;
	int center_y = H / 2;
	double angle;

	if (!game || !game->mlx || !game->mlx->mlx || !game->mlx->win)
		return (0);
	if (x == center_x && y == center_y)
	{
		last_x = center_x;
		return (0);
	}
	if (last_x == -1)
		last_x = x;
	angle = (x - last_x) * 0.002;
	if (angle != 0)
	{
		double old_dir_x = game->mlx->dir_x;
		double old_plane_x = game->mlx->plane_x;

		game->mlx->dir_x = game->mlx->dir_x * cos(angle) - game->mlx->dir_y * sin(angle);
		game->mlx->dir_y = old_dir_x * sin(angle) + game->mlx->dir_y * cos(angle);
		game->mlx->plane_x = game->mlx->plane_x * cos(angle) - game->mlx->plane_y * sin(angle);
		game->mlx->plane_y = old_plane_x * sin(angle) + game->mlx->plane_y * cos(angle);
	}
	last_x = x;
	mlx_mouse_move(game->mlx->mlx, game->mlx->win, center_x, center_y);
	return (0);
}

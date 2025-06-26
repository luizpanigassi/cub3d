/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luinasci <luinasci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 11:45:31 by luinasci          #+#    #+#             */
/*   Updated: 2025/06/26 19:38:03 by luinasci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	rotate_player_view(t_mlx_data *mlx, double angle)
{
	double	old_dir_x;
	double	old_plane_x;

	old_plane_x = mlx->plane_x;
	old_dir_x = mlx->dir_x;
	mlx->dir_x = old_dir_x * cos(angle) - mlx->dir_y * sin(angle);
	mlx->dir_y = old_dir_x * sin(angle) + mlx->dir_y * cos(angle);
	mlx->plane_x = old_plane_x * cos(angle) - mlx->plane_y * sin(angle);
	mlx->plane_y = old_plane_x * sin(angle) + mlx->plane_y * cos(angle);
}

int	close_event(t_game *game)
{
	t_mlx_data	*mlx;

	mlx = game->mlx;
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

void	events(t_game *game)
{
	mlx_hook(game->mlx->win, 2, 1L << 0, key_press, game);
	mlx_hook(game->mlx->win, 3, 1L << 1, key_release, game);
	mlx_hook(game->mlx->win, 17, 0, close_event, game);
	mlx_hook(game->mlx->win, 6, 1L << 6, mouse_move, game);
}

int	mouse_move(int x, int y, t_game *game)
{
	static int	last_x = -1;
	double		angle;
	int			dx;

	if (!game || !game->mlx)
		return (0);
	if (last_x == -1)
	{
		last_x = x;
		return (0);
	}
	dx = x - last_x;
	if (dx != 0)
	{
		angle = dx * 0.01;
		if (angle > 0.1)
			angle = 0.1;
		if (angle < -0.1)
			angle = -0.1;
		rotate_player_view(game->mlx, angle);
	}
	last_x = x;
	return (y);
}

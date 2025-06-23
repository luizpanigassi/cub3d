/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luinasci <luinasci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 11:45:31 by luinasci          #+#    #+#             */
/*   Updated: 2025/06/23 16:49:39 by luinasci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	close_event(t_game *game)
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


void	events(t_game *game)
{
	mlx_hook(game->mlx->win, 2, 1L << 0, key_press, game);
	mlx_hook(game->mlx->win, 3, 1L << 1, key_release, game);
	mlx_hook(game->mlx->win, 17, 0, close_event, game);
}

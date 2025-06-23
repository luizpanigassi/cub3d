/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcologne <jcologne@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 08:10:39 by jcologne          #+#    #+#             */
/*   Updated: 2025/06/23 08:57:51 by jcologne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_window(t_mlx_data *mlx)
{
	mlx->mlx = mlx_init();
	mlx->win = mlx_new_window(mlx->mlx, W, H, "Cub3d");
	mlx->img = mlx_new_image(mlx->mlx, W, H);
	mlx->img_addr = mlx_get_data_addr(mlx->img, &mlx->bpp, &mlx->line_size, &mlx->endian);
}

static void	setup_orientation(t_mlx_data *mlx, char dir)
{
	if (dir == 'N')
	{
		mlx->dir_x = 0;
		mlx->dir_y = -1;
		mlx->plane_x = 0.66;mlx_clear_window
		mlx->plane_y = 0;
	}
	else if (dir == 'S')
	{
		mlx->dir_x = 0;
		mlx->dir_y = 1;
		mlx->plane_x = -0.66;
		mlx->plane_y = 0;
	}
	else if (dir == 'E')
	{
		mlx->dir_x = 1;
		mlx->dir_y = 0;
		mlx->plane_x = 0;
		mlx->plane_y = 0.66;
	}
	else if (dir == 'W')
	{
		mlx->dir_x = -1;
		mlx->dir_y = 0;
		mlx->plane_x = 0;
		mlx->plane_y = -0.66;
	}
}

void	init_player(t_game *game)
{
	game->mlx->pos_x = game->data->player_x + 0.5;
	game->mlx->pos_y = game->data->player_y + 0.5;
	setup_orientation(game->mlx, game->data->player_direction);
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcologne <jcologne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 08:10:39 by jcologne          #+#    #+#             */
/*   Updated: 2025/06/23 13:30:55 by jcologne         ###   ########.fr       */
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
		mlx->plane_x = 0.66;
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

static void init_keys(t_keys *keys)
{
	keys->w = 0;
	keys->a = 0;
	keys->s = 0;
	keys->d = 0;
	keys->left = 0;
	keys->right = 0;
	keys->esc = 0;
}

void	init_player(t_game *game)
{
	t_keys	*keys;

	keys = malloc(sizeof(t_keys));
	init_keys(keys);
	game->mlx->pos_x = game->data->player_x + 0.5;
	game->mlx->pos_y = game->data->player_y + 0.5;
	setup_orientation(game->mlx, game->data->player_direction);
}
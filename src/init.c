/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luinasci <luinasci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 08:10:39 by jcologne          #+#    #+#             */
/*   Updated: 2025/06/26 19:09:21 by luinasci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_window(t_mlx_data *mlx)
{
	mlx->mlx = mlx_init();
	mlx->win = mlx_new_window(mlx->mlx, W, H, "Cub3d");
	mlx->img = mlx_new_image(mlx->mlx, W, H);
	mlx->img_addr = mlx_get_data_addr(mlx->img,
			&mlx->bpp, &mlx->line_size, &mlx->endian);
}

void	set_orientation(t_mlx_data *mlx, t_orientation o)
{
	mlx->dir_x = o.dir_x;
	mlx->dir_y = o.dir_y;
	mlx->plane_x = o.plane_x;
	mlx->plane_y = o.plane_y;
}

void	init_keys(t_keys *keys)
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
	init_keys(&game->keys);
	game->mlx->pos_x = game->data->player_x + 0.5;
	game->mlx->pos_y = game->data->player_y + 0.5;
	setup_orientation(game->mlx, game->data->player_direction);
}

void	init_textures(t_game *game)
{
	t_mlx_data	*mlx;

	mlx = game->mlx;
	mlx->textures[0] = load_xpm(mlx->mlx, game->data->north);
	mlx->textures[1] = load_xpm(mlx->mlx, game->data->south);
	mlx->textures[2] = load_xpm(mlx->mlx, game->data->east);
	mlx->textures[3] = load_xpm(mlx->mlx, game->data->west);
	mlx->textures[4] = load_xpm(mlx->mlx, "textures/door.xpm");
	load_fire_textures(mlx, game->data);
	init_fireballs(mlx);
	if (!mlx->textures[0] || !mlx->textures[1]
		|| !mlx->textures[2] || !mlx->textures[3] || !mlx->textures[4])
	{
		report_texture_errors(game);
	}
}

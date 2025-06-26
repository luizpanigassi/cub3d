/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_window.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luinasci <luinasci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 20:01:19 by jcologne          #+#    #+#             */
/*   Updated: 2025/06/26 19:11:41 by luinasci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	get_step_direction(int start, int end)
{
	if (start < end)
		return (1);
	else
		return (-1);
}

int	abs_int(int n)
{
	if (n < 0)
		return (-n);
	else
		return (n);
}

void	update_line_state(t_line_state *s)
{
	s->e2 = 2 * s->err;
	if (s->e2 > -s->dy)
	{
		s->err -= s->dy;
		s->x += s->sx;
	}
	if (s->e2 < s->dx)
	{
		s->err += s->dx;
		s->y += s->sy;
	}
}

int	game_loop(t_game *game)
{
	update_player_position(game);
	update_fireballs(game->mlx);
	ft_bzero(game->mlx->img_addr, H * game->mlx->line_size);
	draw_background(game->mlx, game->data->ceiling, game->data->floor);
	render_view(game);
	render_fireballs(game->mlx);
	minimap(game->data, game->mlx);
	mlx_put_image_to_window(game->mlx->mlx,
		game->mlx->win, game->mlx->img, 0, 0);
	return (0);
}

void	render_image(t_data *data)
{
	t_mlx_data	*mlx;
	t_game		*game;

	mlx = malloc(sizeof(t_mlx_data));
	game = malloc(sizeof(t_game));
	if (!mlx || !game)
		error_exit("Malloc failed", NULL);
	game->data = data;
	game->mlx = mlx;
	mlx->data = data;
	mlx->keys = &game->keys;
	mlx->mlx = mlx_init();
	if (!mlx->mlx)
		error_exit("MLX init failed", NULL);
	init_window(mlx);
	init_textures(game);
	init_player(game);
	events(game);
	mlx_loop_hook(mlx->mlx, game_loop, game);
	mlx_loop(mlx->mlx);
}

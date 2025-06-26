/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   door.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luinasci <luinasci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 16:30:41 by luinasci          #+#    #+#             */
/*   Updated: 2025/06/26 19:06:30 by luinasci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	is_player_far_from_door(t_game *game, int dx, int dy)
{
	double	px;
	double	py;
	double	margin;

	px = game->mlx->pos_x;
	py = game->mlx->pos_y;
	margin = 0.2;
	return (px > dx + margin || px < dx - margin
		|| py > dy + margin || py < dy - margin);
}

void	toggle_door(t_game *game)
{
	int		dx;
	int		dy;
	t_door	*door;

	dy = (int)(game->mlx->pos_y + game->mlx->dir_y);
	dx = (int)(game->mlx->pos_x + game->mlx->dir_x);
	if (is_door_at(game->data, dx, dy))
	{
		door = get_door(game->data, dx, dy);
		if (door)
		{
			if (door->is_open)
			{
				if (is_player_far_from_door(game, dx, dy))
				{
					door->is_open = 0;
				}
			}
			else
			{
				door->is_open = 1;
			}
		}
	}
}

void	try_toggle_door(t_game *game)
{
	int		tx;
	int		ty;
	t_door	*door;

	tx = (int)(game->mlx->pos_x + game->mlx->dir_x);
	ty = (int)(game->mlx->pos_y + game->mlx->dir_y);
	door = get_door(game->data, tx, ty);
	if (door)
		door->is_open = !door->is_open;
}

void	register_doors(t_data *data)
{
	int	y;
	int	x;

	y = 0;
	data->door_count = 0;
	while (y < data->map_height)
	{
		x = 0;
		while (x < data->map_width)
		{
			if (data->map[y][x] == 'D')
			{
				if (data->door_count < MAX_DOORS)
				{
					data->doors[data->door_count].x = x;
					data->doors[data->door_count].y = y;
					data->doors[data->door_count].is_open = 0;
					data->door_count++;
				}
			}
			x++;
		}
		y++;
	}
}

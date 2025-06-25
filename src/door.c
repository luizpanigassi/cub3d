/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   door.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luinasci <luinasci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 16:30:41 by luinasci          #+#    #+#             */
/*   Updated: 2025/06/25 17:15:30 by luinasci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void toggle_door(t_game *game)
{
	int dx = (int)(game->mlx->pos_x + game->mlx->dir_x);
	int dy = (int)(game->mlx->pos_y + game->mlx->dir_y);

	if (is_door_at(game->data, dx, dy))
	{
		t_door *door = get_door(game->data, dx, dy);
		if (door)
		{
			if (door->is_open)
			{
				double px = game->mlx->pos_x;
				double py = game->mlx->pos_y;
				double margin = 0.2; // adjust as needed
				if (px > dx + margin || px < dx - margin ||
					py > dy + margin || py < dy - margin)
				{
					door->is_open = 0;
				}
				// else: too close, do not close
			}
			else
			{
				door->is_open = 1;
			}
		}
	}
}

t_door *get_door(t_data *data, int x, int y)
{
	int i = 0;

	while (i < data->door_count)
	{
		if (data->doors[i].x == x && data->doors[i].y == y)
			return &data->doors[i];
		i++;
	}
	return NULL;
}

int is_door_open(t_data *data, int x, int y)
{
	t_door *door = get_door(data, x, y);
	return (door && door->is_open);
}

void try_toggle_door(t_game *game)
{
	int tx = (int)(game->mlx->pos_x + game->mlx->dir_x);
	int ty = (int)(game->mlx->pos_y + game->mlx->dir_y);
	t_door *door = get_door(game->data, tx, ty);

	if (door)
		door->is_open = !door->is_open;
}

void register_doors(t_data *data)
{
	int y = 0;
	int x;

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

int is_door_at(t_data *data, int x, int y)
{
	return (data->map[y][x] == 'D');
}

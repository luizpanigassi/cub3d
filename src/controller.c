/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   controller.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luinasci <luinasci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 12:04:21 by luinasci          #+#    #+#             */
/*   Updated: 2025/06/26 15:52:36 by luinasci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	is_walkable(t_data *data, double x, double y)
{
	int	map_x;
	int	map_y;

	map_x = (int)x;
	map_y = (int)y;
	if (map_y < 0 || map_y >= data->map_height
		|| map_x < 0 || map_x >= data->map_width)
		return (0);
	if (data->map[map_y][map_x] == '1')
		return (0);
	if (data->map[map_y][map_x] == 'D' && !is_door_open(data, map_x, map_y))
		return (0);
	return (1);
}

void	try_movement(t_mlx_data *mlx, double dx, double dy)
{
	double	new_x;
	double	new_y;

	new_x = mlx->pos_x + dx;
	new_y = mlx->pos_y + dy;
	if (is_walkable(mlx->data, new_x + COLLISION_MARGIN, mlx->pos_y)
		&& is_walkable(mlx->data, new_x - COLLISION_MARGIN, mlx->pos_y))
		mlx->pos_x = new_x;
	if (is_walkable(mlx->data, mlx->pos_x, new_y + COLLISION_MARGIN)
		&& is_walkable(mlx->data, mlx->pos_x, new_y - COLLISION_MARGIN))
		mlx->pos_y = new_y;
}

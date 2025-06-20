/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   controller.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luinasci <luinasci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 12:04:21 by luinasci          #+#    #+#             */
/*   Updated: 2025/06/20 15:26:57 by luinasci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	is_walkable(t_data *data, double x, double y)
{
	int	map_x;
	int	map_y;

	map_x = (int)x;
	map_y = (int)y;
	if (map_y < 0 || map_y >= data->map_height || map_x < 0
		|| map_x >= data->map_width)
	{
		printf("Blocked: [%d][%d] = '%c'\n", map_y, map_x,
			data->map[map_y][map_x]); //debug
		return (0);
	}
	return (1);
}

void	try_movement(t_mlx_data *mlx, double dx, double dy)
{
	double	new_x;
	double	new_y;

	new_x = mlx->pos_x + dx;
	new_y = mlx->pos_y + dy;
	printf("Trying to move to: (%.2f, %.2f)\n", new_x, new_y); //debug
	if (is_walkable(mlx->data, new_x + COLLISION_MARGIN, mlx->pos_y)
		&& is_walkable(mlx->data, new_x - COLLISION_MARGIN, mlx->pos_y))
		mlx->pos_x = new_x;
	if (is_walkable(mlx->data, mlx->pos_x, new_y + COLLISION_MARGIN)
		&& is_walkable(mlx->data, mlx->pos_x, new_y - COLLISION_MARGIN))
		mlx->pos_y = new_y;
	printf("Moved to: (%.2f, %.2f)\n", mlx->pos_x, mlx->pos_y); //debug
}

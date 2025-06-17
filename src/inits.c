/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inits.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luinasci <luinasci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 19:18:09 by luinasci          #+#    #+#             */
/*   Updated: 2025/06/17 19:18:24 by luinasci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	set_player_position(t_map *map, int x, int y)
{
	map->player_x = x;
	map->player_y = y;
	map->player_direction = map->grid[y][x];
	map->grid[y][x] = '0';
}

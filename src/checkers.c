/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checkers.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luinasci <luinasci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 19:20:07 by luinasci          #+#    #+#             */
/*   Updated: 2025/06/17 19:23:17 by luinasci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	is_wall_or_space(char c)
{
	if (c == '1' || c == ' ')
		return (1);
	return (0);
}

int	is_walkable(char c)
{
	if (c == '0')
		return (1);
	return (0);
}

int	is_player_char(char c)
{
	return (c == 'N' || c == 'S' || c == 'E' || c == 'W');
}

int	is_enclosed(t_map *map, int y, int x)
{
	if (y < 0 || y >= map->height - 1)
		return (0);
	if (x < 0 || x >= (int)ft_strlen(map->grid[y]) - 1)
		return (0);
	if (map->grid[y - 1][x] == ' ' || map->grid[y + 1][x] == ' ')
		return (0);
	if (map->grid[y][x - 1] == ' ' || map->grid[y][x + 1] == ' ')
		return (0);
	return (1);
}

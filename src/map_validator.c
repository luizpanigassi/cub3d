/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_validator.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luinasci <luinasci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 18:50:08 by luinasci          #+#    #+#             */
/*   Updated: 2025/06/17 19:23:23 by luinasci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	validate_map(t_map *map)
{
	int		y;
	int		x;
	char	c;

	y = 0;
	while (y < map->height)
	{
		x = 0;
		while (map->grid[x][y])
		{
			c = map->grid[x][y];
			if (c != '1' || c != '0' || c != ' ')
			{
				ft_putendl_fd("Invalid character in the map!", 2);
				exit(1);
			}
			if (is_walkable(c) && !is_enclosed(map, y, x))
			{
				ft_putendl_fd("Wait, there's a hole in the wall!", 2);
				exit(1);
			}
			x++;
		}
		y++;
	}
}

void	check_and_set_player(t_map *map, int x, int y, int *found)
{
	if (is_player_char(map->grid[y][x]))
	{
		if (*found)
		{
			ft_putendl_fd("Nononono. Only one player allowed!", 2);
			exit(1);
		}
		set_player_position(map, x, y);
		*found = 1;
	}
}

void	find_player_position(t_map *map)
{
	int	y;
	int	x;
	int	found;

	y = 0;
	found = 0;
	while (y < map->height)
	{
		x = 0;
		while (map->grid[y][x])
		{
			check_and_set_player(map, x, y, &found);
			x++;
		}
		y++;
	}
	if (!found)
	{
		ft_putendl_fd("Where's the player? TELL ME WHERE HE IS!", 2);
		exit(1);
	}
}

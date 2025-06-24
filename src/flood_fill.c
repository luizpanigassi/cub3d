/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flood_fill.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luinasci <luinasci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 19:49:42 by luinasci          #+#    #+#             */
/*   Updated: 2025/06/24 17:35:21 by luinasci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	flood_fill(t_data *data, char **map, int x, int y)
{
	if (y < 0 || y >= data->map_height
		|| x < 0 || x >= (int)ft_strlen(map[y]))
	{
		fprintf(stderr, "Flood fill escaped at (%d, %d)\n", x, y);
		error_exit("Map leak: flood escaped the map!", data);
	}
	if (map[y][x] == '1' || map[y][x] == 'F')
		return ;
	if (map[y][x] == ' ')
		error_exit("Map leak: flood hit open space!", data);
	if (!ft_strchr("0NSEW", map[y][x]))
		return ;
	map[y][x] = 'F';
	flood_fill(data, map, x + 1, y);
	flood_fill(data, map, x - 1, y);
	flood_fill(data, map, x, y + 1);
	flood_fill(data, map, x, y - 1);
}

char	**dup_map(t_data *data)
{
	char	**copy;
	int		i;

	copy = ft_calloc(data->map_height + 1, sizeof(char *));
	i = 0;
	if (!copy)
		error_exit("Memory failed during flood fill", data);
	while (i < data->map_height)
	{
		copy[i] = ft_strdup(data->map[i]);
		i++;
	}
	return (copy);
}

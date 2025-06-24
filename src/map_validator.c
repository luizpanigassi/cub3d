/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_validator.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luinasci <luinasci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 18:50:08 by luinasci          #+#    #+#             */
/*   Updated: 2025/06/24 17:35:34 by luinasci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	is_invalid_tile(t_data *data, int x, int y)
{
	if (y < 0 || y >= data->map_height)
		return (1);
	if (x < 0 || x >= (int)ft_strlen(data->map[y]))
		return (1);
	if (data->map[y][x] == ' ')
		return (1);
	return (0);
}

void	validate_map_char_at(t_data *data, int x, int y, int *player_count)
{
	char	c;

	c = data->map[y][x];
	if (!ft_strchr(MAP_CHARS, c))
	{
		fprintf(stderr, "Invalid character '%c' at (%d, %d)\n", c, x, y);
		error_exit("Wait, your map has invalid characters!", data);
	}
	if (ft_strchr(PLAYER_CHARS, c))
	{
		(*player_count)++;
		data->player_x = x;
		data->player_y = y;
		data->player_direction = c;
	}
}

void	validate_map_chars(t_data *data)
{
	int	player_count;
	int	y;
	int	x;

	y = 0;
	player_count = 0;
	while (y < data->map_height)
	{
		x = 0;
		while (x < data->map_width)
		{
			validate_map_char_at(data, x, y, &player_count);
			x++;
		}
		y++;
	}
	if (player_count == 0)
		error_exit("Wait, there's no player in the map!", data);
	else if (player_count != 1)
		error_exit("Wait, there's too many players in the map!", data);
}

void	validate_map_with_flood_fill(t_data *data)
{
	char	**map_copy;

	map_copy = dup_map(data);
	flood_fill(data, map_copy, data->player_x, data->player_y);
	ft_free_array(map_copy);
}

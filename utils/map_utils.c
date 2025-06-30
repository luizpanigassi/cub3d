/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luinasci <luinasci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 17:42:35 by luinasci          #+#    #+#             */
/*   Updated: 2025/06/27 14:51:13 by luinasci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	parse_texture_line(char *trimmed, t_data *data)
{
	if (!ft_strncmp(trimmed, "NO", 2) && ft_isspace(trimmed[2]))
		return (parse_texture(trimmed, data, "NO"));
	else if (!ft_strncmp(trimmed, "SO", 2) && ft_isspace(trimmed[2]))
		return (parse_texture(trimmed, data, "SO"));
	else if (!ft_strncmp(trimmed, "WE", 2) && ft_isspace(trimmed[2]))
		return (parse_texture(trimmed, data, "WE"));
	else if (!ft_strncmp(trimmed, "EA", 2) && ft_isspace(trimmed[2]))
		return (parse_texture(trimmed, data, "EA"));
	return (0);
}

int	handle_non_map_line(char *trimmed,
	t_data *data, t_list **map_lines, int *max_width)
{
	(void)map_lines;
	(void)max_width;
	if (parse_texture_line(trimmed, data))
	{
		free(trimmed);
		return (1);
	}
	else if (parse_color_line(trimmed, data))
	{
		free(trimmed);
		return (1);
	}
	else
	{
		free(trimmed);
		return (2);
	}
}

void	handle_map_line(char *trimmed, t_list **map_lines,
		int *max_width, t_data *data)
{
	if (trimmed[0] == '\0')
		error_exit("Empty line detected inside map definition.", data);
	add_map_line(trimmed, map_lines, max_width);
}

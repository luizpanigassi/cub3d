/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luinasci <luinasci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 18:09:50 by luinasci          #+#    #+#             */
/*   Updated: 2025/06/26 16:38:11 by luinasci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	parse_rgb_component(char *part, int *value)
{
	char	*trimmed;
	int		res;

	trimmed = ft_strtrim(part, " \t\n");
	if (!trimmed || !ft_isdigit_str(trimmed))
	{
		free(trimmed);
		return (0);
	}
	res = ft_atoi(trimmed);
	free(trimmed);
	if (res < 0 || res > 255)
		return (0);
	*value = res;
	return (1);
}

int	parse_rgb(char **parts, int *rgb)
{
	int	i;

	i = 0;
	while (i < 3)
	{
		if (!parse_rgb_component(parts[i], &rgb[i]))
			return (0);
		i++;
	}
	return (1);
}

int	parse_color(char *line, t_data *data, char id)
{
	char	**parts;
	int		rgb[3];
	int		color;

	if ((id == 'F' && data->floor != -1) || (id == 'C' && data->ceiling != -1))
		return (0);
	parts = ft_split(line, ',');
	if (!parts || !parts[0] || !parts[1] || !parts[2] || parts[3])
		return (ft_free_array(parts), 0);
	if (!parse_rgb(parts, rgb))
		return (ft_free_array(parts), 0);
	color = (rgb[0] << 16) | (rgb[1] << 8) | rgb[2];
	if (id == 'F')
		data->floor = color;
	else if (id == 'C')
		data->ceiling = color;
	ft_free_array(parts);
	return (1);
}

int	parse_texture(char *line, t_data *data, const char *id)
{
	char	*path;

	path = ft_strtrim(line + 3, " \t");
	if (!path)
		return (0);
	if (access(path, R_OK))
	{
		fprintf(stderr, "Error: Cannot access texture file: %s\n", path);
		free(path);
		return (0);
	}
	if (!ft_strcmp(id, "NO"))
		data->north = path;
	else if (!ft_strcmp(id, "SO"))
		data->south = path;
	else if (!ft_strcmp(id, "EA"))
		data->east = path;
	else if (!ft_strcmp(id, "WE"))
		data->west = path;
	else
	{
		free(path);
		return (0);
	}
	return (1);
}

int	parse_color_line(char *trimmed, t_data *data)
{
	if (trimmed[0] == 'F' && ft_isspace(trimmed[1]))
	{
		if (!parse_color(trimmed + 2, data, 'F'))
		{
			fprintf(stderr,
				"Error: Invalid floor color format: \"%s\"\n", trimmed + 2);
			error_exit("Invalid floor color!", data);
		}
		return (1);
	}
	else if (trimmed[0] == 'C' && ft_isspace(trimmed[1]))
	{
		if (!parse_color(trimmed + 2, data, 'C'))
			error_exit("Invalid ceiling color!", data);
		return (1);
	}
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_config.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luinasci <luinasci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 18:09:50 by luinasci          #+#    #+#             */
/*   Updated: 2025/06/17 18:30:31 by luinasci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	parse_rgb(char *line, t_rgb *color)
{
	char	**split;
	int		r;
	int		g;
	int		b;

	split = ft_split(line, ',');
	if (!split || !split[0] || !split[1] || !split[2])
	{
		ft_putendl_fd("Error: your RGB is not valid", 2);
		exit(1);
	}
	r = ft_atoi(split[0]);
	g = ft_atoi(split[1]);
	b = ft_atoi(split[2]);
	if (r < 0 || r > 255 || g < 0 || g > 255 || b < 0 || b > 255)
	{
		ft_putendl_fd("Error: your RGB values must be between 0 and 255", 2);
		exit (1);
	}
	color->r = r;
	color->g = g;
	color->b = b;
	ft_free_split(split);
}

void	parse_config_line(char *line, t_config *config)
{
	while (ft_isspace(*line))
		line++;
	if (!ft_strncmp(line, "NO", 3))
		config->texture_north = ft_strdup(ft_strtrim(line + 3, "\t"));
	else if (!ft_strncmp(line, "SO", 3))
		config->texture_south = ft_strdup(ft_strtrim(line + 3, "\t"));
	else if (!ft_strncmp(line, "EA", 3))
		config->texture_east = ft_strdup(ft_strtrim(line + 3, "\t"));
	else if (!ft_strncmp(line, "WE", 3))
		config->texture_west = ft_strdup(ft_strtrim(line + 3, "\t"));
	else if (!ft_strncmp(line, "F", 1))
		parse_rgb(line + 1, &config->color_floor);
	else if (!ft_strncmp(line, "C", 1))
		parse_rgb(line + 1, &config->color_ceiling);
	else
	{
		ft_putendl_fd("Error: Invalid configuration line", 2);
		exit(1);
	}
}

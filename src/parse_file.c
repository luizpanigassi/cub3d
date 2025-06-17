/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luinasci <luinasci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 17:29:26 by luinasci          #+#    #+#             */
/*   Updated: 2025/06/17 18:49:07 by luinasci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	is_map_line(char *line)
{
	while (*line)
	{
		if (*line == '1' || *line == '0' || *line == 'N'
			||*line == 'S' || *line == 'E' || *line == 'W' || *line == ' ')
			return (1);
		line++;
	}
	return (0);
}

void	read_cub_lines(int fd, t_game *game, t_list **map_lines)
{
	char	*line;
	int		map_started;

	map_started = 0;
	line = get_next_line(fd);
	while (line != NULL)
	{
		if (isempty(line))
		{
			free(line);
			line = get_next_line(fd);
			continue ;
		}
		if (!map_started && is_map_line(line))
			map_started = 1;
		if (map_started)
			ft_lstadd_back(map_lines, ft_listnew(ft_strdup(line)));
		else
			parse_config_line(line, &game->config);
		free(line);
		line = get_next_line(fd);
	}
}

void	parse_cub_file(const char *filename, t_game *game)
{
	int		fd;
	t_list	*map_lines;

	map_lines = NULL;
	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (perror("Error opening file"));
	read_cub_lines(fd, game, &map_lines);
	close(fd);
	build_map_from_list(map_lines, &game->map);
	ft_lstclear(&map_lines, free);
}

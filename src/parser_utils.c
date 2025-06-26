/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luinasci <luinasci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 19:12:25 by luinasci          #+#    #+#             */
/*   Updated: 2025/06/26 19:13:00 by luinasci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	advance_line(char **line, int *line_num, int fd)
{
	*line = get_next_line(fd);
	(*line_num)++;
}

void	trim_newline_inplace(char *line)
{
	char	*nl;

	nl = strchr(line, '\n');
	if (nl)
		*nl = '\0';
}

int	process_non_map_line(char *line, int line_num, t_parse_ctx *ctx)
{
	char	*trimmed;
	int		result;

	trimmed = trim_and_free_line(ft_strdup(line));
	result = handle_non_map_line_block(line, trimmed, line_num, ctx);
	return (result);
}

int	process_line(char **line, int *line_num, int fd, t_parse_ctx *ctx)
{
	trim_newline_inplace(*line);
	if (*(ctx->map_started))
	{
		if (!handle_map_line_block(*line, ctx->map_lines,
				ctx->max_width, ctx->data))
		{
			advance_line(line, line_num, fd);
			return (1);
		}
	}
	else
	{
		if (!process_non_map_line(*line, *line_num, ctx))
		{
			advance_line(line, line_num, fd);
			return (1);
		}
	}
	advance_line(line, line_num, fd);
	return (1);
}

int	handle_map_line_block(char *line, t_list **map_lines,
		int *max_width, t_data *data)
{
	char	*trimmed;

	trimmed = trim_and_free_line(ft_strdup(line));
	if (!trimmed || trimmed[0] == '\0')
	{
		free(trimmed);
		free(line);
		return (0);
	}
	handle_map_line(line, map_lines, max_width, data);
	free(trimmed);
	return (1);
}

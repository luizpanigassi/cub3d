/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luinasci <luinasci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 17:24:06 by luinasci          #+#    #+#             */
/*   Updated: 2025/06/19 18:09:25 by luinasci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	len1;
	size_t	len2;
	size_t	i;
	size_t	j;
	char	*new_str;

	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	i = 0;
	j = 0;
	new_str = (char *)malloc(len1 + len2 + 1);
	if (new_str == NULL)
		return (NULL);
	while (i < len1)
	{
		new_str[i] = s1[i];
		i++;
	}
	while (j < len2)
	{
		new_str[i + j] = s2[j];
		j++;
	}
	new_str[len1 + len2] = '\0';
	return (new_str);
}

int	initialize_buffer(int fd, char **receiver_buffer)
{
	if (fd < 0 || BUFFER_SIZE <= 0)
	{
		free(*receiver_buffer);
		*receiver_buffer = NULL;
		return (0);
	}
	if (!*receiver_buffer)
		*receiver_buffer = ft_calloc(1, sizeof(char));
	return (1);
}

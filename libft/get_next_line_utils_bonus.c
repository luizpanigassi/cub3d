/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luinasci <luinasci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 17:24:06 by luinasci          #+#    #+#             */
/*   Updated: 2024/11/20 15:41:06 by luinasci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*ft_strchr(const char *s, int c)
{
	char	ch;

	ch = (char)c;
	while (*s)
	{
		if (*s == ch)
			return ((char *)s);
		s++;
	}
	if (ch == '\0')
		return ((char *)s);
	return (((void *)0));
}

void	*ft_calloc(size_t number, size_t size)
{
	size_t	total_size;
	size_t	i;
	void	*ptr;

	total_size = number * size;
	i = 0;
	ptr = malloc(total_size);
	if (!ptr)
	{
		return (NULL);
	}
	while (i < total_size)
	{
		((unsigned char *)ptr)[i] = 0;
		i++;
	}
	return (ptr);
}

int	ft_strlen(const char *str)
{
	int	length;

	length = 0;
	while (str[length] != '\0')
	{
		length++;
	}
	return (length);
}

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

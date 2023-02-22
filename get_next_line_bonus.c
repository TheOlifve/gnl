/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrahovha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/07 16:19:01 by hrahovha          #+#    #+#             */
/*   Updated: 2023/02/22 14:43:11 by hrahovha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*ft_b_endl(char *str)
{
	int		i;
	char	*s;

	i = 0;
	while (str && str[i] && str[i] != '\n')
		i++;
	s = ft_substr(str, 0, i + 1);
	return (s);
}

char	*ft_a_endl(char *str)
{
	int		i;
	char	*s;

	i = 0;
	while (str && str[i] && str[i] != '\n')
		i++;
	s = ft_substr(str, i + 1, ft_strlen(str) - i);
	free(str);
	str = ft_strdup(s);
	free(s);
	s = NULL;
	return (str);
}

static char	*ft_str(int fd, char *str, int i, char *temp)
{
	char	*buff;

	if (ft_strchr(str, '\n'))
		return (str);
	buff = (char *) malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buff)
		return (NULL);
	i = read(fd, buff, BUFFER_SIZE);
	while (i > 0)
	{
		buff[i] = '\0';
		if (!str)
			str = ft_strdup("");
		temp = ft_strdup(str);
		free(str);
		str = ft_strjoin(temp, buff);
		free(temp);
		temp = NULL;
		if (ft_strchr(str, '\n'))
			break ;
		i = read(fd, buff, BUFFER_SIZE);
	}
	free(buff);
	buff = NULL;
	return (str);
}

char	*get_next_line(int fd)
{	
	char		*s;
	char		*temp;
	static char	*str[OPEN_MAX];

	temp = NULL;
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	str[fd] = ft_str(fd, str[fd], 0, temp);
	s = ft_b_endl(str[fd]);
	if (!str[fd])
		return (NULL);
	str[fd] = ft_a_endl(str[fd]);
	if (*s == 0)
	{
		free(str[fd]);
		str[fd] = NULL;
		free(s);
		s = NULL;
		return (NULL);
	}
	return (s);
}

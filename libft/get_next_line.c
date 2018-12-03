/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okryzhan <okryzhan@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/03 15:56:11 by okryzhan          #+#    #+#             */
/*   Updated: 2018/11/03 15:56:13 by okryzhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static t_gnl	*ft_new_fd(int fd, t_gnl *next)
{
	t_gnl	*tmp;

	tmp = (t_gnl *)malloc(sizeof(t_gnl));
	tmp->str = NULL;
	tmp->fd = fd;
	tmp->next = next;
	return (tmp);
}

static char		*ft_update_str(int path, char *st_buff, char *buff, size_t len)
{
	char *tmp;

	tmp = st_buff;
	if (path == 1)
		st_buff = ft_strjoin(st_buff, buff);
	else if (path == 2)
		st_buff = ft_strdup(&st_buff[len + 1]);
	free(tmp);
	return (st_buff);
}

static int		ft_return_line(int ret, t_gnl *elem, char **line)
{
	size_t	len;

	len = 0;
	if (ret < 0)
		return (-1);
	if (ret == 0 && elem->str == NULL)
		return (0);
	while (elem->str[len] != '\n' && elem->str[len] != '\0')
		len++;
	if (elem->str[len] == '\n')
	{
		*line = len ? ft_strsub(elem->str, 0, len) : ft_strnew(0);
		elem->str = ft_update_str(2, elem->str, NULL, len);
		if (elem->str[0] == '\0')
			ft_strdel(&elem->str);
	}
	else
	{
		*line = len ? ft_strsub(elem->str, 0, len) : ft_strnew(0);
		ft_strdel(&elem->str);
		if (**line && ret == 0)
			return (0);
	}
	return (1);
}

int				get_next_line(const int fd, char **line)
{
	static t_gnl	*list;
	t_gnl			*elem;
	char			buff[BUFF_SIZE + 1];
	int				ret;

	if (fd < 0 || line == NULL)
		return (-1);
	elem = list;
	while (elem && elem->fd != fd)
		elem = elem->next;
	if (elem == NULL)
	{
		elem = ft_new_fd(fd, list);
		list = elem;
	}
	while ((ret = read(fd, buff, BUFF_SIZE)) > 0)
	{
		buff[ret] = '\0';
		elem->str = elem->str ? elem->str : ft_strnew(0);
		elem->str = ft_update_str(1, elem->str, buff, 0);
		if (ft_strrchr(buff, '\n'))
			break ;
	}
	return (ft_return_line(ret, elem, line));
}

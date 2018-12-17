/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okryzhan <okryzhan@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/04 17:27:51 by okryzhan          #+#    #+#             */
/*   Updated: 2018/12/04 17:27:51 by okryzhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int		skip_comments(char **line)
{
	while (*line && **line == '#')
	{
		if (ft_strnequ(*line, "##", 2))
			break ;
		add_to_tab(*line);
		get_next_line(0, line);
	}
	if (!*line || !**line)
		return (0);
	return (1);
}

int		get_command(char **line)
{
	int ret;

	ret = 0;
	if (!skip_comments(line))
		return (-1);
	if (**line == '#')
	{
		if (!ft_strcmp(*line, "##start"))
			ret = 1;
		if (!ft_strcmp(*line, "##end"))
			ret = 2;
		if (!ft_strcmp(*line, "##dead"))
			ret = 3;
		if (!ft_strcmp(*line, "##locked"))
			ret = 4;
		add_to_tab(*line);
		get_next_line(0, line);
	}
	if (!*line || (**line == '#' && ret != 0))
		exit_func(0, "Bad commands");
	if (**line == 'L' || **line == '#')
		exit_func(0, "Rooms name begins with 'L' or '#'");
	return (ret);
}

void	get_ants(void)
{
	char	*line;

	get_next_line(0, &line);
	if (!line)
		exit_func(0, "Empty file");
	if (get_command(&line) == -1)
		exit_func(0, "No ants");
	g_ants = ft_atoi(line);
	add_to_tab(line);
	if (g_ants <= 0)
		exit_func(0, "Wrong number of ants");
}

void	set_tubes(t_room *room, char *line)
{
	char	*ch;

	skip_comments(&line);
	if (!ft_match(line, "*-*"))
		exit_func(0, "Bad connection input");
	ch = ft_strchr(line, '-');
	add_connection(room, ft_strsub(line, 0, ch - line),
		ft_strsub((ch + 1), 0, ft_strlen((ch + 1))));
	add_to_tab(line);
	while (get_next_line(0, &line))
	{
		if (get_command(&line) == -1)
			return ;
		if (!ft_match(line, "*-*"))
		{
			add_to_tab(line);
			exit_func(0, "Bad connection input");
		}
		ch = ft_strchr(line, '-');
		add_connection(room, ft_strsub(line, 0, ch - line),
			ft_strsub((ch + 1), 0, ft_strlen((ch + 1))));
		add_to_tab(line);
	}
}

t_room	**get_rooms(void)
{
	t_room	*rooms;
	char	*line;
	int		role;

	rooms = NULL;
	g_src = -1;
	g_dst = -1;
	while (get_next_line(0, &line))
	{
		if ((role = get_command(&line)) == -1)
			exit_func(0, "Bad");
		if (!ft_match(line, "* * *"))
		{
			set_tubes(rooms, line);
			break ;
		}
		rooms = add_room(rooms, line, role);
		add_to_tab(line);
	}
	if (g_src == -1 || g_dst == -1)
		exit_func(0, "No start or end");
	return (lst_to_array(rooms));
}

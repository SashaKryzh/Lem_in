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
	if (!*line)
		return (0);
	return (1);
}

void	get_ants(void)
{
	char	*line;

	get_next_line(0, &line);
	if (!line)
		exit_func(NULL, "Empty file");
	if (!skip_comments(&line))
		return ;
	g_ants = ft_atoi(line);
	add_to_tab(line);
	if (g_ants <= 0)
		exit_func(NULL, "Wrong number of ants");
}

int		get_rooms_role(t_room *rooms, char **line)
{
	int ret;

	ret = 0;
	if (!skip_comments(line))
		return (-1);
	if (**line == '#' && ret == 0)
	{
		if (!ft_strcmp(*line, "##start"))
			ret = 1;
		if (!ft_strcmp(*line, "##end"))
			ret = 2;
		add_to_tab(*line);
		get_next_line(0, line);
	}
	if (!*line || (**line == '#' && ret == 0))
		exit_func(rooms, "Bad commands");
	if (**line == 'L')
		exit_func(rooms, "Rooms name begin with 'L'");
	return (ret);
}

void	set_tubes(t_room *room, char *line)
{
	char	*ch;

	skip_comments(&line);
	if (!ft_match(line, "*-*"))
		exit_func(room, "Bad connection input");
	ch = ft_strchr(line, '-');
	add_connection(room, ft_strsub(line, 0, ch - line),
		ft_strsub((ch + 1), 0, ft_strlen((ch + 1))));
	add_to_tab(line);
	while (get_next_line(0, &line))
	{
		if (get_rooms_role(NULL, &line) == -1)
			return ;
		if (!ft_match(line, "*-*"))
		{
			add_to_tab(line);
			exit_func(room, "Bad connection input");
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
	while (get_next_line(0, &line))
	{
		if ((role = get_rooms_role(rooms, &line)) == -1)
			exit_func(NULL, "Bad");
		if (!ft_match(line, "* * *"))
		{
			set_tubes(rooms, line);
			break ;
		}
		rooms = add_room(rooms,
			ft_strsub(line, 0, ft_strchr(line, ' ') - line), role);
		add_to_tab(line);
	}
	return (lst_to_array(rooms));
}

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

void	get_ants(void)
{
	char	*line;

	if (get_next_line(0, &line))
	{
		g_ants = ft_atoi(line);
		free(line);
	}
	if (g_ants <= 0)
	{
		ft_printf("Wrong number of ants: %d\n", g_ants);
		exit(0);
	}
}

int		get_rooms_role(t_room *rooms, char **line)
{
	int ret;

	ret = 0;
	if (**line == '#')
	{
		if (!ft_strcmp(*line, "##start"))
			ret = 1;
		if (!ft_strcmp(*line, "##end"))
			ret = 2;
		free(*line);
		get_next_line(0, line);
	}
	if (**line == 'L')
		exit_func(rooms, "Rooms name begin with 'L'");
	return (ret);
}

void	set_tubes(t_room *room, char *line)
{
	char	*ch;

	if (!ft_match(line, "*-*"))
	{
		free(line);
		exit_func(room, "Bad connection input");
	}
	ch = ft_strchr(line, '-');
	add_connection(room, ft_strsub(line, 0, ch - line),
		ft_strsub((ch + 1), 0, ft_strlen((ch + 1))));
	free(line);
	while (get_next_line(0, &line))
	{
		get_rooms_role(room, &line);
		if (!ft_match(line, "*-*"))
		{
			free(line);
			exit_func(room, "Bad connection input");
		}
		ch = ft_strchr(line, '-');
		add_connection(room, ft_strsub(line, 0, ch - line),
			ft_strsub((ch + 1), 0, ft_strlen((ch + 1))));
		free(line);
	}
}

t_room	*get_rooms(void)
{
	t_room	*room;
	char	*line;
	int		role;

	room = NULL;
	while (get_next_line(0, &line))
	{
		role = get_rooms_role(room, &line);
		if (!ft_match(line, "* * *"))
		{
			set_tubes(room, line);
			break ;
		}
		room = add_room(room,
			ft_strsub(line, 0, ft_strchr(line, ' ') - line), role);
		free(line);
	}
	return (room);
}

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

int		get_ants(void)
{
	char	*line;
	int		ret;

	get_next_line(0, &line);
	ret = ft_atoi(line);
	free(line);
	if (ret <= 0)
		exit_func(0, "Error on input");
	return (ret);
}

int		get_rooms_role(char **line)
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
		exit_func(0, "Error on input");
	return (ret);
}

void	set_tubes(t_room *room, char *line)
{
	char **data;

	data = ft_strsplit(line, '-');
	free(line);
	add_connection(room, data[0], data[1]);
	while (get_next_line(0, &line))
	{
		get_rooms_role(&line);
		data = ft_strsplit(line, '-');
		free(line);
		add_connection(room, data[0], data[1]);
	}
}

t_room	*get_rooms(void)
{
	t_room	*room;
	char	*line;
	char	**data;
	int		role;

	room = NULL;
	while (get_next_line(0, &line))
	{
		role = get_rooms_role(&line);
		if (char_tab_len((data = ft_strsplit(line, ' '))) != 3)
		{
			set_tubes(room, line);
			break ;
		}
		room = add_room(room, data[0], role);
	}
	return (room);
}

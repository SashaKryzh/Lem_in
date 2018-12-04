/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okryzhan <okryzhan@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/03 12:12:22 by okryzhan          #+#    #+#             */
/*   Updated: 2018/12/03 12:12:22 by okryzhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	exit_func(int type, char *msg)
{
	ft_printf("%s\n", msg);
	exit(type);
}

int		get_ants(void)
{
	char	*line;
	int		ret;

	get_next_line(0, &line);
	ret = ft_atoi(line);
	free(line);
	if (ret < 0)
		exit_func(0, "Error on input");
	return (ret);
}

int		get_room_role(char **line)
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

void	get_rooms(void)
{
	char	*line;
	char	**data;
	t_room	*room;

	room = (t_room *)malloc(sizeof(t_room));
	get_next_line(0, &line);
	room->role = get_room_role(&line);
	data = ft_strsplit(line, ' ');
	room->name = ft_strdup(data[0]);
	print_room_info(*room);
}

t_room	*create_room(char *name, int role)
{
	t_room *new;

	new = (t_room *)malloc(sizeof(t_room));
	ft_bzero(new, sizeof(t_room));
	new->name = ft_strdup(name);
	new->role = role;
	return (new);
}

t_room	*add_room(t_room *start, char *name, int role)
{
	t_room	*new;

	new = create_room(name, role);
	new->next = start;
	start = new;
	return (start);
}

int		main(void)
{
	t_room	*room;

	room = test_init();
	while (room)
	{
		ft_printf("%s %d, path to: %s\n", room->name, room->role, NULL);
		room = room->next;
	}
	return (0);
}

// int		main(void)
// {
// 	t_map	map;
// 	char *line;

// 	map.ants = get_ants();
// 	get_rooms();

// 	line = NULL;
// 	// while (get_next_line(0, &line))
// 	// {
// 	// 	ft_printf("%s\n", line);
// 	// 	free(line);
// 	// }
// 	return (0);
// }

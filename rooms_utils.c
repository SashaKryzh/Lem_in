/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rooms_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okryzhan <okryzhan@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/04 16:31:32 by okryzhan          #+#    #+#             */
/*   Updated: 2018/12/04 16:31:32 by okryzhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

t_room	*create_room(char *line, int role)
{
	t_room *new;

	new = (t_room *)malloc(sizeof(t_room));
	ft_bzero(new, sizeof(t_room));
	new->name = ft_strsub(line, 0, ft_strchr(line, ' ') - line);
	new->x = ft_atoi(ft_strchr(line, ' ') + 1);
	new->y = ft_atoi(ft_strrchr(line, ' ') + 1);
	if (new->x < 0 || new->y < 0)
		exit_func(0, "Negative cordinates");
	new->role = role;
	if (role == start)
		g_src = g_cnt_rooms;
	if (role == end)
		g_dst = g_cnt_rooms;
	new->index = g_cnt_rooms;
	g_cnt_rooms += 1;
	return (new);
}

int		room_cmp(t_room *room, t_room *new)
{
	if (ft_strequ(room->name, new->name))
		return (0);
	if (room->x == new->x && room->y == new->y)
		return (0);
	if (room->role == start && new->role == start)
		return (0);
	if (room->role == end && new->role == end)
		return (0);
	return (1);
}

t_room	*add_room(t_room *start, char *line, int role)
{
	t_room	*tmp;
	t_room	*new;

	new = create_room(line, role);
	if (!start)
		start = new;
	else
	{
		tmp = start;
		while (1)
		{
			if (!room_cmp(tmp, new))
				exit_func(0, "Rooms info dublicates");
			if (!tmp->next)
				break ;
			tmp = tmp->next;
		}
		tmp->next = new;
	}
	return (start);
}

int		is_double_connection(t_room *r_from, t_room *r_to)
{
	t_tube	*tmp;

	tmp = r_from->tubes;
	while (tmp)
	{
		if (tmp->path == r_to)
			return (1);
		tmp = tmp->next;
	}
	return (0);
}

void	add_connection(t_room *room, char *from, char *to)
{
	t_room	*r_from;
	t_room	*r_to;
	t_tube	*con1;
	t_tube	*con2;

	if (ft_strequ(from, to))
		exit_func(0, "Same rooms in connection");
	r_from = find_room_name(room, from);
	r_to = find_room_name(room, to);
	if (!r_from || !r_to)
		exit_func(0, "No rooms in connection");
	if (is_double_connection(r_from, r_to))
		exit_func(0, "Double connection");
	con1 = (t_tube *)malloc(sizeof(t_tube));
	con2 = (t_tube *)malloc(sizeof(t_tube));
	con1->path = r_to;
	con2->path = r_from;
	con1->next = r_from->tubes;
	con2->next = r_to->tubes;
	r_from->tubes = con1;
	r_to->tubes = con2;
	free(from);
	free(to);
}

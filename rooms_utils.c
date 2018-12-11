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

t_room	*create_room(char *name, int role)
{
	t_room *new;

	new = (t_room *)malloc(sizeof(t_room));
	ft_bzero(new, sizeof(t_room));
	new->name = name;
	new->role = role;
	if (role == start)
		g_src = g_cnt_rooms;
	if (role == end)
		g_dst = g_cnt_rooms;
	new->index = g_cnt_rooms;
	g_cnt_rooms += 1;
	return (new);
}

t_room	*add_room(t_room *start, char *name, int role)
{
	t_room	*tmp;
	t_room	*new;

	new = create_room(name, role);
	if (!start)
		start = new;
	else
	{
		tmp = start;
		while (tmp->next)
		{
			if (ft_strequ(tmp->name, name)
				|| (tmp->role == role && role != none))
				exit_func(start, "Rooms info dublicates");
			tmp = tmp->next;
		}
		if (ft_strequ(tmp->name, name)
			|| (tmp->role == role && role != none))
			exit_func(start, "Rooms info dublicates");
		tmp->next = new;
	}
	return (start);
}

void	add_connection(t_room *room, char *from, char *to)
{
	t_room	*r_from;
	t_room	*r_to;
	t_tube	*con1;
	t_tube	*con2;

	if (ft_strequ(from, to))
		exit_func(room, "Same rooms in connection");
	r_from = find_room_name(room, from);
	r_to = find_room_name(room, to);
	if (!r_from || !r_to)
		exit_func(room, "No rooms in connection");
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

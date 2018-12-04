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

t_room	*find_room(t_room *room, char *name)
{
	while (room)
	{
		if (!ft_strcmp(room->name, name))
			break ;
		room = room->next;
	}
	return (room);
}

t_room	*find_room_role(t_room *room, int role)
{
	while (room)
	{
		if (room->role == role)
			break ;
		room = room->next;
	}
	return (room);
}

void	add_connection(t_room *room, char *from, char *to)
{
	t_room	*r_from;
	t_tube	*tube;

	if (!ft_strcmp(from, to))
		exit_func(0, "Error on input");
	if (!(r_from = find_room(room, from)))
		exit_func(0, "Error on input");
	tube = (t_tube *)malloc(sizeof(t_tube));
	if (!(tube->path = find_room(room, to)))
		exit_func(0, "Error on input");
	tube->next = r_from->tubes;
	r_from->tubes = tube;
}

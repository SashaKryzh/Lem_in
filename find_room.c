/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_room.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okryzhan <okryzhan@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/05 11:33:24 by okryzhan          #+#    #+#             */
/*   Updated: 2018/12/05 11:33:24 by okryzhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

t_room	*find_room_name(t_room *rooms, char *name)
{
	while (rooms)
	{
		if (!ft_strcmp(rooms->name, name))
			break ;
		rooms = rooms->next;
	}
	return (rooms);
}

t_room	*find_room_role(t_room *rooms, int role)
{
	while (rooms)
	{
		if (rooms->role == role)
			break ;
		rooms = rooms->next;
	}
	return (rooms);
}

t_room	*find_room_index(t_room *rooms, int index)
{
	while (rooms)
	{
		if (rooms->index == index)
			break ;
		rooms = rooms->next;
	}
	return (rooms);
}

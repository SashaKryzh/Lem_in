/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okryzhan <okryzhan@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/04 16:49:20 by okryzhan          #+#    #+#             */
/*   Updated: 2018/12/04 16:49:20 by okryzhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int			char_tab_len(char **tab)
{
	int count;

	count = 0;
	while (tab[count])
		count++;
	return (count);
}

t_room		**lst_to_array(t_room *lst)
{
	t_room	**rooms;
	int		i;

	rooms = (t_room **)malloc(sizeof(t_room *) * count_rooms(lst) + 1);
	i = 0;
	while (lst)
	{
		rooms[i] = lst;
		lst = lst->next;
		i++;
	}
	rooms[i] = 0;
	return (rooms);
}

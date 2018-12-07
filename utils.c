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


void	swap_nodes_info(t_path *n1, t_path *n2)
{
	int *tmp_p;
	int tmp_src;
	int tmp_len;

	tmp_p = n1->p;
	tmp_src = n1->src;
	tmp_len = n1->len;
	n1->p = n2->p;
	n1->src = n2->src;
	n1->len = n2->len;
	n2->p = tmp_p;
	n2->src = tmp_src;
	n2->len = tmp_len;
}

void	lst_sort(t_path *routs)
{
	t_path	*tmp;
	int		changed;

	if (routs == NULL)
		return ;
	changed = 1;
	while (changed)
	{
		tmp = routs;
		changed = 0;
		while (tmp->next)
		{
			if (tmp->len > tmp->next->len)
			{
				swap_nodes_info(tmp, tmp->next);
				changed = 1;
			}
			tmp = tmp->next;
		}
	}
}

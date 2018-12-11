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

t_room		**lst_to_array(t_room *lst)
{
	t_room	**rooms;
	int		i;

	if (!lst)
		exit_func(NULL, "No data");
	rooms = (t_room **)malloc(sizeof(t_room *) * (g_cnt_rooms + 1));
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

void		convert_routs(t_room **rooms, t_route *routs)
{
	int i;
	int v;

	while (routs)
	{
		routs->route = (t_room **)malloc(sizeof(t_room *) * (routs->len + 2));
		i = routs->len + 1;
		routs->route[i--] = NULL;
		v = g_dst;
		while (i > 0)
		{
			routs->route[i] = rooms[v];
			v = routs->p[v];
			i--;
		}
		routs->route[i] = rooms[g_src];
		routs = routs->next;
	}
}

void	swap_nodes_info(t_route *n1, t_route *n2)
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

void	lst_sort(t_route *routs)
{
	t_route	*tmp;
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

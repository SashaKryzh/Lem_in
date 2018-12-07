/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_routs.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okryzhan <okryzhan@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/07 08:49:49 by okryzhan          #+#    #+#             */
/*   Updated: 2018/12/07 08:49:49 by okryzhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	mark_rout(t_room *rooms, int *p, int src, int dst)
{
	int v;

	v = p[dst];
	while (v != src)
	{
		find_room_index(rooms, v)->used = 1;
		v = p[v];
	}
}

void	unmark_rout(t_room *rooms)
{
	while (rooms)
	{
		rooms->used = 0;
		rooms = rooms->next;
	}
}

t_path	*add_rout(t_path *routs, int *p, int len, int src)
{
	t_path	*tmp;
	t_path	*new;

	new = (t_path *)malloc(sizeof(t_path));
	new->p = p;
	new->src = src;
	new->len = len;
	new->next = NULL;
	if (!routs)
		routs = new;
	else
	{
		tmp = routs;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
	}
	return (routs);
}

t_path	*find_routs(t_room **rooms, int src, int dst)
{
	t_path	*routs;
	t_tube	*tubes;
	int		*p;
	int		*d;

	routs = NULL;
	tubes = rooms[src]->tubes;
	int i = 0;
	while (tubes)
	{
		rooms[src]->used = 1;
		while (1)
		{
			d = dijkstra(rooms, tubes->path->index, &p);
			p[dst] = tubes->path->index == dst ? src : p[dst];
			if (p[dst] == -1)
			{
				free(p);
				free(d);
				break ;
			}
			mark_rout(*rooms, p, tubes->path->index, dst);
			routs = add_rout(routs, p, d[dst] + 1, tubes->path->index);
			free(d);
			if (rooms[p[dst]] == tubes->path || tubes->path->index == dst)
				break ;
			i++;
		}
		unmark_rout(*rooms);
		tubes = tubes->next;
	}
	lst_sort(routs);
	return (routs);
}

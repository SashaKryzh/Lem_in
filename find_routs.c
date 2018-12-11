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

t_route	*add_rout(t_route *routs, int *p, int len, int src)
{
	t_route	*tmp;
	t_route	*new;

	new = (t_route *)malloc(sizeof(t_route));
	new->p = p;
	new->src = src;
	new->len = len;
	new->selected = 0;
	new->best_rout = 0;
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

t_route	*find_routs(t_room **rooms, int src, int dst)
{
	t_route	*routs;
	t_tube	*tubes;
	int		*p;
	int		dist;

	routs = NULL;
	tubes = rooms[src]->tubes;
	while (tubes)
	{
		rooms[src]->used = 1;
		while (1)
		{
			dijkstra(rooms, tubes->path->index, &p, &dist);
			p[dst] = tubes->path->index == dst ? src : p[dst];
			if (p[dst] == -1)
			{
				free(p);
				break ;
			}
			mark_rout(rooms, p, tubes->path->index, dst);
			routs = add_rout(routs, p, dist + 1, tubes->path->index);
			if (rooms[p[dst]] == tubes->path || tubes->path->index == dst)
				break ;
		}
		unmark_routs(*rooms);
		tubes = tubes->next;
	}
	lst_sort(routs);
	return (routs);
}

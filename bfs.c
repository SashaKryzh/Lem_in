/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bfs.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okryzhan <okryzhan@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/11 19:04:22 by okryzhan          #+#    #+#             */
/*   Updated: 2018/12/11 19:04:22 by okryzhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

t_tube	*q_add(t_tube *q, t_room *to_visit)
{
	t_tube	*new;
	t_tube	*tmp;

	new = (t_tube *)malloc(sizeof(t_tube));
	new->path = to_visit;
	new->next = NULL;
	if (!q)
		q = new;
	else
	{
		tmp = q;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
	}
	return (q);
}

int		q_get(t_tube **q)
{
	t_tube	*tmp;
	int		v;

	v = q[0]->path->index;
	tmp = *q;
	*q = q[0]->next;
	free(tmp);
	return (v);
}

void	bfs_init(int *p, int *u, int *d, int src)
{
	int i;

	i = 0;
	while (i < g_cnt_rooms)
	{
		p[i] = -1;
		u[i] = 0;
		d[i] = INF;
		i++;
	}
	u[src] = 1;
	d[src] = 0;
}

int		bfs_check(t_tube *tmp, int *d, int *p, int v)
{
	d[tmp->path->index] = d[v] + 1;
	p[tmp->path->index] = v;
	if (tmp->path->role == end)
		return (0);
	return (1);
}

int		bfs(t_room **rooms, int *p, int src, t_tube *q)
{
	t_tube	*tmp;
	int		u[g_cnt_rooms];
	int		d[g_cnt_rooms];
	int		v;

	q = q_add(q, rooms[src]);
	bfs_init(p, u, d, src);
	while (q)
	{
		v = q_get(&q);
		tmp = rooms[v]->tubes;
		while (tmp)
		{
			if (!u[tmp->path->index] && !tmp->path->used
				&& tmp->path->role != locked)
			{
				if (!(u[tmp->path->index] = bfs_check(tmp, d, p, v)))
					return (bfs_return(q, d));
				q = q_add(q, tmp->path);
			}
			tmp = tmp->next;
		}
	}
	return (d[g_dst]);
}

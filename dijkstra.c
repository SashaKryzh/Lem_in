/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dijkstra.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okryzhan <okryzhan@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/05 12:29:04 by okryzhan          #+#    #+#             */
/*   Updated: 2018/12/05 12:29:04 by okryzhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	init_arrays(int **d, int **u, int **p, int cnt)
{
	int i;

	*d = (int *)malloc(sizeof(int) * (cnt + 1));
	*u = (int *)malloc(sizeof(int) * (cnt + 1));
	*p = (int *)malloc(sizeof(int) * (cnt + 1));
	i = 0;
	while (i < cnt)
	{
		d[0][i] = INF;
		u[0][i] = 0;
		p[0][i] = -1;
		i++;
	}
}

void	check_tubes(t_room **rooms, int v, int *d, int *p)
{
	t_tube	*tubes;

	if (v == -1)
		return ;
	tubes = rooms[v]->tubes;
	while (tubes)
	{
		if (d[v] + 1 < d[tubes->path->index])
		{
			d[tubes->path->index] = d[v] + 1;
			p[tubes->path->index] = v;
		}
		tubes = tubes->next;
	}
}

int		*dijkstra(t_room **rooms, int src, int **p)
{
	int		*d;
	int		*u;
	int		v;
	int		i;
	int		j;

	init_arrays(&d, &u, p, g_cnt_rooms);
	d[src] = 0;
	i = 0;
	while (i < g_cnt_rooms)
	{
		v = -1;
		j = -1;
		while (++j < g_cnt_rooms)
			if (!u[j] && (v == -1 || d[j] < d[v]) && rooms[j]->used == 0)
				v = j;
		i++;
		if (d[v] == INF)
			break ;
		u[v] = 1;
		check_tubes(rooms, v, d, *p);
	}
	free(u);
	return (d);
}

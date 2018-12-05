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

	*d = (int *)malloc(sizeof(int) * cnt);
	*u = (int *)malloc(sizeof(int) * cnt);
	*p = (int *)malloc(sizeof(int) * cnt);
	i = 0;
	while (i < cnt)
	{
		d[0][i] = INF;
		u[0][i] = 0;
		p[0][i] = -1;
		i++;
	}
}

void	check_tubes(t_room *rooms, int v, int *d, int *p)
{
	t_tube	*tubes;

	tubes = find_room_index(rooms, v)->tubes;
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

void	dijkstra(t_room *rooms, int cnt_rooms, int src, int **p)
{
	int		*d;
	int		*u;
	int		v;
	int		i;
	int		j;

	init_arrays(&d, &u, p, cnt_rooms);
	d[src] = 0;
	i = 0;
	while (i < cnt_rooms)
	{
		v = -1;
		j = -1;
		while (++j < cnt_rooms)
			if (!u[j] && (v == -1 || d[j] < d[v]))
				v = j;
		if (d[v] == INF)
			continue ;
		u[v] = 1;
		check_tubes(rooms, v, d, *p);
		i++;
	}
	free(d);
	free(u);
}

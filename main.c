/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okryzhan <okryzhan@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/03 12:12:22 by okryzhan          #+#    #+#             */
/*   Updated: 2018/12/03 12:12:22 by okryzhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	exit_func(int type, char *msg)
{
	ft_printf("%s\n", msg);
	exit(type);
}

void	print_path(t_room *rooms, int src, int dst, int *p)
{
	int v;

	v = dst;
	if (p[v] == -1)
	{
		ft_printf("No path :(\n");
		return ;
	}
	while (v != src)
	{
		ft_printf("%s <- ", find_room_index(rooms, v)->name);
		v = p[v];
	}
	ft_printf("%s\n", find_room_index(rooms, v)->name);
}

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
			break ;
		u[v] = 1;
		check_tubes(rooms, v, d, *p);
		i++;
	}
	free(d);
	free(u);
}

int		main(void)
{
	t_room	*rooms;
	int		ants;
	int		*p;
	int		src;

	ants = get_ants();
	rooms = get_rooms();

	//print_rooms(lst);
	//ft_printf("!!!!!!!!!!!\n\n");

	src = find_room_role(rooms, 1)->index;
	print_rooms(rooms);
	dijkstra(rooms, count_rooms(rooms), src, &p);
	print_path(rooms, src, find_room_role(rooms, 2)->index, p);
	return (0);
}

// t_room		**lst_to_arr(t_room *lst)
// {
// 	t_room		**rooms;
// 	int			i;

// 	rooms = (t_room **)malloc(sizeof(t_room *) * count_rooms(lst) + 1);
// 	i = 0;
// 	while (lst)
// 	{
// 		rooms[i] = lst;
// 		lst = lst->next;
// 		i++;
// 	}
// 	rooms[i] = 0;
// 	return (rooms);
// }
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

int		count_rooms(t_room *rooms)
{
	int i;

	i = 0;
	while (rooms)
	{
		rooms = rooms->next;
		i++;
	}
	return (i);
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

void	print_path(t_room *rooms, int src, int dst, int *p)
{
	int v;

	v = dst;
	while (v != src)
	{
		ft_printf("%s <- ", find_room_index(rooms, v)->name);
		v = p[v];
	}
	ft_printf("%s\n", find_room_index(rooms, v)->name);
}

void	dijkstra(t_room *rooms, int cnt_rooms, int src)
{
	int	i;
	int j;
	int	v;
	int	*d;
	int	*u;
	int	*p;
	t_tube *cons;

	d = (int *)malloc(sizeof(int) * cnt_rooms);
	u = (int *)malloc(sizeof(int) * cnt_rooms);
	p = (int *)malloc(sizeof(int) * cnt_rooms);
	i = 0;
	while (i < cnt_rooms)
	{
		d[i] = INF;
		u[i] = 0;
		p[i] = 0;
		i++;
	}
	d[src] = 0;
	i = 0;
	while (i < cnt_rooms)
	{
		v = -1;
		j = 0;
		while (j < cnt_rooms)
		{
			if (!u[j] && (v == -1 || d[j] < d[v]))
				v = j;
			j++;
		}
		if (d[v] == INF)
			break ;
		u[v] = 1;
		cons = find_room_index(rooms, v)->tubes;
		while (cons)
		{
			if (d[v] + 1 < d[cons->path->index])
			{
				d[cons->path->index] = d[v] + 1;
				p[cons->path->index] = v;
			}
			cons = cons->next;
		}
		i++;
	}
	print_path(rooms, src, find_room_role(rooms, 2)->index, p);
}

int		main(void)
{
	int		ants;
	t_room	*lst;
	int		src;

	ants = get_ants();
	lst = get_rooms();

	//print_rooms(lst);
	//ft_printf("!!!!!!!!!!!\n\n");

	src = find_room_role(lst, 1)->index;
	print_rooms(lst);
	dijkstra(lst, count_rooms(lst), src);
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
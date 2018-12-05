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
	ft_printf("%s", find_room_index(rooms, v)->name);
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

t_path	*find_routs(t_room **rooms, int src, int dst)
{
	t_path	*routs;
	t_tube	*tubes;
	int		*p;
	int		*d;

	routs = NULL;
	tubes = rooms[src]->tubes;
	while (tubes)
	{
		rooms[src]->used = 1;
		while (1)
		{
			d = dijkstra(rooms, count_rooms(*rooms), tubes->path->index, &p);
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
		}
		unmark_rout(*rooms);
		tubes = tubes->next;
	}
	return (routs);
}

void	print_moves(t_room **rooms, t_path *routs, int src)
{
	rooms = NULL;
	routs = NULL;
	src = 0;
}

int		main(void)
{
	t_room	*lst;
	t_room	**rooms;
	t_path	*routs;
	int		ants;
	int		src;
	int		dst;

	ants = get_ants();
	lst = get_rooms();
	rooms = lst_to_array(lst);
	src = find_room_role(*rooms, start)->index;
	dst = find_room_role(*rooms, end)->index;
	routs = find_routs(rooms, src, dst);

	print_routs(*rooms, routs, src, dst);

	print_moves(rooms, routs, src);
	return (0);
}

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

int	g_cnt_rooms;

void	exit_func(int type, char *msg)
{
	ft_printf("%s\n", msg);
	exit(type);
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
	new->p = (int *)malloc(sizeof(int) * g_cnt_rooms);
	int i = 0;
	while (i < g_cnt_rooms)
	{
		new->p[i] = p[i];
		i++;
	}
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
		ft_printf("%s\n", rooms[tubes->path->index]->name);
		t_path	*tmp;
		while (1)
		{
			if (i == 1)
			{
				print_path(*rooms, tmp->src, dst, tmp->p);
				ft_printf("!!!\n\n");
			}
			d = dijkstra(rooms, count_rooms(*rooms), tubes->path->index, &p);
			if (i == 1)
			{
				print_path(*rooms, tmp->src, dst, tmp->p);
				ft_printf("???\n\n");
			}
			p[dst] = tubes->path->index == dst ? src : p[dst];
			if (p[dst] == -1)
			{
				free(p);
				free(d);
				break ;
			}
			mark_rout(*rooms, p, tubes->path->index, dst);

			ft_printf("JUST FIND\n");
			print_path(*rooms, tubes->path->index, dst, p);
			ft_printf("\n");
			for (int j = 0; j < g_cnt_rooms; j++)
				ft_printf("%d ", p[j]);
			ft_printf("\n\n");

			routs = add_rout(routs, p, d[dst] + 1, tubes->path->index);

			tmp = routs;
			while (tmp->next)
			{
				print_path(*rooms, tmp->src, dst, tmp->p);
				ft_printf("\n");
				for (int j = 0; j < g_cnt_rooms; j++)
					ft_printf("%d ", tmp->p[j]);
				ft_printf("\n");
				tmp = tmp->next;
			}
			print_path(*rooms, tmp->src, dst, tmp->p);
			ft_printf("!!!\n\n");

			free(d);
			if (rooms[p[dst]] == tubes->path || tubes->path->index == dst)
			{
				free(p);
				break ;
			}
			free(p);
			i++;
		}
		unmark_rout(*rooms);
		tubes = tubes->next;
	}
	ft_printf("\n!!!! END OF ROUTS !!!!\n\n");
	// lst_sort(routs);
	return (routs);
}

// void	print_moves(t_room **rooms, t_path *routs, int src)
// {

// }

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
	
	int i = 0;
	while (rooms[i])
	{
		print_room_info(rooms[i]);
		i++;
	}
	
	src = find_room_role(*rooms, start)->index;
	dst = find_room_role(*rooms, end)->index;
	g_cnt_rooms = count_rooms(*rooms);
	// print_room_info(rooms[src]);
	// print_room_info(rooms[dst]);
	// exit(1);

	routs = find_routs(rooms, src, dst);
	print_routs(*rooms, routs, src, dst);
	// print_moves(rooms, routs, src);
	return (0);
}

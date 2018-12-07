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
int	g_ants;

void	exit_func(int type, char *msg)
{
	ft_printf("%s\n", msg);
	exit(type);
}

void	print_path(t_room *rooms, t_path *routs, int dst)
{
	int v;

	v = dst;
	if (routs->p[v] == -1)
	{
		ft_printf("No path :(\n");
		return ;
	}
	while (v != routs->src)
	{
		ft_printf("%s <- ", find_room_index(rooms, v)->name);
		v = routs->p[v];
	}
	ft_printf("%s", find_room_index(rooms, v)->name);
}

void	convert_routs(t_path *routs, int src, int dst)
{
	int v;

	while (routs)
	{
		v = routs->p[dst];
		while (v != routs->src)
			v = routs->p[v];
		routs->p[v] = src;
		routs->src = src;
		routs = routs->next;
	}
}

void	print_moves(t_room **rooms, t_path *first_rout, int src, int dst)
{
	t_path	*routs;
	t_path	*tmp;
	int		moves;

	ft_printf("ants: %d\n", g_ants);
	routs = first_rout;
	while (routs)
	{
		moves = routs->len + g_ants - 1;
		mark_rout(*rooms, routs->p, src, dst);
		tmp = first_rout;
		while (tmp)
		{
			tmp = tmp->next;
		}
		ft_printf("%d\n", moves);
		routs = routs->next;
	}
}

int		main(void)
{
	t_room	*lst;
	t_room	**rooms;
	t_path	*routs;
	int		src;
	int		dst;

	g_ants = get_ants();
	lst = get_rooms();
	rooms = lst_to_array(lst);
	g_cnt_rooms = count_rooms(*rooms);
	print_rooms(*rooms);
	
	src = find_room_role(*rooms, start)->index;
	dst = find_room_role(*rooms, end)->index;
	routs = find_routs(rooms, src, dst);
	convert_routs(routs, src, dst);
	print_routs(*rooms, routs, src, dst);

	ft_printf("\n!!! MOVES !!!\n\n");
	print_moves(rooms, routs, src, dst);
	return (0);
}

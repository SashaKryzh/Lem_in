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
int	g_src;
int	g_dst;

void	exit_func(t_room *rooms, char *msg)
{
	ft_printf("Error: %s\n", msg);
	exit(0);
}

int		is_rout_free(t_room **rooms, t_path *route, int dst)
{
	int v;

	v = route->p[dst];
	while (v != route->src)
	{
		if (rooms[v]->used)
			return (0);
		v = route->p[v];
	}
	return (1);
}

void	mark_best_rout(t_path *routes)
{
	while (routes)
	{
		if (routes->selected)
			routes->best_rout = 1;
		routes->selected = 0;
		routes = routes->next;
	}
}

void	unselect_rout(t_path *routes)
{
	while (routes)
	{
		routes->selected = 0;
		routes = routes->next;
	}
}

int		cnt_moves(t_room **rooms, t_path *first_routes)
{
	t_path	*routes;
	int		moved;
	int		cnt;
	int		i;

	cnt = 0;
	rooms[g_src]->ant = g_ants;
	rooms[g_dst]->ant = 0;
	while (rooms[g_dst]->ant != g_ants)
	{
		moved = 0;
		routes = first_routes;
		while (routes)
		{
			if (routes->selected)
			{
				i = routes->len;
				while (i > 0)
				{
					if (routes->route[i - 1]->ant)
					{
						routes->route[i - 1]->ant -= 1;
						routes->route[i]->ant += 1;
						moved = 1;
					}
					i--;
				}
			}
			routes = routes->next;
		}
		cnt += moved;
	}
	return (cnt);
}

void	find_best(t_room **rooms, t_path *first_route)
{
	t_path	*routes;
	t_path	*tmp;
	int		best_moves;
	int		moves1;
	int		moves2;

	best_moves = INF;
	ft_printf("ants: %d\n", g_ants); //

	routes = first_route;
	while (routes)
	{
		routes->selected = 1;
		moves1 = cnt_moves(rooms, routes);
		mark_rout2(routes);
		tmp = first_route;
		while (tmp)
		{
			if (is_rout_free(rooms, tmp, g_dst))
			{
				tmp->selected = 1;
				moves2 = cnt_moves(rooms, first_route);
				if (moves2 < moves1)
				{
					moves1 = moves2;
				} else {
					tmp->selected = 0;
					break ;
				}
			}
			tmp = tmp->next;
		}
		if (moves1 < best_moves)
		{
			best_moves = moves1;
			mark_best_rout(first_route);
		}
		unselect_rout(first_route);
		unmark_rout(*rooms);
		routes = routes->next;
	}
	ft_printf("%d\n", best_moves); //
}

int		main(void)
{
	t_room	**rooms;
	t_path	*routs;

	get_ants();
	rooms = get_rooms();
	print_rooms(*rooms); //

	ft_printf("!!! ROUTES !!!\n\n"); //
	g_src = find_room_role(*rooms, start)->index;
	g_dst = find_room_role(*rooms, end)->index;
	if (!(routs = find_routs(rooms, g_src, g_dst)))
		exit_func(*rooms, "No path to end");
	convert_routs(rooms, routs, g_src, g_dst);
	print_routs(routs); //

	// routs->selected = 1;
	// routs->next->selected = 1;
	// ft_printf("%d\n", cnt_moves(rooms, routs));
	// exit(1);

	ft_printf("\n!!! MOVES !!!\n\n"); //
	find_best(rooms, routs);

	// system("leaks ants");
	return (0);
}

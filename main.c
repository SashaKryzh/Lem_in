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
	system("leaks ants");
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

int		cnt_moves(t_room **rooms, t_path *routes, int dst)
{
	int cnt;
	int v;

	cnt = 0;
	rooms[routes->src]->ant = g_ants;
	rooms[dst]->ant = 0;
	while (rooms[dst]->ant != g_ants)
	{
		if (rooms[routes->p[dst]]->ant)
		{
			rooms[dst]->ant += 1;
			rooms[routes->p[dst]]->ant -= 1;
		}
		v = routes->p[dst];
		while (1)
		{
			if (rooms[routes->p[v]]->ant)
			{
				rooms[v]->ant += 1;
				rooms[routes->p[v]]->ant -= 1;
			}
			v = routes->p[v];
			if (v == routes->src)
				break ;
		}
		cnt++;
	}
	return (cnt);
}

void	find_best(t_room **rooms, t_path *first_route, int src, int dst)
{
	t_path	*routes;
	t_path	*tmp;
	int		moves1;
	int		moves2;
	int		best_moves;
	int		together;

	best_moves = INF;
	ft_printf("ants: %d\n", g_ants); //
	routes = first_route;
	while (routes)
	{
		// moves1 = cnt_moves(rooms, routes, dst);
		// if (moves1 < best_moves)
		// {
		// 	best_moves = moves1;
		// 	routes->selected = 1;
		// }
		// mark_rout(rooms, routes->p, src, dst);
		// tmp = first_route;
		// while (tmp && tmp->len <= g_ants)
		// {
		// 	if (is_rout_free(rooms, tmp, dst))
		// 	{
				
		// 	}
		// 	tmp = tmp->next;
		// }
		unmark_rout(*rooms);
		ft_printf("%d\n", moves1);
		routes = routes->next;
	}
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

	ft_printf("\n!!! MOVES !!!\n\n"); //
	find_best(rooms, routs, g_src, g_dst);

	// system("leaks ants");
	return (0);
}

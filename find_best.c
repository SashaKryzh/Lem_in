/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_best.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okryzhan <okryzhan@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/10 18:55:55 by okryzhan          #+#    #+#             */
/*   Updated: 2018/12/10 18:55:55 by okryzhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int		is_rout_free(t_route *routes)
{
	int i;

	i = 1;
	while (routes->route[i + 1])
	{
		if (routes->route[i]->used)
			return (0);
		i++;
	}
	return (1);
}

void	mark_best_rout(t_route *routes)
{
	while (routes)
	{
		routes->best_rout = 0;
		if (routes->selected)
			routes->best_rout = 1;
		routes = routes->next;
	}
}

void	unselect_routs(t_route *routes)
{
	while (routes)
	{
		routes->selected = 0;
		routes = routes->next;
	}
}

void	unhold_ants(t_room **rooms)
{
	int i;

	i = 0;
	while (rooms[i])
	{
		rooms[i]->ant_hold = 0;
		i++;
	}
}

int		cnt_moves(t_room **rooms, t_route *first_routes)
{
	t_route	*routes;
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
					if (routes->route[i - 1]->ant && !routes->route[i - 1]->ant_hold
					&& (routes->route[i]->ant == 0 || routes->route[i]->role == end))
					{
						routes->route[i - 1]->ant -= 1;
						routes->route[i]->ant += 1;
						routes->route[i]->ant_hold = 1;
						moved = 1;
					}
					i--;
				}
			}
			routes = routes->next;
		}
		unhold_ants(rooms);
		cnt += moved;
	}
	return (cnt);
}

void	find_best(t_room **rooms, t_route *first_route)
{
	t_route	*routes;
	t_route	*tmp;
	int		best_moves;
	int		moves1;
	int		moves2;

	best_moves = INF;
	ft_printf("ants: %d\n", g_ants); //

	routes = first_route;
	while (routes)
	{
		routes->selected = 1;
		moves1 = cnt_moves(rooms, first_route);
		// ft_printf("one : %d\n", moves1);
		mark_rout2(routes);
		tmp = first_route;
		while (tmp)
		{
			if (tmp != routes) // если путь start-end
			{
				tmp->selected = 1;
				moves2 = cnt_moves(rooms, first_route);
				// ft_printf("more : %d\n", moves2);
				mark_rout2(tmp);
				if (moves2 < moves1)
				{
					moves1 = moves2;
				}
				else
				{
					tmp->selected = 0;
					unmark_rout(tmp);
				}
			}
			tmp = tmp->next;
		}
		if (moves1 < best_moves)
		{
			best_moves = moves1;
			mark_best_rout(first_route);
		}
		unselect_routs(first_route);
		unmark_routs(*rooms);
		routes = routes->next;
	}
	g_cnt_moves = best_moves;
	ft_printf("best: %d\n\n", best_moves); //
}

// int		find_best(t_room **rooms, t_route *first_route, int best_moves)
// {
// 	t_route	*routes;
// 	t_route	*tmp;
// 	int		moves1;
// 	int		moves2;

// 	routes = first_route;
// 	while (routes)
// 	{
// 		if (!routes->selected)
// 		{
// 			routes->selected = 1;
// 			moves1 = cnt_moves(rooms, first_route);
// 			if (moves1 < best_moves)
// 			{
// 				if (find_best(rooms, first_route, moves1))
// 				{
// 					return (1);
// 				}
// 			}
// 			else
// 			{
// 				routes->selected = 0;
// 				return (0);
// 			}
// 		}
// 		routes = routes->next;
// 	}
// 	return (1);
// }
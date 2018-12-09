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

void	exit_func(t_room *rooms, char *msg)
{
	ft_printf("Error: %s\n", msg);
	system("leaks ants");
	exit(0);
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

void	print_moves(t_room **rooms, t_path *first_route, int src, int dst)
{
	t_path	*routes;
	t_path	*tmp;
	int		moves1;
	int		moves2;
	int		together;

	ft_printf("ants: %d\n", g_ants); //
	routes = first_route;
	while (routes)
	{
		moves1 = routes->len + g_ants - 1;
		ft_printf("%d\n", moves1); //
		// mark_rout(*rooms, routes->p, src, dst);
		// tmp = first_route;
		// while (tmp)
		// {
		// 	if (is_rout_free(rooms, tmp, dst) && tmp != routes) // road free and its not start-end
		// 	{
		// 		moves2 = tmp->len + g_ants - 1;
		// 		ft_printf("another moves: %d\n", moves2);
		// 		together = g_ants / 2 - 1 + routes->len > tmp->len ? routes->len : tmp->len; // bullshit
		// 		ft_printf("together: %d\n", together);
		// 	}
		// 	tmp = tmp->next;
		// }
		// unmark_rout(*rooms);
		routes = routes->next;
	}
}

int		main(void)
{
	t_room	*lst;
	t_room	**rooms;
	t_path	*routs;
	int		src;
	int		dst;

	get_ants();
	lst = get_rooms();
	rooms = lst_to_array(lst);
	print_rooms(*rooms);
	
	ft_printf("!!! ROUTES !!!\n\n");
	src = find_room_role(*rooms, start)->index;
	dst = find_room_role(*rooms, end)->index;
	if (!(routs = find_routs(rooms, src, dst)))
		exit_func(*rooms, "No path to end");
	convert_routs(routs, src, dst);
	print_routs(*rooms, routs, src, dst);

	ft_printf("\n!!! MOVES !!!\n\n");
	print_moves(rooms, routs, src, dst);

	// system("leaks ants");
	return (0);
}

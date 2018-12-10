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

void	print_moves(t_room **rooms, t_path *first_routes)
{
	t_path	*routes;
	int		i;
	int		cnt;

	cnt = 0;
	rooms[g_src]->ant = g_ants;
	rooms[g_dst]->ant = 0;
	while (rooms[g_dst]->ant != g_ants)
	{
		routes = first_routes;
		while (routes)
		{
			if (routes->best_rout)
			{
				i = routes->len;
				while (i > 0)
				{
					if (routes->route[i - 1]->ant)
					{
						routes->route[i - 1]->ant -= 1;
						routes->route[i]->ant += 1;
						if (i > 1)
							routes->route[i]->ant_index = routes->route[i - 1]->ant_index;
						else
							routes->route[i]->ant_index = ++cnt;
						ft_printf("L%d-%s ", routes->route[i]->ant_index, routes->route[i]->name);
					}
					i--;
				}
			}
			routes = routes->next;
		}
		ft_printf("\n");
	}
}

int		main(void)
{
	t_room	**rooms;
	t_path	*routs;

	get_ants();
	rooms = get_rooms();
	// print_rooms(*rooms); //

	// ft_printf("!!! ROUTES !!!\n\n"); //
	g_src = find_room_role(*rooms, start)->index;
	g_dst = find_room_role(*rooms, end)->index;
	if (!(routs = find_routs(rooms, g_src, g_dst)))
		exit_func(*rooms, "No path to end");
	convert_routs(rooms, routs, g_src, g_dst);
	// print_routs(routs); //

	ft_printf("\n!!! BEST COMB !!!\n\n"); //
	find_best(rooms, routs);
	print_routs(routs);

	ft_printf("\n!!! MOVES !!!\n\n"); 
	print_moves(rooms, routs);

	// system("leaks ants");
	return (0);
}

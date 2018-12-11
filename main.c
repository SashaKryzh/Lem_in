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

int		g_cnt_rooms;
int		g_cnt_moves;
int		g_ants;
int		g_src;
int		g_dst;
int		g_tab_size;
char	**g_tab;

void	exit_func(t_room *rooms, char *msg)
{
	ft_printf("Error: %s\n", msg);
	// system("leaks ants");
	exit(0);
}

void	print_parsed_data(void)
{
	int i;

	i = 0;
	while (g_tab[i])
	{
		ft_printf("%s\n", g_tab[i]);
		i++;
	}
	ft_printf("\n");
}

void	print_moves(t_room **rooms, t_route *first_routes)
{
	t_route	*routes;
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
					if (ROOM[i - 1]->ant)
					{
						ROOM[i - 1]->ant -= 1;
						ROOM[i]->ant += 1;
						if (i > 1)
							ROOM[i]->ant_index = ROOM[i - 1]->ant_index;
						else
							ROOM[i]->ant_index = ++cnt;
						ft_printf("L%d-%s ", ROOM[i]->ant_index, ROOM[i]->name);
					}
					i--;
				}
			}
			routes = routes->next;
		}
		ft_printf("!\n");
	}
	ft_printf("moves: %d\n", g_cnt_moves);
}

int		main(void)
{
	t_room	**rooms;
	t_route	*routs;

	g_tab_size = 1000;
	g_tab = (char **)malloc(sizeof(char *) * g_tab_size);
	get_ants();
	rooms = get_rooms();
	print_rooms(*rooms);

	int p[g_cnt_rooms + 1];
	bfs(rooms, p, g_src, NULL);

	for (int i = 0; i < g_cnt_rooms; i++)
		ft_printf("%d ", p[i]);
	ft_printf("\n");

	for (int i = 0; i < g_cnt_rooms; i++)
		ft_printf("%d ", p[i]);
	ft_printf("\n");

	for (int i = 0; i < g_cnt_rooms; i++)
		ft_printf("%d ", p[i]);
	ft_printf("\n");
	
	int v;
	v = g_dst;
	while (v != -1)
	{
		ft_printf("%s <- ", rooms[v]->name);
		v = p[v];
	}
	exit(0);

	// ft_printf("!!! ROUTES !!!\n\n"); //
	if (!(routs = find_routs(rooms, g_src, g_dst)))
		exit_func(*rooms, "No path to end");
	convert_routs(rooms, routs);
	// print_routs(routs); //

	ft_printf("\n!!! BEST COMB !!!\n\n"); //
	find_best(rooms, routs);

	print_routs(routs);

	ft_printf("\n!!! MOVES !!!\n\n");
	print_parsed_data();
	print_moves(rooms, routs);

	// system("leaks ants");
	return (0);
}

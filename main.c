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

char	**g_tab;
int		g_tab_size;
int		g_cnt_rooms;
int		g_ants;
int		g_cnt_dead;
int		g_src;
int		g_dst;
int		g_flag;

void	print_parsed_data(t_room **rooms, t_route *routes)
{
	int i;

	show_info(rooms, routes);
	i = 0;
	while (g_tab[i])
	{
		ft_printf("%s\n", g_tab[i]);
		i++;
	}
	ft_printf("\n");
}

int		main(int ac, char *av[])
{
	t_room	**rooms;
	t_route	*routes;
	int		cnt;

	manage_flags(ac, av);
	g_tab_size = 10000;
	g_tab = (char **)malloc(sizeof(char *) * g_tab_size);
	get_ants();
	rooms = get_rooms();
	if (!(routes = find_routs(rooms)))
		exit_func(0, "No path to end");
	print_parsed_data(rooms, routes);
	if (routes->route[1]->role == end)
		start_end(rooms);
	cnt = g_flag == 2 ? short_move(rooms, routes) : move(rooms, routes);
	if (g_flag == 3)
		ft_printf("\033[0;32m[TURNS]: %d\033[0m\n", cnt);
	if (g_cnt_dead > 0)
		ft_printf("\033[0;31m[DEAD]: %d\033[0m\n", g_cnt_dead);
	return (0);
}

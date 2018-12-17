/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okryzhan <okryzhan@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/13 10:23:19 by okryzhan          #+#    #+#             */
/*   Updated: 2018/12/13 10:23:20 by okryzhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	exit_func(int usage, char *msg)
{
	ft_printf("\033[0;31m[Error]:\033[0m \033[0;33m%s\033[0m\n", msg);
	if (usage)
	{
		ft_printf("\033[0;32m/=============================\\\n");
		ft_printf("|                             |\n");
		ft_printf("|  -i : show info             |\n");
		ft_printf("|  -s : use shortest path     |\n");
		ft_printf("|  -c : count turns           |\n");
		ft_printf("|                             |\n");
		ft_printf("|  Only one at a time         |\n");
		ft_printf("\\=============================/\033[0m\n");
	}
	exit(0);
}

void	manage_flags(int ac, char *av[])
{
	if (ac == 1)
		return ;
	if (ac > 2)
		exit_func(1, "Too much flags");
	if (ft_strequ(av[1], "-i"))
		g_flag = 1;
	else if (ft_strequ(av[1], "-s"))
		g_flag = 2;
	else if (ft_strequ(av[1], "-c"))
		g_flag = 3;
	else
		exit_func(1, "Unknown flag");
}

void	start_end(t_room **rooms)
{
	int cnt;

	cnt = 0;
	rooms[g_src]->ant = g_ants;
	rooms[g_dst]->ant = 0;
	while (rooms[g_dst]->ant != g_ants)
	{
		cnt += 1;
		rooms[g_dst]->ant += 1;
		ft_printf("L%d-%s ", cnt, rooms[g_dst]->name);
	}
	ft_printf("\n");
	exit(0);
}

int		bfs_return(t_tube *q, int *d)
{
	t_tube *tmp;

	while (q)
	{
		tmp = q;
		free(tmp);
		q = q->next;
	}
	return (d[g_dst]);
}

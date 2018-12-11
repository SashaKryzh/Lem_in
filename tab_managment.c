/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tab_managment.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okryzhan <okryzhan@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/11 17:48:00 by okryzhan          #+#    #+#             */
/*   Updated: 2018/12/11 17:48:01 by okryzhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	increase_tab(void)
{
	char	**tmp;
	int		prev;
	int		i;

	tmp = g_tab;
	prev = g_tab_size;
	g_tab_size *= 2;
	g_tab = (char **)malloc(sizeof(char *) * g_tab_size);
	i = 0;
	while (i < prev)
	{
		g_tab[i] = tmp[i];
		i++;
	}
	free(tmp);
	while (i < g_tab_size)
	{
		g_tab[i] = NULL;
		i++;
	}
}

void	add_to_tab(char *line)
{
	static int	i;

	if (i == g_tab_size)
		increase_tab();
	g_tab[i] = line;
	i++;
}

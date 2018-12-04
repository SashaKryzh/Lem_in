/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okryzhan <okryzhan@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/03 12:39:11 by okryzhan          #+#    #+#             */
/*   Updated: 2018/12/03 12:39:12 by okryzhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEM_IN_H
# define LEM_IN_H

# include "libft.h"

typedef struct		s_room
{
	char			*name;
	struct s_tube	*tubes;
	enum			e_role
	{
		none = 0,
		start,
		end
	}				role;
	struct s_room	*next;
}					t_room;

typedef struct		s_tube
{
	t_room			*path;
	struct s_tube	*next;
}					t_tube;

/*
** Parser
*/

int		get_ants(void);
t_room	*get_rooms(void);

void	exit_func(int type, char *msg);
int		char_tab_len(char **tab);

/*
** Rooms utils
*/

t_room				*create_room(char *name, int role);
t_room				*add_room(t_room *start, char *name, int role);
void				add_connection(t_room *room, char *from, char *to);
t_room				*find_room_name(t_room *room, char *name);
t_room				*find_room_role(t_room *room, int role);

/*
** Tests
*/

void	print_rooms(t_room *room);
void	print_room_info(t_room *room);
t_room	*test_init(void);

#endif

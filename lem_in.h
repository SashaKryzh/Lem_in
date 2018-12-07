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

# define INF 2147483647

extern int g_cnt_rooms;

typedef struct		s_room
{
	int				index;
	char			*name;
	int				used;
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

typedef struct		s_path
{
	int				*p;
	int				src;
	int				len;
	struct s_path	*next;
}					t_path;

int					*dijkstra(t_room **rooms, int src, int **p);

/*
** Parser
*/

int		get_ants(void);
t_room	*get_rooms(void);

/*
** Utils
*/

void	exit_func(int type, char *msg);
int		char_tab_len(char **tab);
t_room	**lst_to_array(t_room *lst);

/*
** Rooms utils
*/

int					count_rooms(t_room *rooms);
t_room				*create_room(char *name, int role);
t_room				*add_room(t_room *start, char *name, int role);
void				add_connection(t_room *room, char *from, char *to);

/*
** Find room
*/

t_room				*find_room_name(t_room *room, char *name);
t_room				*find_room_role(t_room *room, int role);
t_room				*find_room_index(t_room *rooms, int index);

/*
** Tests
*/

void	print_rooms(t_room *room);
void	print_rooms_array(t_room **rooms);
void	print_room_info(t_room *room);
void	print_routs(t_room *rooms, t_path *routs, int src, int dst);
void	print_path(t_room *rooms, int src, int dst, int *p);

#endif

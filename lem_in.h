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
# define ROOM routes->route

extern int		g_cnt_rooms;
extern int		g_cnt_moves;
extern int		g_ants;
extern int		g_src;
extern int		g_dst;
extern int		g_tab_size;
extern char		**g_tab;

typedef struct		s_room
{
	char			*name;
	int				index;

	int				used;
	int				ant;
	int				ant_index;
	int				ant_hold;

	struct s_tube	*tubes;
	enum			e_role
	{
		none = 0,
		start,
		end
	}				role;
	struct s_room	*next;
}					t_room;

typedef struct		s_route
{
	t_room			**route;
	int				*p;
	int				src;
	int				len;
	int				selected;
	int				best_rout;
	struct s_route	*next;
}					t_route;

typedef struct		s_tube
{
	t_room			*path;
	struct s_tube	*next;
}					t_tube;

t_route				*find_routs(t_room **rooms, int src, int dst);
// int					find_best(t_room **rooms, t_route *first_route, int best_moves);
void				find_best(t_room **rooms, t_route *first_route);
t_route				*add_rout(t_route *routs, int *p, int len, int src);
void				dijkstra(t_room **rooms, int src, int **p, int *dist);
int					bfs(t_room **rooms, int *p, int src, t_tube *q);

void				mark_rout(t_room **rooms, int *p, int src, int dst);
void				mark_rout2(t_route *routes);
void				unmark_routs(t_room *rooms);
void				unmark_rout(t_route	*route);

/*
** Parser
*/

void				get_ants(void);
t_room				**get_rooms(void);

/*
** Utils
*/

void				exit_func(t_room *rooms, char *msg);
t_room				**lst_to_array(t_room *lst);
void				lst_sort(t_route *routs);
void				convert_routs(t_room **rooms, t_route *routs);
void				add_to_tab(char *line);

/*
** Rooms utils
*/

t_room				*create_room(char *name, int role);
t_room				*add_room(t_room *start, char *name, int role);
void				add_connection(t_room *room, char *from, char *to);

/*
** Find room
*/

t_room				*find_room_name(t_room *room, char *name);
// t_room				*find_room_role(t_room *room, int role);
// t_room				*find_room_index(t_room *rooms, int index);

/*
** Tests
*/

void				print_rooms(t_room *room);
void				print_rooms_array(t_room **rooms);
void				print_room_info(t_room *room);
void				print_routs(t_route *routs);
void				print_route(t_route *routs);

#endif

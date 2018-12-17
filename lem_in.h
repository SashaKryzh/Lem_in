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

extern char		**g_tab;
extern int		g_tab_size;
extern int		g_cnt_rooms;
extern int		g_ants;
extern int		g_cnt_dead;
extern int		g_src;
extern int		g_dst;
extern int		g_flag;

typedef struct		s_room
{
	char			*name;
	int				index;
	int				x;
	int				y;
	int				used;

	int				ant;
	int				ant_index;
	int				ant_hold;

	struct s_tube	*tubes;
	enum			e_role
	{
		none = 0,
		start,
		end,
		dead,
		locked
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

int					bfs(t_room **rooms, int *p, int src, t_tube *q);
t_route				*find_routs(t_room **rooms);
t_route				*add_rout(t_route *routs, int *p, int len, int src);
int					move(t_room **rooms, t_route *first_route);
int					short_move(t_room **rooms, t_route *first_route);

/*
** Parser
*/

void				get_ants(void);
t_room				**get_rooms(void);

/*
** Utils
*/

void				exit_func(int usage, char *msg);
t_room				**lst_to_array(t_room *lst);
void				lst_sort(t_route *routs);
t_route				*convert_routs(t_room **rooms, t_route *routs);
void				add_to_tab(char *line);
void				start_end(t_room **rooms);
void				show_info(t_room **rooms, t_route *routes);
void				manage_flags(int ac, char *av[]);

/*
** Rooms utils
*/

t_room				*create_room(char *name, int role);
t_room				*add_room(t_room *start, char *line, int role);
void				add_connection(t_room *room, char *from, char *to);

/*
** Route utils
*/

void				mark_route_p(t_room **rooms, int *p, int src, int dst);
void				mark_route_ar(t_route *routes);
void				unmark_routs(t_room *rooms);
void				unmark_rout(t_route	*route);
int					bfs_return(t_tube *q, int *d);

/*
** Find room
*/

t_room				*find_room_name(t_room *room, char *name);

/*
** Tests
*/

void				print_rooms(t_room *room);
void				print_rooms_array(t_room **rooms);
void				print_room_info(t_room *room);
void				print_routs(t_route *routs);
void				print_route(t_route *routs);

#endif

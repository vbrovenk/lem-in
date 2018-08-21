/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lemin.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbrovenk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/05 13:34:17 by vbrovenk          #+#    #+#             */
/*   Updated: 2018/08/05 13:34:19 by vbrovenk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEMIN_H
# define LEMIN_H

# include "libft.h"
# include "get_next_line.h"

# define DELETE_ROOM 1
# define DELETE_LINK 2
# define INFINITY 2147483647

typedef	struct		s_lemin{
	char			*output;
	int				count_ants;
	int				count_start;
	int				count_end;
	int				flag_start;
	int				flag_end;
	int				**matrix;
	int				*distances;
	int				*visited;
	int				*path;
	int				first_room;
	int				length_path;
	char			**final_path;
}					t_lemin;

typedef	struct		s_node
{
	int				index;
	char			*name;
	int				start;
	int				end;
	int				coord_x;
	int				coord_y;
	struct s_node	*next;
}					t_node;

typedef struct		s_queue
{
	t_node			*head;
	t_node			*tail;
	int				count;
}					t_queue;

typedef	struct		s_ant
{
	int				name_ant;
	int				index_room;
	struct s_ant	*next;
}					t_ant;

typedef	struct		s_list_ants
{
	t_ant			*head;
	t_ant			*tail;

}					t_list_ants;

void				enqueue(t_queue *queue, char **split, t_lemin *lemin);
void				check_same_coord(t_queue *queue);
void				ft_error();
void				move_ants(t_lemin *lemin);
void				move_ants_2_rooms(t_lemin *lemin);
void				set_indexes(t_queue *queue);
void				check_start_end(t_queue *queue, t_lemin *lemin);
void				make_matrix(t_queue *queue, t_lemin *lemin);
void				fill_matrix(char *line, t_queue *queue, t_lemin *lemin);
int					find_index(t_queue *queue, char *name_vertex);
void				delete_split(char **split, int what_del);
void				join_str(t_lemin *lemin, char *line);
int					find_index(t_queue *queue, char *name_vertex);
void				get_shortest_path(t_lemin *lemin, t_queue *queue);
int					find_end_index(t_queue *queue);
void				find_path(t_lemin *lemin, t_queue *queue);
void				join_str(t_lemin *lemin, char *line);
void				delete_split(char **split, int what_del);
char				*find_room_name(t_queue *queue, int index);
void				init_structs(t_lemin *lemin, t_queue *queue);
void				check_same_rooms(t_queue *queue);
char				*find_room_name(t_queue *queue, int index);
int					check_line(char *line);
int					check_split(char **split, char *line);
int					check_for_stop(char *line);
int					check_name_rooms(char **split, char *line, t_queue *queue);
void				check_count_spaces(char *line);

#endif

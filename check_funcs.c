/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_funcs.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbrovenk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/20 15:39:15 by vbrovenk          #+#    #+#             */
/*   Updated: 2018/08/20 15:39:17 by vbrovenk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

int		check_line(char *line)
{
	int i;
	int	count_dash;

	count_dash = 0;
	if (ft_strchr(line, '-') == 0)
	{
		ft_strdel(&line);
		return (1);
	}
	i = -1;
	while (line[++i])
	{
		if (line[i] == '-')
			count_dash++;
	}
	if (count_dash > 1)
	{
		ft_strdel(&line);
		return (1);
	}
	i = -1;
	while (line[++i])
	{
		if (ft_isspace(line[i]))
		{
			ft_strdel(&line);
			return (1);
		}
	}
	return (0);
}

int		check_split(char **split, char *line)
{
	int	i;

	i = 0;
	while (split[i] != NULL)
		i++;
	if (i != 2)
	{
		delete_split(split, DELETE_LINK);
		ft_strdel(&line);
		return (1);
	}
	return (0);
}

int		check_for_stop(char *line)
{
	if (line[0] == '\0')
		return (1);
	else
		return (0);
}

int		check_name_rooms(char **split, char *line, t_queue *queue)
{
	t_node	*temp;
	char	*room_left;
	char	*room_right;
	int		room_l_exist;
	int		room_r_exist;

	room_left = split[0];
	room_right = split[1];
	room_l_exist = 0;
	room_r_exist = 0;
	temp = queue->head;
	while (temp != NULL)
	{
		if (ft_strcmp(temp->name, room_left) == 0)
			room_l_exist = 1;
		if (ft_strcmp(temp->name, room_right) == 0)
			room_r_exist = 1;
		temp = temp->next;
	}
	if (room_l_exist == 1 && room_r_exist == 1)
		return (1);
	ft_strdel(&line);
	delete_split(split, DELETE_LINK);
	return (0);
}

void	check_same_coord(t_queue *queue)
{
	t_node	*curr_room;
	t_node	*next_room;

	curr_room = queue->head;
	while (curr_room != NULL)
	{
		next_room = curr_room->next;
		while (next_room != NULL)
		{
			if (curr_room->coord_x == next_room->coord_x &&
				curr_room->coord_y == next_room->coord_y)
			{
				ft_putstr("ROOMS HAVE SAME COORDINATES\n");
				ft_error();
			}
			next_room = next_room->next;
		}
		curr_room = curr_room->next;
	}
}

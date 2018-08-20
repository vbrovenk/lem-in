/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbrovenk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/18 16:54:12 by vbrovenk          #+#    #+#             */
/*   Updated: 2018/08/19 14:32:13 by vbrovenk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

void	ft_error(void)
{
	ft_putstr("ERROR\n");
	system("leaks lem-in");
	exit(1);
}

void	check_same_rooms(t_queue *queue)
{
	t_node *room;
	t_node *next_room;

	room = queue->head;
	while (room != NULL)
	{
		next_room = room->next;
		while (next_room != NULL)
		{
			if (ft_strcmp(room->name, next_room->name) == 0)
			{
				ft_putstr("THERE ARE ROOMS WITH SAME NAMES\n");
				ft_error();
			}
			next_room = next_room->next;
		}
		room = room->next;
	}
}

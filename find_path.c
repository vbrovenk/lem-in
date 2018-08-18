/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_path.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbrovenk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/18 16:14:08 by vbrovenk          #+#    #+#             */
/*   Updated: 2018/08/18 16:14:10 by vbrovenk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

static	void	get_final_path(t_lemin *lemin, t_queue *queue)
{
	int		i;
	int		k;
	char	*room;

	i = lemin->first_room;
	while (i >= 0)
	{
		lemin->lenght_path++;
		i--;
	}
	i = lemin->first_room;
	lemin->final_path = (char**)malloc(sizeof(char*)\
												* (lemin->lenght_path + 1));
	k = 0;
	while (i >= 0)
	{
		room = find_room_name(queue, lemin->path[i]);
		lemin->final_path[k] = ft_strdup(room);
		k++;
		i--;
	}
	lemin->final_path[k] = NULL;
}

static	int		help_find_path(t_lemin *lemin, t_queue *queue)
{
	int	i;
	int	end;

	i = -1;
	lemin->path = (int*)malloc(sizeof(int) * queue->count);
	while (++i < queue->count)
		lemin->path[i] = 0;
	end = find_end_index(queue);
	return (end);
}

void			find_path(t_lemin *lemin, t_queue *queue)
{
	int i;
	int k;
	int weight;
	int end;
	int temp;

	end = help_find_path(lemin, queue);
	lemin->path[0] = end;
	k = 1;
	weight = lemin->distances[end];
	while (end > 0 && (i = -1))
		while (++i < queue->count)
			if (lemin->matrix[end][i] > 0)
			{
				temp = weight - lemin->matrix[end][i];
				if (temp == lemin->distances[i])
				{
					weight = temp;
					end = i;
					lemin->path[k] = i;
					k++;
				}
			}
	lemin->first_room = k - 1;
	get_final_path(lemin, queue);
}

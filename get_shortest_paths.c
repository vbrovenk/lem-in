/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_shortest_paths.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbrovenk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/18 16:05:59 by vbrovenk          #+#    #+#             */
/*   Updated: 2018/08/18 16:06:00 by vbrovenk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

static	void	create_arrays(t_lemin *lemin, t_queue *queue)
{
	int i;
	int start_v;

	i = 0;
	lemin->visited = (int*)malloc(sizeof(int) * queue->count);
	lemin->distances = (int*)malloc(sizeof(int) * queue->count);
	while (i < queue->count)
	{
		lemin->visited[i] = 0;
		lemin->distances[i] = INFINITY;
		i++;
	}
	start_v = 0;
	lemin->distances[start_v] = 0;
}

static	int		help_shortest(t_lemin *lemin, t_queue *queue, int index)
{
	int min;
	int j;
	int k;

	min = INFINITY;
	j = -1;
	while (++j < queue->count)
	{
		if (lemin->visited[j] == 0 && lemin->distances[j] <= min)
		{
			min = lemin->distances[j];
			index = j;
		}
	}
	lemin->visited[index] = 1;
	k = -1;
	while (++k < queue->count)
	{
		if (lemin->visited[k] == 0 && lemin->matrix[index][k] == 1
		&& lemin->distances[index] != INFINITY &&
		lemin->distances[index] + lemin->matrix[index][k] < lemin->distances[k])
			lemin->distances[k] = lemin->distances[index] + \
			lemin->matrix[index][k];
	}
	return (index);
}

int				find_end_index(t_queue *queue)
{
	t_node *node;

	node = queue->head;
	while (node != NULL)
	{
		if (node->end == 1)
			return (node->index);
		node = node->next;
	}
	return (-1);
}

void			get_shortest_path(t_lemin *lemin, t_queue *queue)
{
	int i;
	int index;
	int end_index;

	create_arrays(lemin, queue);
	index = -1;
	i = -1;
	while (++i < queue->count)
	{
		index = help_shortest(lemin, queue, index);
	}
	end_index = find_end_index(queue);
	if (lemin->distances[end_index] == INFINITY)
	{
		ft_putstr("##END VERTEX IS NOT AVAILABLE FROM ##START\n");
		ft_error();
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   useful_func.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbrovenk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/18 16:48:34 by vbrovenk          #+#    #+#             */
/*   Updated: 2018/08/18 16:48:35 by vbrovenk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

void	join_str(t_lemin *lemin, char *line)
{
	char	*temp;

	temp = lemin->output;
	if (lemin->output != NULL)
		lemin->output = ft_strjoin(temp, "\n");
	ft_strdel(&temp);
	temp = lemin->output;
	lemin->output = ft_strjoin(temp, line);
	ft_strdel(&temp);
}

void	delete_split(char **split, int what_del)
{
	int i;

	if (what_del == DELETE_ROOM)
	{
		i = 1;
		while (split[i])
		{
			ft_strdel(&split[i]);
			i++;
		}
	}
	if (what_del == DELETE_LINK)
	{
		i = 0;
		while (split[i])
		{
			ft_strdel(&split[i]);
			i++;
		}
	}
	if (split != NULL)
		free(split);
}

char	*find_room_name(t_queue *queue, int index)
{
	t_node *temp;

	temp = queue->head;
	while (temp != NULL)
	{
		if (index == temp->index)
			return (temp->name);
		temp = temp->next;
	}
	return (NULL);
}

void	init_structs(t_lemin *lemin, t_queue *queue)
{
	lemin->output = NULL;
	lemin->count_ants = 0;
	lemin->count_start = 0;
	lemin->count_end = 0;
	lemin->flag_start = 0;
	lemin->flag_end = 0;
	lemin->matrix = NULL;
	lemin->distances = NULL;
	lemin->visited = NULL;
	lemin->path = NULL;
	lemin->first_room = 0;
	lemin->length_path = 0;
	lemin->final_path = NULL;
	queue->head = NULL;
	queue->tail = NULL;
	queue->count = 0;
}

void	make_matrix(t_queue *queue, t_lemin *lemin)
{
	int i;
	int j;

	i = -1;
	lemin->matrix = (int **)malloc(sizeof(int *) * queue->count);
	while (++i < queue->count)
		lemin->matrix[i] = (int *)malloc(sizeof(int) * queue->count);
	i = -1;
	while (++i < queue->count)
	{
		j = -1;
		while (++j < queue->count)
			lemin->matrix[i][j] = 0;
	}
}

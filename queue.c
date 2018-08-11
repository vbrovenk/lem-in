/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   queue.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbrovenk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/11 16:14:51 by vbrovenk          #+#    #+#             */
/*   Updated: 2018/08/11 16:14:53 by vbrovenk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

static  t_node  *create_node(char *line, t_lemin *lemin)
{
    t_node  *node;

    node = (t_node*)malloc(sizeof(t_node));
    node->name = line;
    node->next = NULL;
    if (lemin->flag_start == 1)
    {
        node->start = 1;
        lemin->flag_start = 0;
    }
    else
        node->start = 0;
    if (lemin->flag_end == 1)
    {
        node->end = 1;
        lemin->flag_end = 0;
    }
    else
        node->end = 0;
    if (node->end == 1 && node->start == 1)
        ft_error(lemin);
    return (node);
}

void    enqueue(t_queue *queue, char *line, t_lemin *lemin)
{
    if (queue->tail == NULL)
    {
        queue->tail = create_node(line, lemin);
        queue->head = queue->tail;
    }
    else
    {
        queue->tail->next = create_node(line, lemin);
        queue->tail = queue->tail->next;
    }
    queue->count++;
}
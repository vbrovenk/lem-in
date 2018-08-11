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

typedef struct  s_lemin{
    char *output;
    int count_ants;
    int count_start;
    int count_end;
    int flag_start;
    int flag_end;
    int **matrix;
}               t_lemin;

typedef struct  s_node
{
    int     index;
    char    *name;
    int     start;
    int     end;
    struct  s_node *next;
}               t_node;

typedef struct  s_queue
{
    t_node  *head;
    t_node  *tail;
    int     count;
}               t_queue;


void    enqueue(t_queue *queue, char *line, t_lemin *lemin);
void    ft_error(t_lemin *lemin);

#endif
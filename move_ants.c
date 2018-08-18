/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_ants.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbrovenk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/13 14:49:03 by vbrovenk          #+#    #+#             */
/*   Updated: 2018/08/13 14:49:05 by vbrovenk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"
#include <stdio.h>

void    add_ant(t_list_ants *list, int name_ant)
{
    t_ant   *ant;

    ant = (t_ant*)malloc(sizeof(t_ant));
    ant->name_ant = name_ant;
    ant->index_room = 1;
    ant->next = NULL;
    if (list->tail == NULL)
        list->head = list->tail = ant;
    else
    {
        list->tail->next = ant;
        list->tail = list->tail->next;
    }
}

int print_ants(t_list_ants *list, t_lemin *lemin)
{
    t_ant   *ant;
    int     flag_print;

    ant = list->head;
    flag_print = 0;
    while (ant != NULL)
    {
        if (ant->index_room < lemin->lenght_path)
        {
            ft_putchar('L');
            ft_putnbr(ant->name_ant);
            ft_putchar('-');
            ft_putstr(lemin->final_path[ant->index_room]);
            ft_putchar(' ');
            ant->index_room++;
            flag_print = 1;
        }
        ant = ant->next;
    }
    return (flag_print);
}

void    free_ants(t_list_ants *list)
{
    t_ant *ant;

    ant = list->head;
    while (ant != NULL)
    {
        free(ant);
        ant = ant->next;
    }
    free(list);
}

void    move_ants(t_lemin *lemin)
{
    t_list_ants *list;
    int         current_ant;
    int         ret;

    list = (t_list_ants*)malloc(sizeof(t_list_ants));
    list->head = list->tail = NULL;
    current_ant = 1;
    ret = 0;
    while (1)
    {
        if (current_ant <= lemin->count_ants)
        {
            add_ant(list, current_ant);
            current_ant++;
        }
        ret = print_ants(list, lemin);
        if (ret == 0)
            break ;
        else
            ft_putchar('\n');
    }
    free_ants(list);
}

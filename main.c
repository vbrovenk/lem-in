/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbrovenk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/02 16:17:57 by vbrovenk          #+#    #+#             */
/*   Updated: 2018/08/02 16:17:59 by vbrovenk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"
#include <stdio.h>

void    ft_error(t_lemin *lemin)
{
    printf("ERROR\n");
    ft_strdel(&lemin->output);
    exit(1);
}

void    print_struct(t_queue *queue)
{
    t_node *node;

    node = queue->head;
    while (node != NULL)
    {
        printf("node->name = %s | node->start = %d | node->end = %d | node->index = %d\n", node->name, node->start, node->end, node->index);
        node = node->next;
    }
    printf("Count of vertexes: %d\n", queue->count);
}

void    print_matrix(t_lemin *lemin, t_queue *queue)
{
    int x;
    int y;

    printf("\n====================\nMATRIX\n");
    x = 0;
    while (x < queue->count)
    {
        y = 0;
        while (y < queue->count)
        {
            printf("%d ", lemin->matrix[x][y]);
            y++;
        }
        printf("\n");
        x++;
    }
    printf("\n");
}

void    set_indexes(t_queue *queue)
{
    t_node  *temp;
    int     i;

    i = 1;
    temp = queue->head;
    while (temp != NULL)
    {
        if (temp->start == 1)
            temp->index = 0;
        else
        {
            temp->index = i;
            i++;
        }
        temp = temp->next;
    }
}

void    check_ants(t_lemin *lemin)
{
    char *line;
    int i;

    get_next_line(0, &line);
    if (line == NULL)
        exit(1);
    i = -1;
    while (line[++i])
    {
        if (ft_isspace(line[i]))
            ;
        else if (!ft_isdigit(line[i]))
            ft_error(lemin);
    }
    lemin->count_ants = ft_atoi(line);
    if (lemin->count_ants == 0)
        ft_error(lemin);
    lemin->output = line;
}

void    join_str(t_lemin *lemin, char *line)
{
    char    *temp;

    temp = lemin->output;
    lemin->output = ft_strjoin(temp, "\n");
    ft_strdel(&temp);
    temp = lemin->output;
    lemin->output = ft_strjoin(temp, line);
    ft_strdel(&temp);

}

void    check_commands(char *line, t_lemin *lemin)
{
    if (ft_strcmp(line, "##start") == 0)
    {
        lemin->count_start++;
        lemin->flag_start = 1;
    }
    else if (ft_strcmp(line, "##end") == 0)
    {
        lemin->count_end++;
        lemin->flag_end = 1;
    }
    else if (line[0] != '#')
         ft_error(lemin);
    join_str(lemin, line);
}

void    delete_split(char **split)
{
    int i;

    i = 1;
    while (split[i])
    {
        ft_strdel(&split[i]);
        i++;
    }
    if (split != NULL)
        free(split);
}

void    get_room(char *line, t_lemin *lemin, t_queue *queue)
{
    char    **split;
    int     i;
    int     j;

    split = ft_strsplit(line, ' ');
    if (split[0][0] == 'L')
        ft_error(lemin);
    i = 1;
    while (split[i])
    {
        j = -1;
        while (split[i][++j])
            if (!ft_isdigit(split[i][j]))
                ft_error(lemin);
        i++;
    }
    if (i != 3)
        ft_error(lemin);
    enqueue(queue, split[0], lemin);
    join_str(lemin, line);
    delete_split(split);
}

char    *check_rooms(t_lemin *lemin, t_queue *queue)
{
    char    *line;

    while (get_next_line(0, &line) > 0 && ft_strchr(line, '-') == 0)
    {
        if (line[0] == '\0')
            ft_error(lemin);
        if (ft_strchr(line, '#'))
            check_commands(line, lemin);
        else
        {
            get_room(line, lemin, queue);
        }
        ft_strdel(&line);
    }
    if (lemin->count_start != 1 || lemin->count_end != 1)
        ft_error(lemin);
    return (line);
}

void    make_matrix(t_queue *queue, t_lemin *lemin)
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

void    fill_matrix(char *line, t_queue *queue, t_lemin *lemin)
{
    int     v1;
    int     v2;
    char    **split;
    int i;

    i = -1;
    while (line[++i])
        if (ft_isspace(line[i]))
            ft_error(lemin);
    split = ft_strsplit(line, '-');
    if (split[2] != NULL)
        ft_error(lemin);
}

void    init_structs(t_lemin *lemin, t_queue *queue)
{
    lemin->output = NULL;
    lemin->count_ants = 0;
    lemin->count_start = 0;
    lemin->count_end = 0;
    lemin->flag_start = 0;
    lemin->flag_end = 0;

    queue->head = NULL;
    queue->tail = NULL;
    queue->count = 0;
}

int main(void)
{
    t_lemin *lemin;
    t_queue *queue;
    char    *last_line;

    lemin = (t_lemin*)malloc(sizeof(t_lemin));
    queue = (t_queue*)malloc(sizeof(t_queue));
    init_structs(lemin, queue);
    check_ants(lemin);
    last_line = check_rooms(lemin, queue);

    set_indexes(queue);
    make_matrix(queue, lemin);
    fill_matrix(last_line, queue, lemin);
    printf("%s\n", lemin->output);
    print_struct(queue);
    
    // print_matrix(lemin, queue);
    // system("leaks lem-in");
    return (0);
}

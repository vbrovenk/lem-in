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

void    check_start_end(t_queue *queue, t_lemin *lemin)
{
    t_node  *temp;
    int     flag_start;
    int     flag_end;

    temp = queue->head;
    flag_start = 0;
    flag_end = 0;
    while (temp != NULL)
    {
        if (temp->start == 1)
            flag_start = 1;
        if (temp->end == 1)
            flag_end = 1;
        temp = temp->next;
    }
    if (flag_end == 0 || flag_start == 0)
        ft_error(lemin);
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

void    delete_split(char **split, int what_del)
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
    delete_split(split, DELETE_ROOM);
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

int     find_index(t_queue *queue, char *name_vertex)
{
    t_node *node;

    node = queue->head;
    while (node != NULL)
    {
        if (ft_strcmp(node->name, name_vertex) == 0)
            return (node->index);
        node = node->next;
    }
    return (-1);
}

void    check_line(char *line, t_lemin *lemin)
{
    int i;

    if (ft_strchr(line, '-') == 0)
        ft_error(lemin);
    i = -1;
    while (line[++i])
        if (ft_isspace(line[i]))
            ft_error(lemin);
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
    check_line(line, lemin);
    split = ft_strsplit(line, '-');
    if (split[2] != NULL)
        ft_error(lemin);
    v1 = find_index(queue, split[0]);
    v2 = find_index(queue, split[1]);
    if (v1 != -1 && v2 != -1)
        lemin->matrix[v1][v2] = lemin->matrix[v2][v1] = 1;
    delete_split(split, DELETE_LINK);
    join_str(lemin, line);
    ft_strdel(&line);
    while (get_next_line(0, &line) > 0)
    {
        check_line(line, lemin);
        split = ft_strsplit(line, '-');
        if (split[2] != NULL)
            ft_error(lemin);
        v1 = find_index(queue, split[0]);
        v2 = find_index(queue, split[1]);
        if (v1 != -1 && v2 != -1)
            lemin->matrix[v1][v2] = lemin->matrix[v2][v1] = 1;
        delete_split(split, DELETE_LINK);
        join_str(lemin, line);
        ft_strdel(&line);
    }
}

void    create_arrays(t_lemin *lemin, t_queue *queue)
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

int    help_shortest(t_lemin *lemin, t_queue *queue, int index)
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
        lemin->distances[k] = lemin->distances[index] + lemin->matrix[index][k];
    }
    return (index);
}

int     find_end_index(t_queue *queue)
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

void    get_shortest_path(t_lemin *lemin, t_queue *queue)
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

    // for (int g = 0; g < queue->count; g++)
    // {
    //     printf("shortest path from 0 to %d = %d\n", g, lemin->distances[g]);
    // }
    end_index = find_end_index(queue);
    if (lemin->distances[end_index] == INFINITY)
    {
        printf("##END VERTEX IS NOT AVAILABLE FROM ##START\n");
        ft_error(lemin);
    }
}

char    *find_room_name(t_queue *queue, int index)
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

void    find_path(t_lemin *lemin, t_queue *queue)
{
    int i;
    int k;
    int weight;
    int end;
    int temp;

    i = -1;
    lemin->path = (int*)malloc(sizeof(int) * queue->count);
    while (++i < queue->count)
        lemin->path[i] = 0;
    end = find_end_index(queue);
    lemin->path[0] = end;
    k = 1;
    weight = lemin->distances[end];
    while (end > 0)
    {
        i = -1;
        while (++i < queue->count)
        {
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
        }
    }
    lemin->last_index = k - 1;
    for (int i = k - 1; i >= 0; i--)
    {
        // printf("%d", lemin->path[i]);
        printf("%s", find_room_name(queue, lemin->path[i]));
        if (i != 0)
            printf("->");
        lemin->lenght_path++;
    }
    printf("\n");
}

void    move_ants(t_lemin *lemin, t_queue *queue)
{
    int ants;
    int i;
    int j;
    int index;

    i = 1;
    j = 0;
    index = lemin->last_index;
    ants = lemin->count_ants;
    while (ants > 0)
    {
        
    }
    

}

void    init_structs(t_lemin *lemin, t_queue *queue)
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
    lemin->last_index = 0;
    lemin->lenght_path = 0;

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
    check_start_end(queue, lemin);
    make_matrix(queue, lemin);
    fill_matrix(last_line, queue, lemin);
    // print_struct(queue);
    
    get_shortest_path(lemin, queue);
    printf("%s\n\n", lemin->output);
    find_path(lemin, queue);

    move_ants(lemin, queue);
    // print_matrix(lemin, queue);
    // system("leaks lem-in");
    return (0);
}

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

void	ft_error(t_lemin *lemin)
{
	printf("ERROR\n");
	ft_strdel(&lemin->output);
	exit(1);
}

void	check_ants(t_lemin *lemin)
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

void	join_str(t_lemin *lemin, char *line)
{
	char	*temp;

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

// void    find_path(t_lemin *lemin, t_queue *queue)
// {
//     int i;
//     int k;
//     int weight;
//     int end;
//     int temp;

//     i = -1;
//     lemin->path = (int*)malloc(sizeof(int) * queue->count);
//     while (++i < queue->count)
//         lemin->path[i] = 0;
//     end = find_end_index(queue);
//     lemin->path[0] = end;
//     k = 1;
//     weight = lemin->distances[end];
//     while (end > 0)
//     {
//         i = -1;
//         while (++i < queue->count)
//         {
//             if (lemin->matrix[end][i] > 0)
//             {
//                 temp = weight - lemin->matrix[end][i];
//                 if (temp == lemin->distances[i])
//                 {
//                     weight = temp;
//                     end = i;
//                     lemin->path[k] = i;
//                     k++;
//                 }
//             }
//         }
//     }
//     lemin->first_room = k - 1;
//     for (int i = k - 1; i >= 0; i--)
//     {
//         // printf("%d", lemin->path[i]);
//         printf("%s", find_room_name(queue, lemin->path[i]));
//         if (i != 0)
//             printf("->");
//         lemin->lenght_path++;
//     }

//     int m = k - 1;
//     lemin->final_path = (char **)malloc(sizeof(char *) * (lemin->lenght_path) + 1);
//     int d = 0;
//     char *str;
//     while (m >= 0)
//     {
//         str = find_room_name(queue, lemin->path[m]);
//         lemin->final_path[d] = ft_strdup(str);
//         d++;
//         m--;
//     }
//     lemin->final_path[d] = NULL;
//     printf("\n");
// }

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
    lemin->first_room = 0;
    lemin->lenght_path = 0;

    lemin->final_path = NULL;

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
    
    get_shortest_path(lemin, queue);
    // printf("%s\n\n", lemin->output);
    ft_putstr(lemin->output);
    ft_putchar('\n');
    ft_putchar('\n');
    find_path(lemin, queue);

    move_ants(lemin);
    // print_matrix(lemin, queue);
    // system("leaks lem-in");
    return (0);
}

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
    lemin->first_room = k - 1;
    for (int i = k - 1; i >= 0; i--)
    {
        printf("%d", lemin->path[i]);
        printf("%s", find_room_name(queue, lemin->path[i]));
        if (i != 0)
            printf("->");
        lemin->lenght_path++;
    }

    int m = k - 1;
    lemin->final_path = (char **)malloc(sizeof(char *) * (lemin->lenght_path) + 1);
    int d = 0;
    char *str;
    while (m >= 0)
    {
        str = find_room_name(queue, lemin->path[m]);
        lemin->final_path[d] = ft_strdup(str);
        d++;
        m--;
    }
    lemin->final_path[d] = NULL;
}

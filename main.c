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
    // ft_strdel(&line);
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
        lemin->count_start++;
    else if (ft_strcmp(line, "##end") == 0)
        lemin->count_end++;
    else if (line[0] != '#')
        ft_error(lemin);
    join_str(lemin, line);
}

void    check_rooms(t_lemin *lemin)
{
    char    *line;
    char    **split;
    

    int i;
    int j;

    while (get_next_line(0, &line) > 0 && !ft_strchr(line, '-'))
    {
        if (line[0] == '\0')
            ft_error(lemin);
        if (ft_strchr(line, '#'))
            check_commands(line, lemin);
        else
        {
            split = ft_strsplit(line, ' ');
            if (split[0][0] == 'L')
                ft_error(lemin);
            i = 0;
            while (split[++i])
            {
                j = -1;
                while (split[i][++j])
                    if (!ft_isdigit(split[i][j]))
                        ft_error(lemin);
            }
            join_str(lemin, line);
            i = -1;
            while (split[++i])
                ft_strdel(&split[i]);
            if (split != NULL)
                free(split);
            if (i != 3)
                ft_error(lemin);
        }
        ft_strdel(&line);
    }
    if (lemin->count_start != 1 || lemin->count_end != 1)
        ft_error(lemin);
}

void    init_lemin(t_lemin *lemin)
{
    lemin->output = NULL;
    lemin->count_ants = 0;
    lemin->count_start = 0;
    lemin->count_end = 0;
}

int main(void)
{
    t_lemin *lemin;

    lemin = (t_lemin*)malloc(sizeof(t_lemin));
    init_lemin(lemin);
    check_ants(lemin);
    check_rooms(lemin);

    printf("%s\n", lemin->output);
    // system("leaks lem-in");
    printf("test\n");
    return (0);
}

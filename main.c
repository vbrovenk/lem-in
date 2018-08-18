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

void	check_ants(t_lemin *lemin)
{
	char	*line;
	int		i;

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

void	check_commands(char *line, t_lemin *lemin)
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

void	get_room(char *line, t_lemin *lemin, t_queue *queue)
{
	char	**split;
	int		i;
	int		j;

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

char	*check_rooms(t_lemin *lemin, t_queue *queue)
{
	char	*line;

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

int		main(void)
{
	// ОБРАБОТАТЬ ОДИНАКОВЫЕ НАЗВАНИЯ КОМНАТ
	t_lemin *lemin;
	t_queue *queue;
	char	*last_line;

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
	ft_putstr(lemin->output);
	ft_putchar('\n');
	ft_putchar('\n');
	find_path(lemin, queue);
	move_ants(lemin);
	// system("leaks lem-in");
	return (0);
}

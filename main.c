/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbrovenk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/02 16:17:57 by vbrovenk          #+#    #+#             */
/*   Updated: 2018/08/19 14:31:59 by vbrovenk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

void	check_ants(t_lemin *lemin)
{
	char	*line;
	int		i;

	get_next_line(0, &line);
	if (line == NULL)
		ft_error();
	i = -1;
	while (line[++i])
	{
		if (ft_isspace(line[i]))
			ft_error();
		else if (!ft_isdigit(line[i]))
			ft_error();
	}
	lemin->count_ants = ft_atoi(line);
	if (lemin->count_ants <= 0)
		ft_error();
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
		ft_error();
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
				ft_error();
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
			ft_error();
		if (ft_strchr(line, '#'))
			check_commands(line, lemin);
		else
		{
			if (ft_isspace(line[0]) == 1)
			{
				// ft_putstr("ROOM HAS SPACES IN NAME\n");
				ft_error();
			}
			get_room(line, lemin, queue);
		}
		ft_strdel(&line);
	}
	if (lemin->count_start != 1 || lemin->count_end != 1)
		ft_error();
	return (line);
}

// вопрос про пустые строки в конце карты
int		main(void)
{
	t_lemin *lemin;
	t_queue *queue;
	char	*last_line;

	lemin = (t_lemin*)malloc(sizeof(t_lemin));
	queue = (t_queue*)malloc(sizeof(t_queue));
	init_structs(lemin, queue);
	check_ants(lemin);
	last_line = check_rooms(lemin, queue);
	check_same_rooms(queue);
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
	return (0);
}

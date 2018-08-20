/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbrovenk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/18 14:41:10 by vbrovenk          #+#    #+#             */
/*   Updated: 2018/08/18 14:41:11 by vbrovenk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

static	void	input_link(t_lemin *lemin, int v1, int v2)
{
	lemin->matrix[v1][v2] = 1;
	lemin->matrix[v2][v1] = 1;
}

static	void	join_and_del(t_lemin *lemin, char *line)
{
	join_str(lemin, line);
	ft_strdel(&line);
}

static	void	help_fill(t_queue *queue, t_lemin *lemin,
									char *line, char **split)
{
	int v1;
	int v2;

	while (get_next_line(0, &line) > 0)
		if (line[0] == '#')
			join_and_del(lemin, line);
		else
		{
			if (check_line(line) == 1)
				return ;
			split = ft_strsplit(line, '-');
			if (check_split(split, line) == 1)
				return ;
			if (check_name_rooms(split, line, queue) == 0)
				return ;
			v1 = find_index(queue, split[0]);
			v2 = find_index(queue, split[1]);
			if (v1 != -1 && v2 != -1)
				input_link(lemin, v1, v2);
			delete_split(split, DELETE_LINK);
			join_str(lemin, line);
			ft_strdel(&line);
		}
}

void			fill_matrix(char *line, t_queue *queue, t_lemin *lemin)
{
	int		v1;
	int		v2;
	char	**split;
	int		i;

	i = -1;
	if (line == NULL)
		ft_error(lemin);
	if (check_line(line) == 1)
		return ;
	split = ft_strsplit(line, '-');
	if (check_split(split, line) == 1)
		return ;
	if (check_name_rooms(split, line, queue) == 0)
		return ;
	v1 = find_index(queue, split[0]);
	v2 = find_index(queue, split[1]);
	if (v1 != -1 && v2 != -1)
		input_link(lemin, v1, v2);
	delete_split(split, DELETE_LINK);
	join_and_del(lemin, line);
	help_fill(queue, lemin, line, split);
}

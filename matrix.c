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
#include <stdio.h>

static	void	check_line(char *line, t_lemin *lemin)
{
	int i;

	if (ft_strchr(line, '-') == 0)
		ft_error(lemin);
	i = -1;
	while (line[++i])
		if (ft_isspace(line[i]))
			ft_error(lemin);
}

static	void	input_link(t_lemin *lemin, int v1, int v2)
{
	lemin->matrix[v1][v2] = 1;
	lemin->matrix[v2][v1] = 1;
}

static	void	check_split(char **split, t_lemin *lemin)
{
	int	i;

	i = 0;
	while (split[i] != NULL)
		i++;
	if (i != 2)
		ft_error(lemin);
}

static	void	help_fill(t_queue *queue, t_lemin *lemin,
									char *line, char **split)
{
	int v1;
	int v2;

	while (get_next_line(0, &line) > 0)
	{
		if (line[0] == '#')
		{
			join_str(lemin, line);
			ft_strdel(&line);
		}
		else
		{
			check_line(line, lemin);
			split = ft_strsplit(line, '-');
			// if (split[2] != NULL)
			// 	ft_error(lemin);
			check_split(split, lemin);
			v1 = find_index(queue, split[0]);
			v2 = find_index(queue, split[1]);
			if (v1 != -1 && v2 != -1)
				input_link(lemin, v1, v2);
			delete_split(split, DELETE_LINK);
			join_str(lemin, line);
			ft_strdel(&line);
		}
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
	while (line[++i])
		if (ft_isspace(line[i]))
			ft_error(lemin);
	check_line(line, lemin);
	split = ft_strsplit(line, '-');
	// if (split[2] != NULL)
		// ft_error(lemin);
	check_split(split, lemin);
	v1 = find_index(queue, split[0]);
	v2 = find_index(queue, split[1]);
	if (v1 != -1 && v2 != -1)
		input_link(lemin, v1, v2);
	delete_split(split, DELETE_LINK);
	join_str(lemin, line);
	ft_strdel(&line);
	help_fill(queue, lemin, line, split);
}

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

static	void	add_ant(t_list_ants *list, int name_ant)
{
	t_ant	*ant;

	ant = (t_ant*)malloc(sizeof(t_ant));
	ant->name_ant = name_ant;
	ant->index_room = 1;
	ant->next = NULL;
	if (list->tail == NULL)
	{
		list->head = ant;
		list->tail = ant;
	}
	else
	{
		list->tail->next = ant;
		list->tail = list->tail->next;
	}
}

static	int		print_ants(t_list_ants *list, t_lemin *lemin)
{
	t_ant	*ant;
	int		flag_print;

	ant = list->head;
	flag_print = 0;
	while (ant != NULL)
	{
		if (ant->index_room < lemin->length_path)
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

static	void	free_ants(t_list_ants *list)
{
	t_ant	*ant;

	ant = list->head;
	while (ant != NULL)
	{
		free(ant);
		ant = ant->next;
	}
	free(list);
}

void			move_ants(t_lemin *lemin)
{
	t_list_ants	*list;
	int			current_ant;
	int			ret;

	list = (t_list_ants*)malloc(sizeof(t_list_ants));
	list->head = NULL;
	list->tail = NULL;
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

void			move_ants_2_rooms(t_lemin *lemin)
{
	t_list_ants	*list;
	int			temp_ants;

	temp_ants = 1;
	list = (t_list_ants*)malloc(sizeof(t_list_ants));
	list->head = NULL;
	list->tail = NULL;
	while (temp_ants <= lemin->count_ants)
	{
		add_ant(list, temp_ants);
		temp_ants++;
	}
	print_ants(list, lemin);
	ft_putchar('\n');
	free_ants(list);
}

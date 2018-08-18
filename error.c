/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbrovenk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/18 16:54:12 by vbrovenk          #+#    #+#             */
/*   Updated: 2018/08/18 16:54:13 by vbrovenk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

void	ft_error(t_lemin *lemin)
{
	ft_putstr("ERROR\n");
	ft_strdel(&lemin->output);
	exit(1);
}

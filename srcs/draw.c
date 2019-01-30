/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zoulhafi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/28 21:41:46 by zoulhafi          #+#    #+#             */
/*   Updated: 2019/01/30 20:12:39 by zoulhafi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

void	draw_me(t_list *elem)
{
	t_arg	*arg;

	arg = (t_arg*)elem->content;
	tputs(tgoto(tgetstr("cm", NULL), arg->col, arg->row), 1, my_putchar);
	if (arg->selected == 1)
		ft_printf_fd(2, "\e[4m%-*s\e[24m ", arg->max, arg->name);
	else
		ft_printf_fd(2, "%-*s ", arg->max, arg->name);
	tputs(tgoto(tgetstr("cm", NULL), arg->col, arg->row), 1, my_putchar);
	//ft_printf_fd(2, "\e[7m%-*s\e[27m ", arg->max, arg->name);
}

void	draw_args(int nothing)
{
	(void)nothing;
	tputs(tgetstr("cl", NULL), 1, my_putchar);
	recalculate_args();
}

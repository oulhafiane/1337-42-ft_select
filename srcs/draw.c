/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zoulhafi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/28 21:41:46 by zoulhafi          #+#    #+#             */
/*   Updated: 2019/02/15 17:01:31 by zoulhafi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

/*
**	this functions called from update_coordinates
**	it's simple it draws the argument on the screen
**	with its appropriate coordinates
*/

void	draw_me(t_list *elem)
{
	t_arg	*arg;

	arg = (t_arg*)elem->content;
	tputs(tgoto(tgetstr("cm", NULL), arg->col, arg->row), 1, my_putchar);
	if (arg->cursoron == CURSORON && arg->selected == SELECTED)
		ft_printf_fd(2, "\e[7m\e[4m%-*s\e[24m\e[27m ", arg->max, arg->name);
	else if (arg->cursoron == CURSORON)
		ft_printf_fd(2, "\e[4m%-*s\e[24m ", arg->max, arg->name);
	else if (arg->selected == SELECTED)
		ft_printf_fd(2, "\e[7m%-*s\e[27m ", arg->max, arg->name);
	else
		ft_printf_fd(2, "%-*s ", arg->max, arg->name);
	tputs(tgoto(tgetstr("cm", NULL), arg->col, arg->row), 1, my_putchar);
}

/*
**	draw all arguments stored in the static list
**	we achieve that by calling recalculate_args
**  why we use this function instead of calling recalculate_args directly ?
**	because we need to add a handler to the event SIGWINCH
**	28    SIGWINCH     discard signal       Window size change
**	and the prototype of handler must be like that : void func(int)
**	for more informations check the man : man signal
*/

void	draw_args(int nothing)
{
	t_point	ws;

	(void)nothing;
	tputs(tgetstr("cl", NULL), 1, my_putchar);
	set_window_size(&ws);
	recalculate_args(ws);
}

/*
**	function called from recalculate_args
**	that check clear the screen and print a msg on the screen
**	it was called because the windows size not enough to print all aguments.
*/

void	not_enough(t_list *lst, t_point ws)
{
	t_arg	*arg;
	char	flag;

	flag = 0;
	while (lst)
	{
		arg = (t_arg*)lst->content;
		if (arg->col + arg->max >= ws.col)
		{
			flag = 1;
			break ;
		}
		lst = lst->next;
	}
	if (flag)
	{
		tputs(tgetstr("cl", NULL), 1, my_putchar);
		if (ws.row >= 1 && ws.col >= 47)
			ft_printf_fd(2, "Window size not enough to print all arguments.");
		else if (ws.row >= 1 && ws.col >= 19)
			ft_printf_fd(2, "Windows size small.");
		else if (ws.row >= 1 && ws.col >= 9)
			ft_printf_fd(2, "WS small.");
		tputs(tgoto(tgetstr("cm", NULL), 0, 0), 1, my_putchar);
	}
}

/*
**	this function used to get the current windows size
**	before i was using ioctl(0, TIOCGWINSZ, &ws)
**	but it seems not working when calling the program with BackQuotes
**	like this : ls -l `./ft_select *`
*/

void	set_window_size(t_point *wins)
{
	struct winsize	ws;

	if (init_terms() != -1)
	{
		wins->row = tgetnum("li");
		wins->col = tgetnum("co");
	}
	else
	{
		ioctl(0, TIOCGWINSZ, &ws);
		wins->row = ws.ws_row;
		wins->col = ws.ws_col;
	}
}

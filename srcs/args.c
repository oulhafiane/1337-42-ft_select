/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zoulhafi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/28 18:59:31 by zoulhafi          #+#    #+#             */
/*   Updated: 2019/02/15 17:03:26 by zoulhafi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

/*
**	it's the function that store a static pointer
**	of the list which have all arguments
**	it returns the address of this pointer.
*/

static t_list	**get_args_list(void)
{
	static t_list	*args = NULL;

	return (&args);
}

/*
**	it's called when the program started
**	to add all arguments given to a static list
*/

void			init_args(int ac, char **av)
{
	t_list		**lst;

	lst = get_args_list();
	while (ac > 0)
	{
		add_arg(lst, av[ac - 1]);
		ac--;
	}
}

/*
**	it is called when the program stops
**	to release all the memory stored on the heap.
*/

void			free_args(char print)
{
	t_list	**lst;

	lst = get_args_list();
	if (print == 1)
		ft_lstiter(*lst, &print_selected);
	ft_lstdel(lst, &remove_arg);
}

/*
**	it's called by draw_args function,
**	when the program just started or the windows size changed.
**	it calculates the coordinates of each argument.
**	and draw each argument by calling update_coordinates.
*/

void			recalculate_args(t_point ws)
{
	t_list			*lst;
	t_arg			*arg;
	t_point			coords;
	size_t			max;

	if ((lst = *get_args_list()) == NULL)
		return ;
	arg = NULL;
	coords.row = -1;
	coords.col = 0;
	max = get_max_width(lst, ws.row);
	while (lst)
	{
		if (++(coords.row) >= ws.row)
		{
			coords.row = 0;
			coords.col += max + 1;
			max = get_max_width(lst, ws.row);
		}
		update_coordinates(lst, &arg, coords, max);
		lst = lst->next;
	}
	tputs(tgoto(tgetstr("cm", NULL), arg->col, arg->row), 1, my_putchar);
	not_enough(*get_args_list(), ws);
}

/*
**	it will select or delete or move the cursor or stop the program
**	or return the selected values,
**	according to the given instruction.
*/

void			update_cursor(char direction)
{
	t_list	**lst;

	lst = get_args_list();
	if (*lst == NULL && direction == DIR_DEL)
	{
		terms_handler(1);
		exit(0);
	}
	else if (*lst == NULL && direction != DIR_DEL && direction != DIR_RETURN)
		return ;
	if (direction == DIR_ADD)
		select_current_arg(*lst);
	else if (direction == DIR_DEL)
		delete_current_arg(lst);
	else if (direction == DIR_RETURN)
	{
		terms_handler(2);
		exit(0);
	}
	else
		move_cursor(*lst, direction);
}

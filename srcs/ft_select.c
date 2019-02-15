/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_select.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zoulhafi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/28 13:03:15 by zoulhafi          #+#    #+#             */
/*   Updated: 2019/02/15 15:36:36 by zoulhafi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

/*
**	it filters the given character between different instructions
**	and sends the appropriate flag to update_cursor
*/

static void	update_args(int buff)
{
	if (buff == UP_KEY)
		update_cursor(DIR_UP);
	else if (buff == DOWN_KEY)
		update_cursor(DIR_DOWN);
	else if (buff == RIGHT_KEY)
		update_cursor(DIR_RIGHT);
	else if (buff == LEFT_KEY)
		update_cursor(DIR_LEFT);
	else if (buff == SPACE_KEY)
		update_cursor(DIR_ADD);
	else if (buff == DEL_KEY || buff == BACK_KEY)
		update_cursor(DIR_DEL);
	else if (buff == RETURN_KEY)
		update_cursor(DIR_RETURN);
}

int			my_putchar(int c)
{
	write(2, &c, 1);
	return (1);
}

/*
**	this functions needed by recalculate_args function
**	to get the maximum width of all arguments on the same column.
*/

size_t		get_max_width(t_list *lst, size_t len_rows)
{
	t_arg	*arg;
	size_t	i;
	size_t	len;
	size_t	max;

	max = 0;
	i = 0;
	while (lst && i < len_rows)
	{
		arg = (t_arg*)lst->content;
		len = ft_strlen(arg->name);
		if (max < len)
			max = len;
		i++;
		lst = lst->next;
	}
	return (max + 1);
}

/*
**	it's a function called when the user press ENTER key
**	this function will be called from the libft function : ft_lstiter
**	it will print the argument given,
**	and space if there is more argument selected.
*/

void		print_selected(t_list *elem)
{
	t_arg	*arg;

	arg = (t_arg*)elem->content;
	if (arg->selected == SELECTED)
	{
		ft_printf("%s", arg->name);
		elem = elem->next;
		while (elem)
		{
			arg = (t_arg*)elem->content;
			if (arg->selected == SELECTED)
				break ;
			elem = elem->next;
		}
		if (elem != NULL)
			ft_printf(" ");
	}
}

/*
**	the main function, after initializing the terminal variables,
**	reads a character of the keyboard in a loop and gives it to
**	the update_args function, if it is an expected instruction
*/

int			main(int ac, char **av)
{
	int				buff;

	if (terms_handler(0) == -1)
		return (-1);
	init_args(ac - 1, av + 1);
	draw_args(1);
	buff = 0;
	while (read(0, &buff, 4) != 0)
	{
		if (buff == ESC_KEY)
			break ;
		else
			update_args(buff);
		buff = 0;
	}
	terms_handler(1);
	return (0);
}

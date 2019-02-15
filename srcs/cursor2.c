/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cursor2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zoulhafi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/01 12:29:13 by zoulhafi          #+#    #+#             */
/*   Updated: 2019/02/15 18:31:53 by zoulhafi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

/*
**	it's called from init_args when the program started
**	it creates a new structure t_arg and fills its name with the name given
**	and the other variables with 0.
*/

void	add_arg(t_list **lst, char *name)
{
	t_arg	*arg;

	arg = (t_arg*)ft_memalloc(sizeof(t_arg));
	arg->name = ft_strdup(name);
	arg->row = 0;
	arg->col = 0;
	arg->max = 0;
	if (*lst != NULL)
		((t_arg*)(*lst)->content)->cursoron = NOTHING;
	ft_lstadd(lst, ft_lstnew(arg, 0));
	((t_arg*)(*lst)->content)->cursoron = CURSORON;
}

/*
**	it's called from the libft functions :
**	ft_lstdelone or ft_lstdel
**	it releases the current space allocated by
**	the argument from the heap
*/

void	remove_arg(void *elem, size_t size)
{
	t_arg	*arg;

	(void)size;
	arg = elem;
	free(arg->name);
	free(arg);
}

/*
**	this function create just because of the norm of 42 curriculum
**	that need to be just 25 lines on the function
**	it's a complement of the recalculate_args function.
**	this function just updates the coordinate of the argument.
**	and draw it.
**	and check if the cursor is now on this argument
**	if it's will update the **arg given with the argument *elem
*/

void	update_coordinates(t_list *elem, t_arg **arg, t_point p, size_t max)
{
	((t_arg*)elem->content)->row = p.row;
	((t_arg*)elem->content)->col = p.col;
	((t_arg*)elem->content)->max = max;
	draw_me(elem);
	if (((t_arg*)elem->content)->cursoron == CURSORON)
		*arg = (t_arg*)elem->content;
}

/*
**	it's called from the update_cursor function
**	it will make the current argument where the cursor is now on
**	marked as selected.
*/

void	select_current_arg(t_list *lst)
{
	t_list	*current;
	t_list	*prev;
	t_arg	*arg;

	current = get_arg_cursoron(lst, &prev);
	arg = (t_arg*)current->content;
	arg->cursoron = NOTHING;
	if (arg->selected == SELECTED)
		arg->selected = NOTHING;
	else if (arg->selected == NOTHING)
		arg->selected = SELECTED;
	draw_me(current);
	if (current->next)
		current = current->next;
	else
		current = lst;
	arg = (t_arg*)current->content;
	arg->cursoron = CURSORON;
	draw_me(current);
}

/*
**	it's called from the update_cursor function
**	it will delete the current argument where the cursor is now on.
**	and release it from the heap.
*/

void	delete_current_arg(t_list **lst)
{
	t_point		ws;
	t_list		*current;
	t_list		*prev;

	prev = NULL;
	current = get_arg_cursoron(*lst, &prev);
	if (current == NULL)
		return ;
	if (prev != NULL)
		prev->next = current->next;
	else
		*lst = current->next;
	if (current->next)
		((t_arg*)current->next->content)->cursoron = CURSORON;
	else if (prev != NULL)
		((t_arg*)prev->content)->cursoron = CURSORON;
	set_window_size(&ws);
	tputs(tgetstr("cl", NULL), 1, my_putchar);
	recalculate_args(ws);
	if (prev == NULL && current->next == NULL)
		tputs(tgoto(tgetstr("cm", NULL), 0, 0), 1, my_putchar);
	ft_lstdelone(&current, &remove_arg);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cursor.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zoulhafi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/31 20:01:53 by zoulhafi          #+#    #+#             */
/*   Updated: 2019/02/15 17:03:25 by zoulhafi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

/*
**	it's called from the get_the_chosen function,
**	if the right arrow clicked.
**	this functions decides where the next cursor movement to the right.
*/

static t_list	*get_right_chosen(t_list *head, t_list *lst)
{
	t_list		*backup;
	t_point		ws;
	size_t		i;
	size_t		len;

	backup = lst;
	set_window_size(&ws);
	len = ft_lstlen(head);
	if (ws.row >= len)
		return (lst);
	i = -1;
	while (lst && ++i < ws.row)
		lst = lst->next;
	if (i == ws.row)
		return (lst);
	else
		return (backup);
}

/*
**	it's called from the get_the_chosen function,
**	if the left arrow clicked.
**	this functions decides where the next cursor movement to the left.
*/

static t_list	*get_left_chosen(t_list *head, t_list *lst)
{
	t_point		ws;
	size_t		len_head;
	size_t		len_current;
	size_t		to_achieve;
	size_t		i;

	set_window_size(&ws);
	len_head = ft_lstlen(head);
	if (ws.row >= len_head)
		return (lst);
	len_current = len_head - ft_lstlen(lst);
	to_achieve = len_current - ws.row;
	i = -1;
	if ((int)len_current - (int)ws.row < 0)
		return (lst);
	while (head && ++i < to_achieve)
		head = head->next;
	return (head);
}

/*
**	it's called from the below function called move_cursor
**	this function decides where the next cursor movement.
*/

static t_list	*get_the_chosen(t_list *head,
		t_list *current, t_list *prev, char direction)
{
	if (direction == DIR_DOWN && current->next != NULL)
		current = current->next;
	else if (direction == DIR_DOWN && current->next == NULL)
		current = head;
	else if (direction == DIR_UP && prev != NULL)
		current = prev;
	else if (direction == DIR_UP && prev == NULL)
	{
		while (current->next)
			current = current->next;
	}
	else if (direction == DIR_RIGHT)
		current = get_right_chosen(head, current);
	else if (direction == DIR_LEFT)
		current = get_left_chosen(head, current);
	return (current);
}

/*
**	it's called from the following functions:
**	select_current_arg
**	delete_current_arg
**	it returns the argument where the cursor is now on.
*/

t_list			*get_arg_cursoron(t_list *lst, t_list **prev)
{
	t_arg	*arg;

	while (lst)
	{
		arg = (t_arg*)lst->content;
		if (arg->cursoron == CURSORON)
			return (lst);
		*prev = lst;
		lst = lst->next;
	}
	return (NULL);
}

/*
**	it's called from update_cursor function
**	when a user click one of the arrow keys
**	it moves the cursor according the given arrow.
*/

void			move_cursor(t_list *lst, char direction)
{
	t_list	*prev;
	t_list	*current;

	prev = NULL;
	current = get_arg_cursoron(lst, &prev);
	if (current == NULL)
		return ;
	((t_arg*)current->content)->cursoron = NOTHING;
	draw_me(current);
	current = get_the_chosen(lst, current, prev, direction);
	((t_arg*)current->content)->cursoron = CURSORON;
	draw_me(current);
}

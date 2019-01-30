/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zoulhafi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/28 18:59:31 by zoulhafi          #+#    #+#             */
/*   Updated: 2019/01/30 21:59:18 by zoulhafi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

static t_list	**get_args_list(void)
{
	static t_list	*args = NULL;

	return (&args);
}

static void	add_arg(t_list **lst, char *name)
{
	t_arg	*arg;

	arg = (t_arg*)malloc(sizeof(t_arg));
	arg->name = ft_strdup(name);
	arg->row = 0;
	arg->col = 0;
	arg->max = 0;
	if (*lst == NULL)
		arg->selected = 1;
	else
		arg->selected = 0;
	ft_lstadd_end(lst, ft_lstnew(arg, 0));
}

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

void			recalculate_args(void)
{
	t_list			*lst;
	struct winsize	ws;
	size_t			i;
	size_t			j;
	int				max;

	ioctl(1, TIOCGWINSZ, &ws);
	lst = *get_args_list();
	i = -1;
	j = 0;
	max = get_max_width(lst, ws.ws_row);
	while (lst)
	{
		if (++i >= ws.ws_row)
		{
			i = 0;
			j += max + 1;
			max = get_max_width(lst, ws.ws_row);
		}
		((t_arg*)lst->content)->row = i;
		((t_arg*)lst->content)->col = j;
		((t_arg*)lst->content)->max = max;
		draw_me(lst);
		lst = lst->next;	
	}
}

void			update_cursor(char direction)
{
	t_list	*lst;
	t_list	*prev;
	t_arg	*arg;

	prev = NULL;
	lst = *get_args_list();
	while (lst)
	{
		arg = (t_arg*)lst->content;
		if (arg->selected == 1)
			break;
		prev = lst;
		lst = lst->next;
	}
	if (lst == NULL)
		return ;
	arg->selected = 0;
	draw_me(lst);
	if (direction == 0 && lst->next != NULL)
		lst = lst->next;
	else if (direction == 1 && prev != NULL)
		lst = prev;
	((t_arg*)lst->content)->selected = 1;
	draw_me(lst);
}

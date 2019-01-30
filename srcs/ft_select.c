/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_select.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zoulhafi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/28 13:03:15 by zoulhafi          #+#    #+#             */
/*   Updated: 2019/01/30 19:54:13 by zoulhafi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

int		my_putchar(int c)
{
	write(2, &c, 1);
	return (1);
}

size_t	get_max_width(t_list *lst, size_t len_rows)
{
	t_arg	*arg;
	size_t	max;
	size_t	i;
	size_t	len;

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


int		main(int ac, char **av)
{
	int				buff;

	if (terms_handler(0) == -1)
		return (-1);
	init_args(ac - 1, av + 1);
	draw_args(1);
	tputs(tgoto(tgetstr("cm", NULL), 0, 0), 1, my_putchar);
	while (read(0, &buff, 4) != 0)
	{
		if (buff == UP_KEY)
			update_cursor(1);
		else if (buff == DOWN_KEY)
			update_cursor(0);
		else if (buff == ESC_KEY)
			break ;
		buff = 0;
			//tputs(tgetstr("up", NULL), 1, my_putchar);
			//tputs(tgetstr("do", NULL), 1, my_putchar);
	}
	terms_handler(1);
	//to remove
	ft_printf("author");
	return (0);
}

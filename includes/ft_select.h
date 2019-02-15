/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_select.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zoulhafi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/26 15:29:59 by zoulhafi          #+#    #+#             */
/*   Updated: 2019/02/15 17:03:27 by zoulhafi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_SELECT_H
# define FT_SELECT_H
# include "const.h"
# include "libft.h"
# include <term.h>
# include <sys/ioctl.h>

typedef struct	s_arg
{
	char		*name;
	size_t		row;
	size_t		col;
	size_t		max;
	char		cursoron;
	char		selected;
}				t_arg;

typedef struct	s_point
{
	size_t		row;
	size_t		col;
}				t_point;

/*
**	ft_select.c
*/
int				my_putchar(int c);
size_t			get_max_width(t_list *lst, size_t len_rows);
void			print_selected(t_list *elem);

/*
**	init_terms.c
*/
int				init_terms(void);
int				terms_handler(char restore_to_default);

/*
**	args.c
*/
void			init_args(int ac, char **av);
void			free_args(char print);
void			recalculate_args(t_point ws);
void			update_cursor(char direction);

/*
**	draw.c
*/
void			draw_me(t_list *elem);
void			draw_args(int nothing);
void			not_enough(t_list *lst, t_point ws);
void			set_window_size(t_point *wins);

/*
**	cursor.c
*/
t_list			*get_arg_cursoron(t_list *lst, t_list **prev);
void			move_cursor(t_list *lst, char direction);

/*
**	cursor2.c
*/
void			add_arg(t_list **lst, char *name);
void			remove_arg(void *elem, size_t size);
void			update_coordinates(t_list *elem, t_arg **arg, t_point p,
		size_t max);
void			select_current_arg(t_list *lst);
void			delete_current_arg(t_list **lst);

#endif

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_select.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zoulhafi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/26 15:29:59 by zoulhafi          #+#    #+#             */
/*   Updated: 2019/01/30 20:07:33 by zoulhafi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_SELECT_H
# define FT_SELECT_H
# define UP_KEY 4283163
# define DOWN_KEY 4348699
# define RIGHT_KEY 4414235
# define LEFT_KEY 4479771
# define ESC_KEY 27
# define SPACE_KEY 32
# define RETURN_KEY 10
# include "libft.h"
# include <term.h>
# include <sys/ioctl.h>

typedef struct	s_arg
{
	char		*name;
	size_t		row;
	size_t		col;
	size_t		max;
	char		selected;
}				t_arg;

int				my_putchar(int c);
size_t			get_max_width(t_list *lst, size_t len_rows);

void			exit_handler(int sig);
int				terms_handler(int restore_to_default);

void			init_args(int ac, char **av);
void			recalculate_args(void);
void			update_cursor(char direction);

void			draw_me(t_list *elem);
void			draw_args(int nothing);

#endif

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simple_com.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youjeong <youjeong@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 02:23:54 by youjeong          #+#    #+#             */
/*   Updated: 2023/08/10 02:12:17 by youjeong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "common/common.h"

void			init_simple_com(t_simple_com *simple_com);
t_simple_com	*get_simple_com(void);
void			clear_simple_com(t_simple_com *simple_com);
void			free_simple_com(t_simple_com *simple_com);

void	init_simple_com(t_simple_com *simple_com)
{
	simple_com->words = 0;
	simple_com->redirects = 0;
	simple_com->connection = 0;
}

t_simple_com	*get_simple_com(void)
{
	t_simple_com	*simple_com;

	simple_com = (t_simple_com *)malloc(sizeof(t_simple_com));
	if (!simple_com)
		crash(ENOMEM, 0);
	init_simple_com(simple_com);
	return (simple_com);
}

void	clear_simple_com(t_simple_com *simple_com)
{
	if (simple_com->words)
		free_word_list(simple_com->words);
	if (simple_com->redirects)
		free_redirect_list(simple_com->redirects);
	if (simple_com->connection)
		free_connection(simple_com->connection);
	init_simple_com(simple_com);
}

void	free_simple_com(t_simple_com *simple_com)
{
	clear_simple_com(simple_com);
	free(simple_com);
}
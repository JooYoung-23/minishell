/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youjeong <youjeong@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/09 15:20:39 by youjeong          #+#    #+#             */
/*   Updated: 2023/08/14 03:10:25 by youjeong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser/tokenize.h"
#include "parser/lex.h"
#include "libft.h"

t_lex_list				*lex(char *str);
static t_lex_list		*lex_token_list(t_token_list *token_list);
static void				add_word_to_lex_list(t_lex_list **lex_list, char *word);
static int				get_simple_com_flag(char *str);
static t_command_type	get_command_type(char *word);

t_lex_list	*lex(char *str)
{
	t_lex_list		*lex_list;
	t_token_list	*token_list;

	token_list = tokenize(str);
	lex_list = lex_token_list(token_list);
	free_token_list(token_list);
	return (lex_list);
}

static t_lex_list	*lex_token_list(t_token_list *token_list)
{
	t_lex_list		*lex_list;
	t_token_list	*pnode;
	char			*word;

	lex_list = 0;
	pnode = token_list;
	while (pnode)
	{
		word = pnode->word;
		add_word_to_lex_list(&lex_list, word);
		pnode = pnode->next;
	}
	return (lex_list);
}

static void	add_word_to_lex_list(t_lex_list **lex_list, char *word)
{
	t_lex_node	*lex_data;

	lex_data = get_lex_node();
	lex_data->word = ft_strdup(word);
	lex_data->type = get_command_type(word);
	if (lex_data->type == cm_simple)
		lex_data->flag = get_simple_com_flag(word);
	push_lex_list(lex_list, lex_data);
}

static int	get_simple_com_flag(char *str)
{
	int		flag;
	char	*substr;

	flag = 0;
	while (*str)
	{
		if (*str == '\'' && ft_strchr(str + 1, '\''))
		{
			flag |= W_QUOTED;
			str = ft_strchr(str + 1, '\'');
		}
		else if (*str == '\"' && ft_strchr(str + 1, '\"'))
		{
			substr = ft_substr(str, 0, ft_strchr(str + 1, '\"') - str);
			if (ft_strchr(substr, '$'))
				flag |= W_HASDOLLAR;
			flag |= W_DQUOTED;
			free(substr);
		}
		str++;
	}
	return (flag);
}

static t_command_type	get_command_type(char *word)
{
	t_command_type	type;

	if (*word == '|')
		type = cm_connection;
	else if (*word == '<' || *word == '>')
		type = cm_redirect;
	else
		type = cm_simple;
	return (type);
}

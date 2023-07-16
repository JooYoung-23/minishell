/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youjeong <youjeong@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/04 20:16:15 by youjeong          #+#    #+#             */
/*   Updated: 2023/07/14 12:19:28 by youjeong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/type.h"

t_node	*getnode(t_token *data);
void	free_node(t_node *node);

t_node	*getnode(t_token *data)
{
	t_node	*new_node;

	new_node = 0;
	new_node = (t_node *)malloc(1 * sizeof(t_node));
	if (!new_node)
		print_error(ENOMEM);
	new_node->parent = 0;
	new_node->left = 0;
	new_node->right = 0;
	new_node->data = data;
	return (new_node);
}

void	free_node(t_node *node)
{
	if (node->data)
		free_token(node->data);
	free(node);
}

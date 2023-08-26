/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bind_variable.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jy_23 <jy_23@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/11 18:22:00 by jy_23             #+#    #+#             */
/*   Updated: 2023/08/26 15:54:17 by jy_23            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "variables.h"
#include "hashlib.h"
#include "libft.h"
#include "utils.h"

t_variable			*bind_variable(char *name,
						char *value, t_hash_table *table, int flag);
static t_variable	*hash_lookup(char *key, t_hash_table *table);

t_variable	*bind_variable(char *name,
				char *value, t_hash_table *table, int flag)
{
	t_bucket_contents	*bucket;
	t_variable			*entry;
	char				*dup_name;
	char				*dup_value;

	entry = hash_lookup(name, table);
	dup_name = 0;
	dup_value = 0;
	if (name)
		dup_name = ft_xstrdup(name);
	if (value)
		dup_value = ft_xstrdup(value);
	if (!entry && flag == V_CREATE)
	{
		bucket = hash_insert(ft_xstrdup(name), table);
		entry = create_variable(dup_name, dup_value);
		bucket->data = (void *)entry;
	}
	else
	{
		if (entry)
		{
			free(entry->value);
			entry->value = dup_value;
		}
	}
	return (entry);
}

static t_variable	*hash_lookup(char *key, t_hash_table *table)
{
	t_bucket_contents	*bucket;

	bucket = hash_search(key, table);
	if (bucket)
		return ((t_variable *)bucket->data);
	else
		return (0);
}

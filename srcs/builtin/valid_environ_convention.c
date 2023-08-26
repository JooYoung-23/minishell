/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid_environ_convention.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jy_23 <jy_23@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/26 16:47:05 by jy_23             #+#    #+#             */
/*   Updated: 2023/08/26 18:49:12 by jy_23            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "status.h"
#include "libft.h"

int	valid_environ_convention(char *cmd, char *key);

int	valid_environ_convention(char *cmd, char *key)
{
	if (*key == '=')
		return (exception_handler(EGENRAL, cmd, key, INVARG));
	while (*key)
	{
		if (*key == '=')
			break ;
		else if (!(ft_isalnum(*key) || *key == '_'))
			return (exception_handler(EGENRAL, cmd, key, INVARG));
		key++;
	}
	return (SUCCESS);
}

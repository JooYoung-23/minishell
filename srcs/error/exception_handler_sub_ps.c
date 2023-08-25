/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exception_handler_sub_ps.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jy_23 <jy_23@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/24 05:33:32 by jy_23             #+#    #+#             */
/*   Updated: 2023/08/24 05:35:18 by jy_23            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "status.h"

extern int	g_status;

void	exception_handler_sub_ps(int status, char *arg_str);

void	exception_handler_sub_ps(int status, char *arg_str)
{
	print_error_msg(status, arg_str);
	g_status = status;
	exit(g_status);
}
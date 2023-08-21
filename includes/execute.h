/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jy_23 <jy_23@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 18:15:59 by youjeong          #+#    #+#             */
/*   Updated: 2023/08/21 20:40:57 by jy_23            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTE_H
# define EXECUTE_H

# include "command.h"
# include "builtin.h"
# include "variables.h"

# define ERROR -1
# define ENOCMD 127

int	execute_command(t_command *command, t_environment *environ);
int	execute_command_internal(t_command *command, t_environment *environ, int pre_in, int pre_out);
int	execute_connection_command(t_command *command, t_environment *environ, int pre_in, int pre_out);
int	execute_simple_command(t_command *command, t_environment *environ, int pipe_in_fd, int pipe_out_fd);
int	do_redirect(t_redirect_list *redirects);
void	undo_redirect(int save_stdin_fd, int save_stdout_fd);

#endif

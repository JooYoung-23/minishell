/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youjeong <youjeong@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 17:50:50 by youjeong          #+#    #+#             */
/*   Updated: 2023/08/21 21:07:59 by youjeong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "minishell.h"
#include <termios.h>
#include <term.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "minishell.h"
#include "variables.h"
#include "execute.h"

int	g_status;

int		main(int argc, char *args[], char **environment);
void	reader_loop(char **environ);

int	main(int argc, char *args[], char **environment)
{
	(void)argc;
	(void)args;
	
	initialize();
	reader_loop(environment);
	return (0);
}

void	reader_loop(char **initial_environ)
{
	char	*str;
	t_command	*command;
	t_environment *environ;

	environ = create_environmet_variable(initial_environ);

	while (1)
	{
		// read
		str = readline("minshell-3.2$ ");
		if (rl_eof_found)
		{
			printf("exit\n");
			exit(0);
		}
		add_history(str);
		// parse
		command = parse(str);
		// execute
		free(str);
		execute_command(command, environ);
		if (command)
			free_command(command);
	}
}


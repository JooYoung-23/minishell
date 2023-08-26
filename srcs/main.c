/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jy_23 <jy_23@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 19:50:40 by jy_23             #+#    #+#             */
/*   Updated: 2023/08/26 19:52:48 by jy_23            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "minishell.h"
#include <termios.h>
#include <term.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "variables.h"
#include "execute.h"
#include "initialize.h"
#include "parse/parse.h"


int			main(int argc, char *args[], char **environment);
static void	reader_loop();
static char	*sh_readline(void);

/* leaks check */
void	check_leaks(void)
{
	system("leaks minishell");
}

int	main(int argc, char *args[], char **environment)
{
	(void)argc;
	(void)args;

	/* leaks check */
	//atexit(check_leaks);

	initialize(environment);
	reader_loop();
	clear_sh_variable();
	return (0);
}

static void	reader_loop()
{
	char		*str;
	t_command	*command;

	while (1)
	{
		initialize_shell_signals(0);
		str = sh_readline();
		initialize_shell_signals(1);
		if (!str)
			return ;
		command = parse(str);
		execute_command(command);
		free(str);
		if (command)
			free_command(command);
	}
}

static char	*sh_readline(void)
{
	char	*str;

	str = readline("minshell-3.2$ ");
	if (rl_eof_found)
	{
		printf("exit\n");
		return (0);
	}
	add_history(str);
	return (str);
}

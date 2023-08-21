/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youjeong <youjeong@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 17:50:50 by youjeong          #+#    #+#             */
/*   Updated: 2023/08/21 20:49:28 by youjeong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include <assert.h>
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "command.h"
#include "parser/tokenize.h"
#include "parser/lex.h"
#include "parser/parse.h"
#include "expand/expand.h"
#include "signal/sig_handler.h"

int		main(int argc, char *args[], char **environ);
void	intro();
void	reader_loop(char **environ);
void	type_test();
void	tokenize_test();
void	lex_test();
void	parse_test();
void	expander_test();
void	expand_words_test();
void	check_leaks();
void	setting_signal_test();

int	main(int argc, char *args[], char **environ) {
	char	*str;
	(void)argc;
	(void)args;

	atexit(check_leaks);
	intro();
	str = readline("test_type:");

	if (!strcmp(str, "reader") || !strcmp(str, "1"))
		reader_loop(environ);
	else if (!strcmp(str, "type") || !strcmp(str, "2"))
		type_test();
	else if (!strcmp(str, "token") || !strcmp(str, "3"))
		tokenize_test();
	else if (!strcmp(str, "lex") || !strcmp(str, "4"))
		lex_test();
	else if (!strcmp(str, "parse") || !strcmp(str, "5"))
		parse_test();
	else if (!strcmp(str, "epd") || !strcmp(str, "6"))
		expander_test();
	else if (!strcmp(str, "ex_words") || !strcmp(str, "7"))
		expand_words_test();
	else if (!strcmp(str, "signal") || !strcmp(str, "8"))
		setting_signal_test();	
	free(str);
	return (0);
}

void	intro() {
	printf("Introduce test_type\n");
	printf("1. reader : reader_loop test\n");
	printf("2. type : type test\n");
	printf("3. toekn : token test\n");
	printf("4. lex : lex test\n");
	printf("5. parse : parse test\n");
	printf("6. epd : expander test\n");
	printf("7. ex_words : expand words test\n");
	printf("8. signal : test of setting the signal\n");
}

void	reader_loop(char **environ) {
	char 		*str;

	(void)environ;
	while (1) {
		str = readline("test_shell:");
		printf("%s\n", str);
	}
}

static void word_desc_test();
static void	redirect_test();
static void	word_list_test();
static void redirect_list_test();
void	type_test() {
	word_desc_test();
	redirect_test();
	word_list_test();
	redirect_list_test();
	printf("type test completed!\n");
}

void	tokenize_test() {
	t_token_list	*tokened_list;
	t_token_list	*ptoken;

	char *str = readline("input one line: ");
	tokened_list = tokenize(str);
	ptoken = tokened_list;
	while (ptoken) {
		printf("%s\n", ptoken->word);
		ptoken = ptoken->next;
	}
	free(str);
	free_token_list(tokened_list);
}

void	lex_test() {
	t_lex_list	*lexed_list;
	t_lex_list	*plex;

	char *str = readline("input one line: ");
	lexed_list = lex(str);
	plex = lexed_list;
	while (plex) {
		printf("\n");
		printf("⎧word:\"%s\"\n", plex->data->word);
		printf("⎟type:\"%d\"\n", plex->data->type);
		printf("⎩flag:\"%d\"\n", plex->data->flag);
		printf("\n");
		plex = plex->next;
	}
	free(str);
	free_lex_list(lexed_list);
}

void	parse_test() {
	t_command	*res_parse;

	char *str = readline("input one line: ");

	res_parse = parse(str);

	// stop point
	free(str);
	if (res_parse)
		free_command(res_parse);
}

void	expander_test() {
	char	*res_epd;

	char *str = readline("input one line: ");

	res_epd = expand_str(str);

	printf("\n");
	printf(" [ expander result ]\n"); 
	printf("%s\n", res_epd);
	printf("\n");

	// stop point
	free(str);
	free(res_epd);
}

void	expand_words_test() {
	char *str = readline("input one line: ");
	t_command	*res_parse = parse(str);
	t_word_list *word_list = res_parse->simple->words;
	t_word_list	*expand_res = expand_words(word_list);
	
	t_word_list	*pword;
	pword = expand_res;
	while (pword) {
		printf("⎧word:\"%s\"\n", pword->word->word);
		printf("⎩flag:\"%d\"\n", pword->word->flag);
		pword = pword->next;
	}
	free_word_list(expand_res);
	free_command(res_parse);
	free(str);
}

void	setting_signal_test()
{
	char	*test;

	initialize_shell_signals();
	printf("test\n");
	while (1) 
	{
		test = readline("test shell$ ");
		if (test == 0)
			printf("ctrl d\n");
		else
		{
			add_history(test);
			if (strcmp(test, "stop") == 0)
			{
				free(test);
				break;
			}
			free(test);
		}
	}
}

static void word_desc_test() {
	t_word_desc	*word_desc;

	word_desc = get_word_desc();
	word_desc->word = strdup("word_desc_word");
	free_word_desc(word_desc);
}

static void	redirect_test() {
	t_redirect	*redirect;

	redirect = get_redirect();
	redirect->word = strdup("redirect_word");
	redirect->filename = strdup("redirect_filename");
	free_redirect(redirect);
}

static void word_list_test() {
	t_word_list	*word_list = 0;

	for (int i = 0; i < 10; i++) {
		t_word_desc	*word_desc;
		char word[15] = "wordlist_word ";
		
		word_desc = get_word_desc();
		word[13] = i + '0';
		word_desc->word = strdup(word);
		push_word_list(&word_list, word_desc);
	}
	free_word_list(word_list);
	word_list = 0;
	for (int i = 0; i < 10; i++) {
		t_word_desc	*word_desc;
		char word[15] = "wordlist_word ";
		
		word_desc = get_word_desc();
		word[13] = i + '0';
		word_desc->word = strdup(word);
		push_word_list(&word_list, word_desc);
	}
	for (int i = 0; i < 10; i++) {
		t_word_desc *word_desc;
		assert(word_desc = pop_word_list(&word_list));
		free_word_desc(word_desc);
	}
}

static void redirect_list_test() {
	t_redirect_list	*redirect_list = 0;

	for (int i = 0; i < 10; i++) {
		t_redirect	*redirect;
		char redirect_file[15] = "redirect_file ";
		char redirect_word[15] = "redirect_word ";
		
		redirect = get_redirect();
		redirect_file[13] = i + '0';
		redirect_word[13] = i + '0';
		redirect->filename = strdup(redirect_file);
		redirect->word = strdup(redirect_word);
		push_redirect_list(&redirect_list, redirect);
	}
	free_redirect_list(redirect_list);
	redirect_list = 0;
	for (int i = 0; i < 10; i++) {
		t_redirect	*redirect;
		char redirect_file[15] = "redirect_file ";
		char redirect_word[15] = "redirect_word ";
		
		redirect = get_redirect();
		redirect_file[13] = i + '0';
		redirect_word[13] = i + '0';
		redirect->filename = strdup(redirect_file);
		redirect->word = strdup(redirect_word);
		push_redirect_list(&redirect_list, redirect);
	}
	for (int i = 0; i < 10; i++) {
		t_redirect *redirect;
		assert(redirect = pop_redirect_list(&redirect_list));
		free_redirect(redirect);
	}
}

void	check_leaks() {
	system("leaks minishell");
}

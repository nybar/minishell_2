/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbach <bbach@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/02 22:15:31 by bbach             #+#    #+#             */
/*   Updated: 2023/12/04 12:52:48 by bbach            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINI_H
# define MINI_H

# include "./includes/libft/libft.h"
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <sys/wait.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <signal.h>
# include <readline/readline.h>
# include <readline/history.h>

# define SUCCESS 0
# define FAILURE 1
# define ERROR -1

typedef enum
{
	T_WORD,
	T_BAR,
	T_AMPER,
	T_LT,
	T_GT,
	T_GTGT,
	T_NL,
	T_EOF
} TOKEN;

typedef enum
{
	START,
	IN_WORD,
	IN_SINGLE_QUOTES,
	IN_DOUBLE_QUOTES,
	NO_QUOTES
} STATE;

typedef struct s_node
{
	char			*value;
	struct s_node	*next;
	char			**args;
	TOKEN			token;
	TOKEN			op_type;
	STATE			quote_state;
	struct s_node	*left;
	struct s_node	*right;
}		t_node;

typedef struct s_lst
{
	struct s_node	*head;
}		t_lst;

typedef struct s_lexer
{
	char	*line;
	char	quote_type;
	int		index;
	int		start;
	int		end;
	int		quote_start;
	int		quote_end;
	t_lst	*token_list;
	STATE	state;
	STATE	quotes;
}		t_lexer;

typedef struct s_input
{
    char    *line;
    int     i;
    int     count_double;
    int     count_single;
    int     in_double_quotes;
    int     in_single_quotes;
}           t_input;

typedef struct s_command
{
	char	**my_env;
	char	*name;
	char	**args;
}		t_command;


//
char	*get_command_path(char *command, char **env);
char	*find_command_path(char *command, char **env);

//parsing

t_lst    *tokenize_input(char *input_line);
t_lst	*lexer(char *line);

//parsing_utils

char	get_type(char c, t_lexer *lx);
char	*ft_strndup(char *str, int n);
t_node	*create_new_token(char *value, t_lexer *lexer);
TOKEN	determine_token_type(char *value);
void	add_token(t_lexer *lexer, char *token_value);
void	add_token_to_list(t_node **head, t_node *new_token);
char *ft_strcat(char *dest, const char *src);



//handle_quotes

void	process_quotes(t_lexer *lx);
void	process_no_quotes(t_lexer *lx);
void	tokenize_last_word(t_lexer *lx);

//get_any_env

char	**ft_strsplit(char *str, char c);
int    ft_strcmp(char *s1, char *s2);
char	**get_my_env(char **env);
char	*get_value_any_env(char **any_env, char *key);
void	ft_free_2d_array(char **array);

//init

void	init_lexer(t_lexer *lx, char *line);

//execution

char   *get_command_path(char *command, char **env);
char   *find_command_path(char *command, char **path);
void	execute_command(t_node *command, char **env);

#endif
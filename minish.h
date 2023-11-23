/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minish.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbach <bbach@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/18 10:58:48 by bbach             #+#    #+#             */
/*   Updated: 2023/11/18 16:32:41 by bbach            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISH_H
# define MINISH_H

# include "./includes/libft/libft.h"
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <sys/wait.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <sys/param.h>
# include <fcntl.h>
# include <signal.h>
# include <readline/readline.h>
# include <readline/history.h>

# define SUCCESS 0
# define FAILURE 1
# define ERROR -1

typedef struct s_minish
{
    char    *input;
}           t_minish;


// valid_input.c

int     valid_input(char *input);

// parsing.c

void    sort_input(t_minish *minish, char *input);
int     str_in_input(char *str);
char    *ft_strndup(char *s, int n);

#endif
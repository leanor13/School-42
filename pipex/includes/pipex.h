/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yioffe <yioffe@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 11:27:07 by yioffe            #+#    #+#             */
/*   Updated: 2024/03/10 13:25:45 by yioffe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "libft/libft.h"
# include <limits.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <fcntl.h>
# include <string.h>

# ifndef PATH_MAX
#  define PATH_MAX 256
# endif

# define CHILD_PID 0
# define NEG_ERROR -1
# define FD_IN 0
# define FD_OUT 1
# define PRINT_PIPE_ERROR true

# define WRONG_ARG_NUM "Wrong number of arguments. \
	Usage: ./pipex file1 cmd1 cmd2 file2\n"

typedef struct command
{
	char			*command;
	char			*path;
	char			**args;
}	t_command;

char		**ft_split_pipex(char *s, char c);
int			is_quote(char c);
char		*make_path(char *command, int len, char *dir_start, bool is_end);
char		*find_path(char *command, char **envp);
void		new_command(t_command *command, char *av_curr, char **envp);
t_command	*build_command_list(int ac, char **av, char **envp);
void		free_command_list(t_command *command_list, int size);

#endif
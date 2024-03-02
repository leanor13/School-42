/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yioffe <yioffe@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 11:27:07 by yioffe            #+#    #+#             */
/*   Updated: 2024/03/02 10:04:00 by yioffe           ###   ########.fr       */
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

# define ERROR "Error\n"
# define WRONG_ARG_NUM "Wrong number of arguments. \
	Usage: ./pipex file1 cmd1 cmd2 file2\n"

typedef struct command
{
	char			*command;
	char			*path;
	char			**args;
	int				fd_input;
	int				fd_output;
}	t_command;

char		**ft_split_pipex(char *s, char c);
char		*make_path(char *command, int dir_len, char *dir_start, bool is_end);
char		*find_path(char *command, char **envp);
void		new_command(t_command *command, char *av_curr, char **envp);
t_command	*build_command_list(int ac, char **av, char **envp);
void		free_command_list(t_command *command_list, int size);

#endif
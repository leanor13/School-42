/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yioffe <yioffe@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 11:27:07 by yioffe            #+#    #+#             */
/*   Updated: 2024/03/24 12:31:08 by yioffe           ###   ########.fr       */
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
# define HERE_DOC 0
# define INPUT_FILE 1
# define OUTPUT_FILE 2

# define WRONG_ARG_NUM "Wrong number of arguments. \
Usage: ./pipex file1 cmd1 cmd2 file2 or \
./pipex here_doc LIMITER cmd cmd1 file \n"
# define ERR_NESTED_QUOTES "Syntax error: nested quotes"
# define ERR_SINGLE_QUOTE "Syntax error: single quote"
# define EMPTY_ENV "No PATH in envp, provide full path\n"

typedef struct command
{
	char			*command;
	char			*path;
	char			**args;
}	t_command;

char		**ft_split_pipex(char *s, char c);
int			is_quote(char c);
t_command	*build_command_list(int ac, char **av, char **envp);
int			dir_len_count(char *dir_start);
char		*absolute_path(char *command);
void		here_doc(char *limiter, int *fd_files);
int			open_file(int ac, char **av, int type);
void		open_files_here_doc(int ac, char **av, int fd_files[2]);
void		ft_close_protected(void);
void		ft_close_all(void);

void		free_command_list(t_command *command_list, int size);
void		close_both_ends(int fd[2], bool pipe_error);
void		close_2_fds(int fd1, int fd2);
void		close_3_fds(int fd_files[2], int fd[2], int fd_pipe[2]);
void		dup_close(int fd, int reference);
void		ft_close(int fd);
void		validate_params(int ac, char **av);
void		exit_pipe_error(int fd[2]);

#endif
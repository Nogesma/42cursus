//
// Created by tkondrac on 26.12.21.
//

#include "minishell.h"

//finds next occurence of tokens &&, || or | in string, zeros their chars, stores pointer to characters just
// after in cmd_two and returns which one it found, -1 if none
static int	find_token(char *line, char **cmd_two)
{
	while(*line)
	{
		if (!ft_strncmp(line, "&&", 2))
		{
			line[0] = 0;
			line[1] = 0;
			*cmd_two = line + 2;
			return (0);
		}
		else if (!ft_strncmp(line, "||", 2))
		{
			line[0] = 0;
			line[1] = 0;
			*cmd_two = line + 2;
			return (1);
		}
		else if (!ft_strncmp(line, "|", 1))
		{
			line[0] = 0;
			*cmd_two = line + 1;
			return (2);
		}
		line++;
	}
	return (-1);
}

static int	piped_exec(char *line, char *cmd_two, t_list **env) //todo maybe deal with errors and errno of pipe and dup, dup2
{
	int	saved_fd;
	int p[2];
	int	ret;

	saved_fd = dup(1);
	if (saved_fd == -1)
		return (1);
	if (pipe(p) == -1)
		return (1);
	if (dup2(p[1], 1) == -1)
		return (1);
	close(p[1]);
	ret = rec_cmds(line, env);
	if (ret != 0)
		return (ret);
	if (dup2(saved_fd, 1) == -1)
		return (1);
	saved_fd = dup(0);
	if (saved_fd == -1)
		return (1);
	if (dup2(p[0], 0) == -1)
		return (1);
	close(p[0]);
	ret = rec_cmds(cmd_two, env);
	if (dup2(saved_fd, 0) == -1)
		return (1);
	close(saved_fd);
	return (ret);
}

int	rec_cmds(char *line, t_list **env)
{
	int		ret;
	char	*cmd_two;
	int		token;

	token = find_token(line, &cmd_two);
	if (token == 0)
		return (rec_cmds(line, env) || rec_cmds(cmd_two, env));
	if (token == 1)
		return (rec_cmds(line, env) && rec_cmds(cmd_two, env));
	if (token == 2)
		return (piped_exec(line, cmd_two, env));
//	set_redirect(line, env);
	ret = search_exec(line, env);
//	unset_redirect(line, env);
	return (ret);
}

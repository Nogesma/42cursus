//
// Created by tkondrac on 26.12.21.
//

#include "minishell.h"

int	rec_cmds(char *line, t_list **env)
{
	int		ret;
	char	*cmd_two;
	int		token;

	cmd_two = line;
	token = find_token(line, cmd_two);
	if (token == 0)
		return (search_exec(line, env) && search_exec(cmd_two, env));
	if (token == 1)
		return (search_exec(line, env) || search_exec(cmd_two, env));
	if (token == 2)
		return (piped_exec(line, cmd_two, env));
	set_redirect(line, env);
	ret = search_exec(line, env);
	unset_redirect(line, env);
	return (ret);
}

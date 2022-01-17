#include <libft.h>

#include "validator.h"

int	print_error(char *err)
{
	ft_printf(2, "minish: syntax error near unexpected token `%s`\n", err);
	return (1);
}

int	check_quotes(char *line)
{
	char	single_quote;
	char	double_quote;

	single_quote = 0;
	double_quote = 0;
	while (*line)
	{
		if (*line == '\'')
			++single_quote;
		if (*line == '"')
			++double_quote;
		++line;
	}
	if (single_quote % 2)
		return (print_error("'"));
	if (double_quote % 2)
		return (print_error("\""));
	return (0);
}

int check_pipes(char *line)
{
	char	has_char;

	has_char = 0;
	while (*line)
	{
		if (*line == '|')
		{
			if (!has_char)
				return (print_error("|"));
			has_char = 0;
		}
		else if (!ft_isspace(*line))
			has_char = 1;
		++line;
	}
	if (!has_char)
		return (print_error("|"));
	return (0);
}

int check_double(char *line, char *token)
{
	size_t	i;
	char	has_char;

	has_char = 0;
	i = 0;
	while (line[i])
	{
		if (!ft_strncmp(token, line + i, 2))
		{
			if (!has_char)
				return (print_error(token));
			has_char = 0;
		}
		else if (i > 0 && !ft_strncmp(token, line + i - 1, 2))
			has_char = 0;
		else if (!ft_isspace(line[i]))
			has_char = 1;
		++i;
	}
	if (!has_char)
		return (print_error(token));
	return (0);
}

int	check_line(char *line)
{
	if (check_quotes(line))
		return (1);
	if (check_double(line, "&&"))
		return (1);
	if (check_double(line, "||"))
		return (1);
	if (check_pipes(line))
		return (1);
	return (0);
}
#include "asm.h"

static t_type_token	get_type_token(char *str, size_t len)
{
	if (str == NULL)
		return (UNKNOWN);
	if (len == 1 && str[0] == SEPARATOR_CHAR)
		return (SEPARATOR);
	else if (!ft_strcmp(str, NAME_CMD_STRING))
		return (NAME);
	else if (!ft_strcmp(str, COMMENT_CMD_STRING))
		return (COMMENT);
	else if (len >= 2 && len <= 3 && str[0] == 'r' && is_num_from_ind(str, 1))
		return (REGISTER);
	else if (is_num_from_ind(str, 0))
		return (INDIRECT);
	else if (len >= 2 && str[0] == LABEL_CHAR)
		return (INDIRECT_LABEL);
	else if (len >= 3 && str[0] == DIRECT_CHAR && str[1] == LABEL_CHAR)
		return (DIRECT_LABEL);
	else if (len >= 2 && str[0] == DIRECT_CHAR)
		return (DIRECT);
	else if (is_instr(str))
		return (INSTRUCTION);
	else if (is_label(str, len))
		return (LABEL);
	else if (len >= 2 && str[0] == '"' && str[len - 1] == '"')
		return (STRING);
	return (UNKNOWN);
}

static void			parse_by_sep(char *str, t_token_list *tokens)
{
	t_type_token	type;
	size_t			index;
	size_t			curr_index;
	char			*str_sub;

	index = 0;
	curr_index = 0;
	while (str[index] != '\0')
	{
		while (str[curr_index] != SEPARATOR_CHAR && str[curr_index] != '\0')
			++curr_index;
		// TO DO
//		str_sub = ft_strsub(str, index, curr_index - index);
		MFAIL((str_sub = ft_strsub(str, index, curr_index - index)));
		type = get_type_token(str_sub, ft_strlen(str_sub));
		tokens_add_tokens(tokens, create_token(str_sub, type));
		if (str[curr_index] == SEPARATOR_CHAR)
		{
			tokens_add_tokens(tokens,
					create_token(char_to_string(SEPARATOR_CHAR), SEPARATOR));
			++curr_index;
		}
		index = curr_index;
	}
}

static size_t		get_last_index_string(const char *line, size_t start_index)
{
	size_t	index;

	index = start_index + 1;
	while (line[index] != '\0' && line[index] != '"')
		++index;
	if (line[index] == '"')
		++index;
	return (index);
}

t_token_list		*get_token_list(const char *line, size_t *curr_index)
{
	size_t			start_ind_token;
	size_t			len_token;
	char			*str_token;
	t_token_list	*token_list;

	start_ind_token = *curr_index;
	// TO DO
//	if ((token_list = (t_token_list *)malloc(sizeof(t_token_list))) == NULL)
//		print_error_and_exit();
	MFAIL((token_list = (t_token_list *)malloc(sizeof(t_token_list))));
	init_token_list(token_list);
	if (line[start_ind_token] == '"')
		*curr_index = get_last_index_string(line, start_ind_token);
	else
		while (line[*curr_index] != '\0' && !is_whitespace(line[*curr_index]))
			++(*curr_index);
	len_token = *curr_index - start_ind_token;
	if (len_token != 0)
	{
//		str_token = ft_strsub(line, start_ind_token, len_token);
		MFAIL((str_token = ft_strsub(line, start_ind_token, len_token)));
		parse_by_sep(str_token, token_list);
//		free(str_token);
		FCNT((free(str_token)));
	}
	return (token_list);
}

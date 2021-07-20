#include "asm.h"

static void			parse_line(t_token_list *token_list, const char *line)
{
	size_t			index;
	t_token_list	*new_list;

	index = 0;
	while (line[index] != '\0')
	{
		index = skip_whitespaces(line, index);
		if (line[index] == COMMENT_CHAR || line[index] == '\0')
			break ;
		new_list = get_token_list(line, &index);
		tokens_add_tokens(token_list, new_list->begin);
		FCNT(free(new_list));
	}
}

void				parse(t_token_list *token_list, char *file_name)
{
	int		fd;
	int		ret;
	char	*line;
	char	*new_line;
	char	*end_line;

	line = NULL;
	if ((fd = open(file_name, O_RDONLY)) == -1)
		print_error_and_exit();
	while ((ret = get_next_line(fd, &line)))
	{
		parse_line(token_list, line);
		// TO DO
//		tokens_add_tokens(token_list,
//					create_token(ft_strdup("NEW_LINE"), NEW_LINE));
		MFAIL((new_line = ft_strdup("NEW_LINE")));
		tokens_add_tokens(token_list,
					create_token(new_line, NEW_LINE));
		free(line);
		line = NULL;
	}
	close(fd);
//	tokens_add_tokens(token_list, create_token(ft_strdup("END"), END));
	MFAIL((end_line = ft_strdup("END")));
	tokens_add_tokens(token_list, create_token(end_line, END));
}

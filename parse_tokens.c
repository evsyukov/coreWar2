#include "asm.h"

static t_token	*handle_name(t_asm *asm_node, t_token *token)
{
	size_t len;

	if (token == NULL || token->next == NULL
		|| token->next->type_token != STRING)
		print_error_and_exit();
	token = token->next;
	len = ft_strlen(token->str) - 2;
	if (len > PROG_NAME_LENGTH)
		print_error_and_exit();
	if (len != 0)
		ft_strncpy(asm_node->header.prog_name, &(token->str[1]), len);
	asm_node->set_header += 1;
	return (token->next);
}

static t_token	*handle_comment(t_asm *asm_node, t_token *token)
{
	size_t len;

	if (token == NULL || token->next == NULL
		|| token->next->type_token != STRING)
		print_error_and_exit();
	token = token->next;
	len = ft_strlen(token->str) - 2;
	if (len > COMMENT_LENGTH)
		print_error_and_exit();
	if (len != 0)
		ft_strncpy(asm_node->header.comment, &(token->str[1]), len);
	asm_node->set_header += 2;
	return (token->next);
}

static t_token	*parse_header(t_asm *asm_node)
{
	t_token_list	*token_list;
	t_token			*token;
	size_t			count;

	token_list = &(asm_node->token_list);
	token = token_list->begin;
	count = 2;
	while (count--)
	{
		while (token->type_token == NEW_LINE)
			token = token->next;
		if (token->type_token == NAME
			&& (asm_node->set_header == 0 || asm_node->set_header == 2))
			token = handle_name(asm_node, token);
		else if (token->type_token == COMMENT
			&& (asm_node->set_header == 0 || asm_node->set_header == 1))
			token = handle_comment(asm_node, token);
		else
			print_error_and_exit();
	}
	return (token);
}

void			parse_tokens(t_asm *asm_node)
{
	t_token	*token;

	token = parse_header(asm_node);
	parse_code(asm_node, token);
	asm_node->len_final_cor = SIZE_MAGIC + PROG_NAME_LENGTH + SIZE_LEN_CODE
		+ COMMENT_LENGTH + SIZE_NULL_SEP * 2 + asm_node->counter_bytes;
}

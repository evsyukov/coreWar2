#include "asm.h"

static void		instrs_add(t_instr_list *instr_list, t_instr_row *instr_row)
{
	if (instr_list == NULL || instr_row == NULL)
		return ;
	if (instr_list->end == NULL)
	{
		instr_list->begin = instr_row;
		instr_list->end = instr_row;
		instr_row->next = NULL;
		instr_row->prev = NULL;
		instr_list->num_instrs += 1;
		instr_list->num_bytes += instr_row->num_bytes;
		return ;
	}
	instr_list->end->next = instr_row;
	instr_row->prev = instr_list->end;
	instr_list->end = instr_row;
	instr_row->next = NULL;
	instr_list->num_instrs += 1;
	instr_list->num_bytes += instr_row->num_bytes;
}

static size_t	get_index(char *str)
{
	int	index;

	index = 0;
	while (index < NUM_OF_INSTR)
	{
		if (!ft_strcmp(INSTRS[index], str))
			return (index);
		++index;
	}
	return (-1);
}

static t_token	*handle_instr_row(t_asm *asm_node, t_token *token)
{
	int			index;
	t_instr_row	*instr_row;

	if ((index = get_index(token->str)) == -1)
		print_error_and_exit();
//	instr_row = create_instr_row(index, asm_node->counter_bytes);
//	if ((instr_row = (t_instr_row *)malloc(sizeof(t_instr_row))) == NULL)
//		print_error_and_exit();
	MFAIL((instr_row = (t_instr_row *)malloc(sizeof(t_instr_row))));
	init_instr_row(instr_row, index, asm_node->counter_bytes);
	token = parse_instr_row(instr_row, token);
	asm_node->counter_bytes += instr_row->num_bytes;
	instrs_add(&(asm_node->instr_list), instr_row);
	return (token);
}

static t_token	*pass_new_line_token(t_token *token)
{
	while (token->type_token == NEW_LINE)
		token = token->next;
	return (token);
}

void			parse_code(t_asm *asm_node, t_token *token)
{
	t_hash	*node;
	char	*node_str;

	if (asm_node->token_list.end->type_token != END)
		print_error_and_exit();
	token = pass_new_line_token(token);
	while (token->type_token != END)
	{
		while (token->type_token == LABEL)
		{
			// TO DO
//			node_str = ft_strsub(token->str, 0, ft_strlen(token->str) - 1);
			MFAIL((node_str = ft_strsub(token->str, 0, ft_strlen(token->str) - 1)));
			node = assign_to_table(asm_node->h_table, node_str);
			node->value = asm_node->instr_list.num_bytes;
			token = token->next;
			token = pass_new_line_token(token);
		}
		token = pass_new_line_token(token);
		if (token->type_token == INSTRUCTION)
			token = handle_instr_row(asm_node, token);
		else
			print_error_and_exit();
		token = pass_new_line_token(token);
	}
}

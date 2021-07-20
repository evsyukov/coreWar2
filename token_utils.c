#include "asm.h"

t_token	*create_token(char *str_token, t_type_token type)
{
	t_token	*token;

	// TO DO
//	if ((token = (t_token *)malloc(sizeof(t_token))) == NULL)
//		print_error_and_exit();
	MFAIL((token = (t_token *)malloc(sizeof(t_token))));
	token->str = str_token;
	token->type_token = type;
	token->next = NULL;
	token->prev = NULL;
	return (token);
}

void	tokens_add_tokens(t_token_list *token_list, t_token *token)
{
	if (token_list == NULL || token == NULL)
		return ;
	if (token_list->end == NULL)
	{
		token_list->begin = token;
		token->prev = NULL;
		while (token->next != NULL)
			token = token->next;
		token_list->end = token;
		return ;
	}
	token_list->end->next = token;
	token->prev = token_list->end;
	while (token->next != NULL)
		token = token->next;
	token_list->end = token;
	token->next = NULL;
}

//redirect implementation


//1 - собираем все токены в один лист
cmds = ft_pipe_separator(str);

typedef struct	s_file
{
	char	*name;
	int		type;
	t_file	*next;
}				t_file;

typedef struct	s_cmd
{
	char	**cmd;
	t_file	*begin_redirs;
	t_cmd	*next;
//	t_tkn	*prev;
}				t_cmd;


t_cmd	*ft_cmd_init(char symb, int count)
{
	t_cmd	*new_cmd;

	new_cmd = (cmd *)malloc(sizeof(t_cmd));
	if (!new_cmd)
		return (NULL);
//	new_cmd->type = ft_def_token_type(symb, count);
//	new_cmd->value = NULL;
	new_cmd->next = NULL;
	return (new_cmd);
}

t_cmd	**ft_free_cmd(t_tkn **begin_cmd)
{
	t_cmd	active;
	t_cmd	prev;

	active = *begin_cmd;
	prev = active;
	while (active->next)
	{
//		if (active->value)
//			free(active->value);
		active = active->next;
		free(prev);
		prev = active;
	}
	free(active);
	*begin_cmd = NULL;
	return (NULL);
}

t_cmd	**ft_cmd_add_back(t_tkn *new_cmd, t_tkn **begin_cmd)
{
	t_cmd	*last;

	if (!new_cmd)
		return (ft_free_cmd(begin_cmd));
	last = *begin_cmd;
	while (current->next)
		last = current->next;
	last->next = new_cmd;
	return (begin_cmd)
}


	t_cmd	*cmd_begin;

	if (!ft_cmd_add_back(ft_cmd_init('0', 0), &cmd_begin));//инициализация первого псевдотокена. не забыть удалить
		return (NULL);


t_cmd	**ft_cmds_tokenizer(char **cmds, t_cmd **cmd_begin)
{
	t_tkn	*tkn_begin;

	while (cmds)
	{
		if (!ft_tkn_add_back(ft_symb_tkn_init('0', 0), &tkn_begin));//инициализация первого псевдотокена. не забыть удалить
			return (NULL);
		if(!ft_command_tokenizer(*cmds, &tkn_begin))
			return (NULL);
		if(!ft_cmd_add_back(ft_cmd_filler(tkn_begin), cmd_begin))
			return (NULL);
		ft_free_tkn(&tkn_begin);
	}
}

int	ft_cmd_is_null(t_cmd *cmd)
{
	int	flag;

	flag == 1;
	flag *= cmd->?? == NULL;
	//...
	return (flag);
}

//--также нужна функция для обработки $с буквами в переменную, а с ? - в код последней ошибки, $$ - pid??

//2 - последовательно идём по токенам и заполняем t_cmd, раскрывая ковычки (у хердока без подмен)
// если после токена нет информативного, выдаём соответствующую ошибку
//> < >> << |

t_cmd	*ft_cmd_filler(t_tkn *tkn_begin))
{
	t_tkn	*tkn;
	t_cmd	*cmdt;

	cmdt = (t_cmd *)malloc(sizeof(t_cmd));
	if (!cmdt)
		return (NULL);
	tkn = tkn_begin;
	while (tkn->next)
	{
		//??????
	}
	return (cmdt);
}

// *предполагаем, что ошибка двух последовательных токенов пайпа уже проверена

//3 - получаем список t_cmd   если звёздочка не раскрыта, то тут можно проверить на абсолютно пустой цмд

//4 - исполняем пайп

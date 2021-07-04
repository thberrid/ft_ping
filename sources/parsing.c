/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thberrid <thberrid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/01 11:43:42 by thberrid          #+#    #+#             */
/*   Updated: 2021/07/01 11:43:46 by thberrid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_ping.h>
#include <ft_ping_parser.h>

static t_parser	*parser_get(void)
{
	static t_parser	parser[PARSER_LEN] = {
		{'h', &parsing_help, 0},
		{'c', &parsing_count, 2},
		{'v', &parsing_verbose, 1},
		{'t', &parsing_ttl, 2}
	};

	return (parser);
}

static int		parse_this(char *this, char *next, t_options *options, int *next_index)
{
	int			index;
	t_parser	*parser;

	if (this[0] != '-')
	{
		options->hostname = this;
		return (e_error_none);
	}
	if (this[1] == '\0'){
		return (e_error_opt_invalid);
	}
	parser = parser_get();
	index = 0;
	while (index < PARSER_LEN)
	{
		if (this[1] == parser[index].option)
		{
			*next_index = parser[index].next_arg;
			return (parser[index].fn(this, next, options));
		}
		index += 1;
	}
	return (e_error_opt_invalid);
}

static int		no_args(int ac)
{
	if (ac < 2)
	{
		ft_putendl(HELP_STRING);
		return (1);
	}
	return (0);
}

static int		no_address(const char *address)
{
	if (!address)
		return (1);
	return (0);
}

int				parsing(int ac, char **av, t_options *options)
{
	int			retrn;
	int			index;
	int			next_index;
	char		*next_arg;

	if (no_args(ac))
		return (e_error_opt_no_args);
	ft_bzero(options, sizeof(t_options));
	index = 1;
	while (index < ac)
	{
		next_index = 1;
		next_arg = NULL;
		if (index + 1 < ac)
			next_arg = av[index + 1];
		retrn = parse_this(av[index], next_arg, options, &next_index);
		if (retrn != e_error_none)
			return (retrn);
		index += next_index;
	}
	if (no_address(options->hostname))
		return (e_error_opt_no_address);
	return (e_error_none);
}
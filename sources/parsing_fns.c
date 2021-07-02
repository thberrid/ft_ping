/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_fns.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thberrid <thberrid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/01 15:42:17 by thberrid          #+#    #+#             */
/*   Updated: 2021/07/01 15:42:19 by thberrid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_ping.h>
#include <ft_ping_parser.h>

int		parsing_help(char *this, char *next, t_options *options)
{
	(void)this;
	(void)next;
	options->help_required = 1;
	ft_putendl(HELP_STRING);
	return (e_error_help_printed);
}

int		parsing_count(char *this, char *next, t_options *options)
{
	(void)this;
	if (next && ft_isnumeric(next))
	{
		options->count = ft_atoi(next);
		if (options->count > 0)
			return (e_error_none);
	}
	return (e_error_opt_count_error);
}

int		parsing_ttl(char *this, char *next, t_options *options)
{
	(void)this;
	if (next && ft_isnumeric(next))
	{
		options->ttl = ft_atoi(next);
		if (options->ttl > 0)
			return (e_error_none);
	}
	return (e_error_opt_ttl_error);
}

int		parsing_verbose(char *this, char *next, t_options *options)
{
	(void)this;
	(void)next;
	options->verbose_required = 1;
	return (e_error_none);
}
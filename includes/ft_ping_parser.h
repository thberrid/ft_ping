/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ping_parser.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thberrid <thberrid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/02 15:36:09 by thberrid          #+#    #+#             */
/*   Updated: 2021/07/02 15:36:11 by thberrid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PING_PARSER_H
# define FT_PING_PARSER_H

# include <libft.h>
# include <ft_ping.h>

# define ICMP_ECHO_REQUEST	8

# define PARSER_LEN			4

typedef struct	s_parser
{
	char 	option;
	int		(*fn)(char *, char *, t_options *);
	int		next_arg;
}				t_parser;

int		parsing(int ac, char **av, t_options *options);

int		parsing_help(char *this, char *next, t_options *options);
int		parsing_count(char *this, char *next, t_options *options);
int		parsing_verbose(char *this, char *next, t_options *options);
int		parsing_ttl(char *this, char *next, t_options *options);

#endif

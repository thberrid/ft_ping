/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ping_errors.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thberrid <thberrid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/02 15:35:55 by thberrid          #+#    #+#             */
/*   Updated: 2021/07/02 15:35:57 by thberrid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PING_ERRORS_H
# define FT_PING_ERRORS_H

#include <errno.h>

# define EMSG_OPT_INVALID			"invalid option."
# define EMSG_USERNOTROOT			"ft_ping needs to be launch with sudo."
# define EMSG_OPT_COUNT_ERROR		"bad number of packets to transmit."
# define EMSG_OPT_MISSING_ADDRESS	"need an address."
# define EMSG_OPT_TTL_ERROR			"ttl out of range."
# define EMSG_SOCKFAIL				"fail to create socket."
# define EMSG_ADDRINFOFAIL			"fail to get address informations."
# define EMSG_SENDTOFAIL			"sendto() fails."
# define EMSG_RECVMSGFAIL			"recvmsg() fails."

# define ERRORS_MSG_LEN				9

enum e_error
{
	e_error_none = 0,
	e_error_notroot,
	e_error_opt_no_address,
	e_error_help_printed,
	e_error_opt_invalid,
	e_error_opt_count_error,
	e_error_opt_ttl_error,
	e_error_opt_no_args,
	e_error_socket_creation,
	e_error_addrinfo_creation,
	e_error_sendto,
	e_error_recvmsg
};

typedef struct	s_errors_msg
{
	enum e_error	enum_code;
	char			*msg;
}				t_error_msg;

void			print_return_code(enum e_error this_enum);

#endif

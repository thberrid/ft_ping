/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_return_code.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thberrid <thberrid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/02 15:30:10 by thberrid          #+#    #+#             */
/*   Updated: 2021/07/02 15:30:18 by thberrid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_ping.h>

static t_error_msg	*error_msgs_get(void)
{
	static t_error_msg msgs[ERRORS_MSG_LEN] = {
		{e_error_opt_no_address, EMSG_OPT_MISSING_ADDRESS},
		{e_error_opt_invalid, EMSG_OPT_INVALID},
		{e_error_opt_count_error, EMSG_OPT_COUNT_ERROR},
		{e_error_opt_ttl_error, EMSG_OPT_TTL_ERROR},
		{e_error_socket_creation, EMSG_SOCKFAIL},
		{e_error_addrinfo_creation, EMSG_ADDRINFOFAIL},
		{e_error_sendto, EMSG_SENDTOFAIL},
		{e_error_recvmsg, EMSG_RECVMSGFAIL}
	};

	return (msgs);
}

void				print_return_code(enum e_error this_enum)
{
	t_error_msg		*msgs;
	int				index;

	msgs = error_msgs_get();
	index = 0;
	while (index < ERRORS_MSG_LEN)
	{
		if (this_enum == msgs[index].enum_code)
		{
			ft_printf("ft_ping: %s\n", msgs[index].msg);
			return ;
		}
		index += 1;
	}
	return ;
}

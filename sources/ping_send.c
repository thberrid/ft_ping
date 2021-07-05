/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ping_send.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thberrid <thberrid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/05 19:44:03 by thberrid          #+#    #+#             */
/*   Updated: 2021/07/05 19:44:23 by thberrid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_ping.h>

void		ping_send(int signum)
{
	ft_printf("\n\nsignum: %d\n\n", signum);
	ping_packet_update(&packet, 1);
	retrn = sendto(sockfd, &packet, sizeof(struct icmp_packet), 0, addrinfo->ai_addr, addrinfo->ai_addrlen);
	if (retrn)
	{
		retrn = ping_reception(sockfd, addrinfo, options);
		if (retrn != e_error_none)
		{
			print_return_code(e_error_sendto);
			exit(e_error_sendto);
		}
		return ;
	}
	print_return_code(e_error_sendto);
	exit(e_error_sendto);
}
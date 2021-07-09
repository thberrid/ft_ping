/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ping_reception.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thberrid <thberrid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/03 14:16:06 by thberrid          #+#    #+#             */
/*   Updated: 2021/07/03 14:16:08 by thberrid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_ping.h>

static void	response_prepare(struct msghdr *response,
				struct iovec *s_iovec,
				char *s_iov_base,
				struct addrinfo *addrinfo)
{
	ft_bzero(response, sizeof(struct msghdr));
	ft_memset(s_iov_base, 0x6e, IOVLEN);
	response->msg_name = addrinfo->ai_addr;                                           
	response->msg_namelen = addrinfo->ai_addrlen;
	response->msg_iovlen = 1;
	response->msg_iov = s_iovec;
	s_iovec->iov_base = s_iov_base;
	s_iovec->iov_len = IOVLEN;
}

int			ping_reception(int sockfd,
				struct addrinfo *addrinfo, 
				t_options *options)
{
	struct msghdr		response;
	struct iovec		s_iovec;
	char				s_iov_base[IOVLEN];
	struct icmp_packet	*icmp;

	ft_printf("CALL Reception\n");
	response_prepare(&response, &s_iovec, s_iov_base, addrinfo);
	if (recvmsg(sockfd, &response, 0) <= 0)
	{
		print_return_code(e_error_recvmsg);
		exit(e_error_recvmsg);
	}
	icmp = (struct icmp_packet *)((char *)s_iov_base + sizeof(struct ip));
	if (icmp->header.type == ICMP_TYPE_ECHO_REQUEST)
	{
		ft_printf("echo rechest\n");
		return (NOT_RECEIVED);
	}
	ft_printf("echo reply\n");
	ping_print_loop((struct ip *)s_iov_base, icmp, options);
	// update statistics
	return (RECEIVED);
}

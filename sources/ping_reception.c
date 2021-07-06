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

static void	ipheader_prepare(struct msghdr *response, struct iovec *s_iovec, char *s_iov_base, struct addrinfo *addrinfo)
{
	bzero(response, sizeof(struct msghdr));
	ft_memset(s_iov_base, 0x6e, IOVLEN);
	response->msg_name = addrinfo->ai_addr;                                           
	response->msg_namelen = addrinfo->ai_addrlen;
	response->msg_iovlen = 1;
	response->msg_iov = s_iovec;
	s_iovec->iov_base = s_iov_base;
	s_iovec->iov_len = IOVLEN;
}

int			ping_reception(int sockfd, struct addrinfo *addrinfo, t_options *options)
{
	int					retrn;
	struct msghdr		response;
	struct iovec		s_iovec;
	char				s_iov_base[IOVLEN];
	struct icmp_packet	*icmp;

	ipheader_prepare(&response, &s_iovec, s_iov_base, addrinfo);
	retrn = recvmsg(sockfd, &response, 0);
	if (retrn < 1)
		return (retrn);
	icmp = (struct icmp_packet *)((char *)s_iov_base + sizeof(struct ip));
	ping_print_loop((struct ip *)s_iov_base, icmp, options);
	if (options->count > 0 && ft_htons(icmp->header.un.echo.sequence) >= options->count)
		ping_end(e_error_none);
	alarm(2);
	return (e_error_none);
}

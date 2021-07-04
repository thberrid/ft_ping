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

static void	ipheader_prepare(struct msghdr *ipheader, struct iovec *s_iovec, char *s_iov_base, struct addrinfo *addrinfo)
{
	bzero(ipheader, sizeof(struct msghdr));
	ft_memset(s_iov_base, 0x6e, IOVLEN);
	ipheader->msg_name = addrinfo->ai_addr;                                           
	ipheader->msg_namelen = addrinfo->ai_addrlen;
	ipheader->msg_iovlen = 1;
	ipheader->msg_iov = s_iovec;
	s_iovec->iov_base = s_iov_base;
	s_iovec->iov_len = IOVLEN;
}	

int			ping_reception(int sockfd, struct addrinfo *addrinfo, t_options *options)
{
	int				retrn;
	struct msghdr	msg;
	struct iovec	s_iovec;
	char			s_iov_base[IOVLEN];

	ipheader_prepare(&msg, &s_iovec, s_iov_base, addrinfo);
	if (!ft_strcmp(options->address, "localhost"))
		recvmsg(sockfd, &msg, 0);
	retrn = recvmsg(sockfd, &msg, 0);
	if (retrn < 1)
		return (retrn);
	ping_print_loop((struct ip *)s_iov_base, options);
	return (e_error_none);
}

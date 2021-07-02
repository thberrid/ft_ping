/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ping_prepare.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thberrid <thberrid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/02 18:02:51 by thberrid          #+#    #+#             */
/*   Updated: 2021/07/02 18:02:53 by thberrid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_ping.h>

static int	set_sockdf(int *sockfd)
{
	*sockfd = socket(AF_INET, SOCK_RAW, IPPROTO_ICMP);
	if (*sockfd > 0)
		return (1);
	return (0);
}

static int	set_addrinfo(struct addrinfo **addrinfo, t_options *options)
{
	struct addrinfo hint;

	ft_bzero(&hint, sizeof(struct addrinfo));
	hint.ai_family = AF_INET;
	hint.ai_protocol = IPPROTO_ICMP;
	if (getaddrinfo(options->address, NULL, &hint, addrinfo) != 0)
		return (e_error_addrinfo_creation);
	return (e_error_none);
}

static void	set_packet(struct icmp_packet *packet)
{
	ft_bzero(packet, sizeof(struct icmp_packet));
	packet->header.type = ICMP_ECHO_REQUEST;
	packet->header.code = 0;
	packet->header.un.id = getpid();
	
	return ;
}

int 		ping_packet_prepare(int *sockfd, struct addrinfo **addrinfo, t_options *options) 		
{
	if (set_sockdf(sockfd))
		return (e_error_socket_creation);
	if (set_addrinfo(addrinfo, options))
		return (e_error_addrinfo_creation);
	set_packet(&packet);
	return (e_error_none);
}
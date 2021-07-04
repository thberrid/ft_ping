/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ping_prepare_update_packet.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thberrid <thberrid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/03 14:10:20 by thberrid          #+#    #+#             */
/*   Updated: 2021/07/03 14:10:25 by thberrid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_ping.h>

static int	set_sockdf(int *sockfd)
{
	*sockfd = socket(AF_INET, SOCK_RAW, IPPROTO_ICMP);
	if (*sockfd < 2)
		return (1);
	return (0);
}

static int	set_addrinfo(struct addrinfo **addrinfo, t_options *options)
{
	struct addrinfo hint;

	ft_bzero(&hint, sizeof(struct addrinfo));
	hint.ai_family = AF_INET;
	hint.ai_protocol = IPPROTO_ICMP;
	hint.ai_flags = AI_CANONNAME;
	if (getaddrinfo(options->hostname, NULL, &hint, addrinfo) != 0)
		return (e_error_addrinfo_creation);
	return (e_error_none);
}

static void	set_packet(struct icmp_packet *packet)
{
	ft_bzero(packet, sizeof(struct icmp_packet));
	packet->header.type = ICMP_TYPE_ECHO_REQUEST;
	packet->header.code = ICMP_CODE_ECHO_REPLY;
	packet->header.un.echo.id = ft_htons(getpid());
	ft_memset(packet->data, 'o', ICMP_DATA_LEN);
	return ;
}

void		ping_packet_update(struct icmp_packet *packet, int index)
{
	packet->header.un.echo.sequence = ft_htons(index);
	packet->header.checksum = 0;
	packet->header.checksum = checksum(packet, sizeof(struct icmp_packet));
}

int 		ping_prepare(struct icmp_packet *packet, int *sockfd, struct addrinfo **addrinfo, t_options *options) 		
{
	if (set_sockdf(sockfd))
		return (e_error_socket_creation);
	if (set_addrinfo(addrinfo, options))
		return (e_error_addrinfo_creation);
	set_packet(packet);
	return (e_error_none);
}

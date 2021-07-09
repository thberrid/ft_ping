/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ping_prepare.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thberrid <thberrid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/06 17:00:42 by thberrid          #+#    #+#             */
/*   Updated: 2021/07/06 17:00:46 by thberrid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_ping.h>
#include <ft_ping_parser.h>

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

int 		ping_prepare(int ac, char **av, t_options *options) 		
{
	int		retrn;

	retrn = parsing(ac, av, options);
	if (retrn != e_error_none)
		return (retrn);
	if (set_sockdf(&g_pingu.sockfd))
		return (e_error_socket_creation);
	if (set_addrinfo(&g_pingu.addrinfo, options))
		return (e_error_addrinfo_creation);
	g_pingu.options = options;
	g_pingu.sequence = 0;
	set_packet(&g_pingu.sendpacket);
	signal(SIGALRM, &ping_alarm);
	signal(SIGINT, &ping_end);
	return (e_error_none);
}

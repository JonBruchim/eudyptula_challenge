// SPDX-License-Identifier: GPL-2.0-only
/*
 * net_monitor.c - eudyptula task 19
 * Copyright (C) 2019 Jonathan Bruchim  <Yonbruchim@gmail.com>
 */

#include <linux/module.h>
#include <linux/netfilter.h>
#include<linux/ip.h>

static unsigned int inspect_packet(void *priv, struct sk_buff *skb,
		    const struct nf_hook_state *state);


__be32 IP_DROP = 2899908078;

struct nf_hook_ops hook_ops = {
	.hook     = inspect_packet,
	.pf       = NFPROTO_IPV4,
	.hooknum  = NF_INET_PRE_ROUTING,
	/* Hooks are ordered in ascending priority. */
	.priority = INT_MAX,
};

static unsigned int inspect_packet(void *priv, struct sk_buff *skb,
		    const struct nf_hook_state *state)
{
	int ret = NF_ACCEPT;
	const struct iphdr *ip;

	ip = ip_hdr(skb);
	pr_info("%pI4\n", &ip->saddr);

	if (ip->daddr == IP_DROP) {
		pr_info("Dropping google\n");
		return NF_DROP;
	}

	return ret;
}

static int __init net_monitor_init(void)
{
	int ret = 0;

	nf_register_net_hook(&init_net, &hook_ops);

	return ret;
}

static void __exit net_monitor_fini(void)
{
	nf_unregister_net_hook(&init_net, &hook_ops);
}

module_init(net_monitor_init);
module_exit(net_monitor_fini);
MODULE_LICENSE("GPL");

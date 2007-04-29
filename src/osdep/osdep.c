/*-
 * Copyright (c) 2007, Andrea Bittau <a.bittau@cs.ucl.ac.uk>
 *
 * All OS dependent crap should go here.
 *
 */

#include <stdlib.h>
#include <assert.h>
#include <string.h>

#include "osdep.h"
#include "network.h"

int wi_read(struct wif *wi, unsigned char *h80211, int len, struct rx_info *ri)
{
        assert(wi->wi_read);
        return wi->wi_read(wi, h80211, len, ri);
}

int wi_write(struct wif *wi, unsigned char *h80211, int len,
             struct tx_info *ti)
{
        assert(wi->wi_write);
        return wi->wi_write(wi, h80211, len, ti);
}

int wi_set_channel(struct wif *wi, int chan)
{
        assert(wi->wi_set_channel);
        return wi->wi_set_channel(wi, chan);
}

int wi_get_channel(struct wif *wi)
{
	assert(wi->wi_set_channel);
        return wi->wi_get_channel(wi);
}

char *wi_get_ifname(struct wif *wi)
{
        return wi->wi_interface;
}

void wi_close(struct wif *wi)
{
        assert(wi->wi_close);
        wi->wi_close(wi);
}

int wi_fd(struct wif *wi)
{
	assert(wi->wi_fd);
	return wi->wi_fd(wi);
}

struct wif *wi_alloc(int sz)
{
        struct wif *wi;
	void *priv;

        /* Allocate wif & private state */
        wi = malloc(sizeof(*wi));
        if (!wi)
                return NULL;
        memset(wi, 0, sizeof(*wi));

        priv = malloc(sz);
        if (!priv) {
                free(wi);
                return NULL;
        }
        memset(priv, 0, sz);
        wi->wi_priv = priv;

	return wi;
}

void *wi_priv(struct wif *wi)
{
	return wi->wi_priv;
}

int wi_get_mac(struct wif *wi, unsigned char *mac)
{
	assert(wi->wi_get_mac);
	return wi->wi_get_mac(wi, mac);
}

int wi_set_mac(struct wif *wi, unsigned char *mac)
{
	assert(wi->wi_set_mac);
	return wi->wi_set_mac(wi, mac);
}

struct wif *wi_open(char *iface)
{
	struct wif *wi;

	/* XXX assume for now that all OSes have UNIX sockets */
	wi = net_open(iface);
	if (!wi)
		wi = wi_open_osdep(iface);
	if (!wi)
		return NULL;
	
	strncpy(wi->wi_interface, iface, sizeof(wi->wi_interface)-1);
	wi->wi_interface[sizeof(wi->wi_interface)-1] = 0;

	return wi;
}

/* tap stuff */
char *ti_name(struct tif *ti)
{
	assert(ti->ti_name);
	return ti->ti_name(ti);
}

int ti_set_mtu(struct tif *ti, int mtu)
{
	assert(ti->ti_set_mtu);
	return ti->ti_set_mtu(ti, mtu);
}

void ti_close(struct tif *ti)
{
	assert(ti->ti_close);
	ti->ti_close(ti);
}

int ti_fd(struct tif *ti)
{
	assert(ti->ti_fd);
	return ti->ti_fd(ti);
}

int ti_read(struct tif *ti, void *buf, int len)
{
	assert(ti->ti_read);
	return ti->ti_read(ti, buf, len);
}

int ti_write(struct tif *ti, void *buf, int len)
{
	assert(ti->ti_write);
	return ti->ti_write(ti, buf, len);
}

int ti_set_mac(struct tif *ti, unsigned char *mac)
{
	assert(ti->ti_set_mac);
	return ti->ti_set_mac(ti, mac);
}

int ti_set_ip(struct tif *ti, struct in_addr *ip)
{
	assert(ti->ti_set_ip);
	return ti->ti_set_ip(ti, ip);
}

struct tif *ti_alloc(int sz)
{
        struct tif *ti;
	void *priv;

        /* Allocate tif & private state */
        ti = malloc(sizeof(*ti));
        if (!ti)
                return NULL;
        memset(ti, 0, sizeof(*ti));

        priv = malloc(sz);
        if (!priv) {
                free(ti);
                return NULL;
        }
        memset(priv, 0, sz);
        ti->ti_priv = priv;

	return ti;
}

void *ti_priv(struct tif *ti)
{
	return ti->ti_priv;
}

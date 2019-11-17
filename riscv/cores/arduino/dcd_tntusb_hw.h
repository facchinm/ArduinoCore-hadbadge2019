/*
 * usb_hw.h
 *
 * Copyright (C) 2019 Sylvain Munaut
 * All rights reserved.
 *
 * LGPL v3+, see LICENSE.lgpl3
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 3 of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program; if not, write to the Free Software Foundation,
 * Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.
 */

#pragma once

#include <stdint.h>

#include "mach_defines.h"


struct tntusb_core {
	uint32_t csr;
	uint32_t ar;
	uint32_t evt;
} __attribute__((packed,aligned(4)));

#define TNTUSB_CSR_PU_ENA		(1 << 15)
#define TNTUSB_CSR_EVT_PENDING	(1 << 14)
#define TNTUSB_CSR_CEL_ACTIVE	(1 << 13)
#define TNTUSB_CSR_CEL_ENA		(1 << 12)
#define TNTUSB_CSR_BUS_SUSPEND	(1 << 11)
#define TNTUSB_CSR_BUS_RST		(1 << 10)
#define TNTUSB_CSR_BUS_RST_PENDING	(1 <<  9)
#define TNTUSB_CSR_SOF_PENDING	(1 <<  8)
#define TNTUSB_CSR_ADDR_MATCH	(1 <<  7)
#define TNTUSB_CSR_ADDR(x)		((x) & 0x7f)

#define TNTUSB_AR_CEL_RELEASE	(1 << 13)
#define TNTUSB_AR_BUS_RST_CLEAR	(1 <<  9)
#define TNTUSB_AR_SOF_CLEAR	(1 <<  8)


struct tntusb_ep {
	uint32_t status;
	uint32_t _rsvd[3];
	struct {
		uint32_t csr;
		uint32_t ptr;
	} bd[2];
} __attribute__((packed,aligned(4)));

struct tntusb_ep_pair {
	struct tntusb_ep out;
	struct tntusb_ep in;
} __attribute__((packed,aligned(4)));

#define TNTUSB_EP_TYPE_NONE	0x0000
#define TNTUSB_EP_TYPE_ISOC	0x0001
#define TNTUSB_EP_TYPE_INT		0x0002
#define TNTUSB_EP_TYPE_BULK	0x0004
#define TNTUSB_EP_TYPE_CTRL	0x0006
#define TNTUSB_EP_TYPE_HALTED	0x0001
#define TNTUSB_EP_TYPE_IS_BCI(x)	(((x) & 6) != 0)
#define TNTUSB_EP_TYPE(x)		((x) & 6)

#define TNTUSB_EP_DT_BIT		0x0080
#define TNTUSB_EP_BD_IDX		0x0040
#define TNTUSB_EP_BD_CTRL		0x0020
#define TNTUSB_EP_BD_DUAL		0x0010

#define TNTUSB_BD_STATE_MSK	0xe000
#define TNTUSB_BD_STATE_NONE	0x0000
#define TNTUSB_BD_STATE_RDY_DATA	0x4000
#define TNTUSB_BD_STATE_RDY_STALL	0x6000
#define TNTUSB_BD_STATE_DONE_OK	0x8000
#define TNTUSB_BD_STATE_DONE_ERR	0xa000
#define TNTUSB_BD_IS_SETUP		0x1000

#define TNTUSB_BD_LEN(l)		((l) & 0x3ff)
#define TNTUSB_BD_LEN_MSK		0x03ff

static volatile struct tntusb_core *    const tntusb_regs    = (void*) (USB_CORE_OFFSET);
static volatile struct tntusb_ep_pair * const tntusb_ep_regs = (void*)((USB_CORE_OFFSET) + (1 << 13));

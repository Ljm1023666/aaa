//
// bcmmailbox.h
//
// USPi - An USB driver for Raspberry Pi written in C
// Copyright (C) 2014  R. Stange <rsta2@o2online.de>
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.
//
#ifndef _uspienv_bcmmailbox_h
#define _uspienv_bcmmailbox_h

#include <uspienv/bcm2835.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct TBcmMailBox {
	unsigned m_nChannel;
} TBcmMailBox;

void BcmMailBox(TBcmMailBox *pThis, unsigned nChannel);
void _BcmMailBox(TBcmMailBox *pThis);

unsigned BcmMailBoxWriteRead(TBcmMailBox *pThis, unsigned nData);

#ifdef __cplusplus
}
#endif

#endif

/*
This file is part of AvrPsxLib.

    AvrPsxLib is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    any later version.

    AvrPsxLib is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with AvrPsxLib.  If not, see <http://www.gnu.org/licenses/>.
    copyleft kenzanin[At]solderen[Dot]tk
*/

#include <avr/io.h>
#include <util/delay.h>
#include "psx.h"

enum boolType {LOW,HI};

// data cmd att clk ack
void psxPadSetup(void)
{
    //data input
    dataPort|=_BV(dataPin);
    *(&dataPort-1)&=~_BV(dataPin);
    //cmd output
    cmdPort|=_BV(cmdPin);
    *(&cmdPort-1)|=_BV(cmdPin);
    //att output
    attPort|=_BV(attPin);
    *(&attPort-1)|=_BV(attPin);
    //clk output
    clkPort|=_BV(clkPin);
    *(&clkPort-1)|=_BV(clkPin);
//   ack input
//   ackPort|=_BV(ackPin);
//   *(&ackPort-1)&=~_BV(ackPin);
}

inline uint8_t getDataPin(void)
{
    return (*(&dataPort-2)&_BV(dataPin));
}

//inline uint8_t getAckPin(void)
//{
//    return (*(&ackPort-2)&_BV(ackPin));
//}

inline void setAttPin(enum boolType status)
{
    switch(status)
    {
    case LOW:
            attPort&=~_BV(attPin);
        break;
    case HI:
        attPort|=_BV(attPin);
        break;
    }
}

inline void setClkPin(enum boolType status)
{
    switch(status)
    {
    case LOW:
            clkPort&=~_BV(clkPin);
        break;
    case HI:
        clkPort|=_BV(clkPin);
        break;
    }
}

inline void setCmdPin(enum boolType status)
{
    switch(status)
    {
    case LOW:
            cmdPort&=~_BV(cmdPin);
        break;
    case HI:
        cmdPort|=_BV(cmdPin);
        break;
    }
}

uint8_t PSXsendCmdAndReciveData(uint8_t cmd)
{
    uint8_t data=0;
    uint8_t i;
    for(i=0; i<8; ++i)
    {
        setCmdPin((cmd>>i)&0x01);
        setClkPin(0);
        _delay_us(PSXclkDelay);
        setClkPin(1);
        _delay_us(PSXclkDelay);
        if(getDataPin())
        {
            data|=(0x01<<i);
        }
    }
    _delay_us(PSXclkDelay*2);
    return data;
}

const uint8_t __flash PSXComInit[]=
{
    0x01,
    0x42
};

uint8_t PsxReadPad(uint16_t *tombol)
{
    uint8_t i=0;
    uint8_t session=0;

    setAttPin(0);
    _delay_us(PSXclkDelay*2);
    for(i=0; i<2; ++i)
    {
        session=PSXsendCmdAndReciveData(PSXComInit[i]);
    }

    switch(session&0xf0)
    {
    case 0x40:
        ;
    case 0x70:
        ;
    case 0x20:
        ;
    case 0x50:
        ;
    case 0x10:
        session&=0x0f;
        ;
        break;
    default:
        goto PsxReadPadJMP01;
    }

    if(PSXsendCmdAndReciveData(PSXComInit[i])!=0x5A)
    {
        goto PsxReadPadJMP01;
    }

    for(i=0; i<(session); ++i)
    {
        *tombol = PSXsendCmdAndReciveData(0)<<8;
        *tombol|= PSXsendCmdAndReciveData(0);
        *tombol=~(*tombol);
        ++tombol;
    }

PsxReadPadJMP01:
    setAttPin(1);
    _delay_us(PSXclkDelay*2);
    setClkPin(1);
    setCmdPin(1);
    return session;
}

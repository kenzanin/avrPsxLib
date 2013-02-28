#ifndef PSX_H
#define PSX_H

// data coklat pin input
#define dataPort    PORTB
#define dataPin     PB0
// cmd putih pin output
#define cmdPort     PORTB
#define cmdPin      PB3
// att kuning pin output
#define attPort     PORTB
#define attPin      PB4
// clk biru pin output
#define clkPort     PORTB
#define clkPin      PB5
//#define ackPort     PORTB
//#define ackPin      PB4

//delay in uS
#define PSXclkDelay 40

#define PSXSelectBtn    0x0100
#define PSXL3Btn        0x0200
#define PSXR3Btn        0x0400
#define PSXStartBtn     0x0800
#define PSXUpBtn        0x1000
#define PSXRightBtn     0x2000
#define PSXDownBtn      0x4000
#define PSXLeftBtn      0x8000
#define PSXL2Btn        0x0001
#define PSXR2Btn        0x0002
#define PSXL1Btn        0x0004
#define PSXR1Btn        0x0008
#define PSXTriagleBtn   0x0010
#define PSXOBtn         0x0020
#define PSXXBtn         0x0040
#define PSXSquareBtn    0x0080

void     psxPadSetup(void);
uint8_t  PsxReadPad(uint16_t *tombol);

#endif // PSX_H

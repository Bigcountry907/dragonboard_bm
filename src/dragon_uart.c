/*
 * This file contains code to drive the uart device on the dragon board
 * Only uart write is implemented
 * The clocks and other UART parameters are expected to be setup up by the
 * boot loader
 */

#include<stdint-gcc.h>

// Defines used for Dragonboard uart(DU)
#define RESET_TX_READY        (3 << 8)
#define TX_READY              (1 << 2)
#define TX_EMPTY              (1 << 3)
#define INT_STATUS_TX_READY   (1 << 7)


// This structure represents the UART used in the dragonboard
// We only list the registers that we need, rest are marked as reserved
// We should add volatile to all the variable
struct DragonUART {
    uint32_t RES0[0x10];
    uint32_t NUM_CHARS_FOR_TX;              // offset: 0x40
    uint32_t RES1[0x18];
    uint32_t STATUS_REG;                    // offset: 0xA4
    uint32_t CMD_REG;                       // offset: 0xA8
    uint32_t RES2[0x2];
    uint32_t INT_STATUS_REG;                // offset: 0xB4
    uint32_t RES3[0x12];
    uint32_t TX_FIFO;                       // offset: 0x100
};

static struct DragonUART* duart = (struct DragonUART*)0x078B0000;

static inline void dragon_reset_tx_ready(void)
{
    // Make sure that the status reg says, tx fifo is empty
    while(!(duart->STATUS_REG & TX_EMPTY))
    {
		if (duart->INT_STATUS_REG & INT_STATUS_TX_READY)
			break;
	}

    duart->CMD_REG = RESET_TX_READY;
}

void dragon_putc(const char c)
{
    unsigned count = 1;
    uint32_t buf   = 0;

    if( c == '\n'){
        count = 2;
        buf = c | ('\r' << 8);
    }
    else
        buf = c;

	dragon_reset_tx_ready();

    // Write the number of chars we have for transmit
    duart->NUM_CHARS_FOR_TX = count;

    // Wait till the status reg says we are ready
    while (!(duart->STATUS_REG & TX_READY));

    duart->TX_FIFO = buf;
}

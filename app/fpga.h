#ifndef _Ifpga
#define _Ifpga

#include <inttypes.h>

int fpga_wr(uint16_t reg, uint32_t val);
int fpga_rd(uint16_t reg, uint32_t *val);

#endif

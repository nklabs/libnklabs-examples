#include "nkcli.h"
#include "nkspi.h"
#include "pins.h"
#include "fpga.h"

const nkspi_device_t fpga_bus =
{
    .cs_pin = &nk_pin_table[PIN_IDX_ARD_D10],
    .hspi = &ARD_SPI
};

int fpga_wr(uint16_t addr, uint32_t val)
{
    uint8_t buf[6];
    buf[0] = (addr >> 8);
    buf[1] = (addr & 0xfc) | 0x02; // Indicate write
    buf[2] = (val >> 24);
    buf[3] = (255 & (val >> 16));
    buf[4] = (255 & (val >> 8));
    buf[5] = (255 & (val));
    return nk_spi_transfer(&fpga_bus, buf, 6);
}

int fpga_rd(uint16_t addr, uint32_t *val)
{
    uint8_t buf[6];
    int rtn;
    buf[0] = (addr >> 8);
    buf[1] = (addr & 0xFc); // Indicates read
    rtn = nk_spi_transfer(&fpga_bus, buf, 6);
    *val = (buf[2] << 24) | (buf[3] << 16) | (buf[4] << 8) | buf[5];
    return rtn;
}

static int cmd_fpga(nkinfile_t *args)
{
        uint32_t      reg_addr;
        uint32_t      reg_data;
        int           transferOK;

        if (facmode && nk_fscan(args, "wr %x %x ", &reg_addr, &reg_data))
        {
                transferOK = fpga_wr(reg_addr, reg_data);
                if (!transferOK)
                    nk_printf("Wrote %lx to register %lx\n", reg_data, reg_addr);
                else
                    nk_printf("Error in fpga_spi_write_reg\n");
                return 0;
        }
        else if (facmode && nk_fscan(args, "rd %x %e", &reg_addr)) {
                transferOK = fpga_rd(reg_addr, &reg_data);
                if (transferOK) {
                        nk_printf("Error in fpga_spi_read_reg\n");
                        return -1;
                }
                nk_printf("Read %lx from register %lx\n", reg_data, reg_addr);
                return 0;
        } else {
            nk_printf("Syntax error\n");
        }
        return 0;
}


COMMAND(cmd_fpga,
    ">fpga                      Access FPGA\n"
    "-fpga rd <xx>              Read FPGA register\n"
    "-fpga wr <xx> <dd>         Write FPGA register\n"
)

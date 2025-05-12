#include "nkcli.h"
#include "i2c.h"

#define ADV7393_I2C_ADDR 0x2A

int nk_adv7393_write(const nk_i2c_device_t *dev, uint8_t ofst, uint8_t data)
{
    return nk_i2c_put_byte(dev, ofst, data);
}

int nk_adv7393_read(const nk_i2c_device_t *dev, uint8_t ofst, uint8_t *data)
{
    return nk_i2c_get_byte(dev, ofst, data);
}

struct setup_item {
    uint8_t addr;
    uint8_t data;
};

struct setup_item adv7393_setup_table[] =
{
    { 0x17, 0x02 },
    { 0x00, 0x1c },
    { 0x80, 0x10 },
    { 0x82, 0xc9 },
    { 0x8a, 0x0c }
};

int adv7393_init(const nk_i2c_device_t *dev)
{
    int x;
    for (x = 0; x != sizeof(adv7393_setup_table)/sizeof(struct setup_item); ++x)
    {
        if (nk_adv7393_write(dev, adv7393_setup_table[x].addr, adv7393_setup_table[x].data))
        {
            return -1;
        }
    }
    return 0;
}

const nk_i2c_device_t adv7393 =
{
    .i2c_bus = &ard_i2c_bus,
    .i2c_addr = ADV7393_I2C_ADDR
};

static int cmd_adv7393(nkinfile_t *args)
{
    uint8_t addr;
    uint8_t val;
    if (nk_fscan(args, "wr %hhu %hhu ", &addr, &val)) {
        if (nk_adv7393_write(&adv7393, addr, val))
        {
            nk_printf("I2C error\n");
        }
        else
        {
            nk_printf("Wrote 0x%x to 0x%x\n", val, addr);
        }
    } else if (nk_fscan(args, "rd %hhu ", &addr)) {
        if (nk_adv7393_read(&adv7393, addr, &val))
        {
            nk_printf("I2C error\n");
        }
        else
        {
            nk_printf("Read 0x%x from 0x%x\n", val, addr);
        }
    } else if (nk_fscan(args, "init ")) {
        nk_printf("Initialize adv7393\n");
        if (adv7393_init(&adv7393))
        {
            nk_printf("I2C error\n");
        }
        else
        {
            nk_printf("Setup complete\n");
        }
    } else {
        nk_printf("Syntax error\n");
    }
    return 0;
}

COMMAND(cmd_adv7393,
    ">adv7393                   adv7393 commands\n"
    "-adv7393 init              Initialize registers\n"
    "-adv7393 rd hh             Read adv7393 register\n"
    "-adv7393 wr hh xx          Write adv7393 register\n"
)

# Nucleo-g070rb notes

## Clocking

The design uses the 16 MHz "HSI RC" internal RC oscillator as the main clock
source and the 32 KHz "LSI RC" internal RC oscillator for the RTC clock.

It is better (more accurate) to use a crystal derived clock.  This can be
done on the Nucleo board by soldering jumper SB17.  This will provide 8 MHz
from ST-LINK (MCO output pin of ST-LINK MCU) to the HSE input pin.

After soldering this jumper, modify the design in STM32CubeMX:

* In the Pinout & Configuration tab:
    * In the System Core / RCC section: Enable High Speed Clock
    * In the RTC section: set Asynchronous Predivider value to 125 and Synchronous Predivider value to 2000.

* In the Clock Configuration tab:
    * Set PLL Source Mux to HSE.
    * Change PLLM to "/1"
    * Set RTC Clock Mux to HSE_RTC

## PA5 for Arduino D13

PA5 is overloaded: it is connected to both the on-board LED and to Arduino
D13 (often used for SPI SCLK).  The software disables the blinking LED
whenever Arduino SPI transactions are performed.

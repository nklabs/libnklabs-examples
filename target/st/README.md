# STM32 targets

## Prerequisites

STM32CubeProgrammer is used to program ST's development boards through their
on-board ST-LINK debugger (OpenOCD could also be used for this, but the
Makefile is set up to use the vendor's own tools if they are available in
Linux):

You can get STM32CubeProgrammer here:

[https://www.st.com/en/development-tools/stm32cubeprog.html](https://www.st.com/en/development-tools/stm32cubeprog.html)

Install it in /opt/STM32CubeProgrammer

STM32CubeMX is ST's "STM32Cube initialization code generator".  Install this
if you want to change project settings:

[https://www.st.com/en/development-tools/stm32cubemx.html](https://www.st.com/en/development-tools/stm32cubemx.html)

## STM32CubeMX

STM32CubeMX is used to generate the HAL and initialization code for each
target.  STM32CubeMX provides sections in the generated files where you can
add your own code.  When you make changes to the project, STM32CubeMX
will preserve these additions.

These files in particular are of note, and have a few changes:

* Core/Inc/main.h

This includes user-assigned names for each of the pins that you use in the
form of #defines.  The names can be set within the STM32CubeMX GUI.  It also
includes the header files for the entire STM32 HAL.  So this one header file
is all that you need to include in your own code.

The example application looks for the following pins:

* With a few exceptions, the application will work if the pins are missing,
but the associated feature will be disabled.

* USER_BUTTON is the "USER" button the Nucleo board.

* ARD_ are pins associated with the Arduino interface of the Nucleo board.

* CONSOLE_ are pins associated with the console UART.

~~~c
/* Private defines -----------------------------------------------------------*/
#define USER_BUTTON_Pin GPIO_PIN_13
#define USER_BUTTON_GPIO_Port GPIOC
#define USER_BUTTON_EXTI_IRQn EXTI4_15_IRQn
#define MCO_Pin GPIO_PIN_0
#define MCO_GPIO_Port GPIOF
#define ARD_A0_Pin GPIO_PIN_0
#define ARD_A0_GPIO_Port GPIOA
#define ARD_A1_Pin GPIO_PIN_1
#define ARD_A1_GPIO_Port GPIOA
#define CONSOLE_TX_Pin GPIO_PIN_2
#define CONSOLE_TX_GPIO_Port GPIOA
#define CONSOLE_RX_Pin GPIO_PIN_3
#define CONSOLE_RX_GPIO_Port GPIOA
#define ARD_A2_Pin GPIO_PIN_4
#define ARD_A2_GPIO_Port GPIOA
#define ARD_D13_Pin GPIO_PIN_5
#define ARD_D13_GPIO_Port GPIOA
#define ARD_D12_Pin GPIO_PIN_6
#define ARD_D12_GPIO_Port GPIOA
#define ARD_D11_Pin GPIO_PIN_7
#define ARD_D11_GPIO_Port GPIOA
#define ARD_D1_Pin GPIO_PIN_4
#define ARD_D1_GPIO_Port GPIOC
#define ARD_D0_Pin GPIO_PIN_5
#define ARD_D0_GPIO_Port GPIOC
#define ARD_D10_Pin GPIO_PIN_0
#define ARD_D10_GPIO_Port GPIOB
#define ARD_A3_Pin GPIO_PIN_1
#define ARD_A3_GPIO_Port GPIOB
#define ARD_A4_Pin GPIO_PIN_11
#define ARD_A4_GPIO_Port GPIOB
#define ARD_A5_Pin GPIO_PIN_12
#define ARD_A5_GPIO_Port GPIOB
#define ARD_D7_Pin GPIO_PIN_8
#define ARD_D7_GPIO_Port GPIOA
#define ARD_D8_Pin GPIO_PIN_9
#define ARD_D8_GPIO_Port GPIOA
#define ARD_D9_Pin GPIO_PIN_7
#define ARD_D9_GPIO_Port GPIOC
#define ARD_D2_Pin GPIO_PIN_10
#define ARD_D2_GPIO_Port GPIOA
#define TMS_Pin GPIO_PIN_13
#define TMS_GPIO_Port GPIOA
#define TCK_Pin GPIO_PIN_14
#define TCK_GPIO_Port GPIOA
#define ARD_D3_Pin GPIO_PIN_3
#define ARD_D3_GPIO_Port GPIOB
#define ARD_D5_Pin GPIO_PIN_4
#define ARD_D5_GPIO_Port GPIOB
#define ARD_D4_Pin GPIO_PIN_5
#define ARD_D4_GPIO_Port GPIOB
#define ARD_D6_Pin GPIO_PIN_6
#define ARD_D6_GPIO_Port GPIOB
#define ARD_I2C_SCL_Pin GPIO_PIN_8
#define ARD_I2C_SCL_GPIO_Port GPIOB
#define ARD_I2C_SDA_Pin GPIO_PIN_9
#define ARD_I2C_SDA_GPIO_Port GPIOB
~~~

Unfortunately, STM32CubeMX does not give us a way to provide user defined names
for peripherals.  Therefore we modify Core/Inc/main.h to include bindings
between the peripherals we expect to exist and the ones actually used.  The
following code is thus added to Core/Inc/main.h:

(also a few declarations are included for functions that we have the
auto-generated code call).

~~~c
/* USER CODE BEGIN Private defines */

// Name the devices we use

#define MAIN_CONSOLE_UART huart2
extern UART_HandleTypeDef huart2;

#define ARD_SPI hspi1
extern SPI_HandleTypeDef hspi1;

#define ARD_I2C hi2c1
extern I2C_HandleTypeDef hi2c1;

#define MAIN_WDT hiwdg
extern IWDG_HandleTypeDef hiwdg;

// Demo app functions called by main.h

void user_main(void);

// Called by stm32f0xx_it.c

void nk_uart_irq_handler(void);

/* USER CODE END Private defines */
~~~

* Core/Src/main.c

This file has the main() function that is called after startup.  We make
just one change to this file:

~~~c
  /* USER CODE BEGIN 2 */

  user_main();

  /* USER CODE END 2 */
~~~

Transfer control to the demo application main application.

* Core/Src/stmxxx_it.c

This file contains the interrupt handlers.  Usually these just call generic
handlers in the HAL, but for the case of the UART we use our own:

~~~c
  /* USER CODE BEGIN USART2_IRQn 0 */

  nk_uart_irq_handler();
  return ;

  /* USER CODE END USART2_IRQn 0 */
~~~ 


* Makefile

We make a few changes to the auto-generated Makefile.  Luckily STM32CubeMX
preserves these changes:

* Add the -Os flag to OPT

~~~make
OPT = -Og -Os
~~~

* Include our our own Makefile

~~~make
# Add our files
include ../nucleo.mk
~~~

This adds the libnklabs and demo application files to the build.  It also
automatically inserts the build date, git hash and version numbers to an
auto-generated "version.o" file.  This is so that the CLI "info" command can
print this information.

It also provides a few phony targets:

	make flash        Programs the board with STLINK using STM32Programmer
	make stlink       Programs the board with STLINK using openocd
        make bump_minor   Bumps the minor version number in the VERSION_MINOR file
        make bump_major   Bumps the major version number in the VERSION_MAJOR file

* Include the version.o file in the buid.


~~~make
$(BUILD_DIR)/$(TARGET).elf: $(OBJECTS) Makefile $(BUILD_DIR)/version.o
	$(CC) $(OBJECTS) $(BUILD_DIR)/version.o $(LDFLAGS) -o $@
        $(SZ) $@
~~~

* C_DEFS

One note about the STM32CubeMX Makefile.  The target device is defined in
the C_DEFS variable.  For example, STM32F030R8 is defined as -DSTM32F030x8.

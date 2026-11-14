#ifndef nt_ppd_GPIO_Registers_H
#define nt_ppd_GPIO_Registers_H

#include <stdint.h>

typedef struct
{
  volatile uint32_t MODER;   /*!< GPIO port mode register,               Address offset: 0x00 */
  volatile uint32_t OTYPER;  /*!< GPIO port output type register,        Address offset: 0x04 */
  volatile uint32_t OSPEEDR; /*!< GPIO port output speed register,       Address offset: 0x08 */
  volatile uint32_t PUPDR;   /*!< GPIO port pull-up/pull-down register,  Address offset: 0x0C */
  volatile uint32_t IDR;     /*!< GPIO port input data register,         Address offset: 0x10 */
  volatile uint32_t ODR;     /*!< GPIO port output data register,        Address offset: 0x14 */
  volatile uint32_t BSRR;    /*!< GPIO port bit set/reset register,      Address offset: 0x18 */
  volatile uint32_t LCKR;    /*!< GPIO port configuration lock register, Address offset: 0x1C */
  volatile uint32_t AFR[2];  /*!< GPIO alternate function registers,     Address offset: 0x20-0x24 */
} nt_ppd_Gpio_RegistersT;

/* GPIO Base Addresses */
#define nt_ppd_GPIO_GPIOA_BASE_ADDR (0x40020000U)
#define nt_ppd_GPIO_GPIOB_BASE_ADDR (0x40020400U)
#define nt_ppd_GPIO_GPIOC_BASE_ADDR (0x40020800U)
#define nt_ppd_GPIO_GPIOD_BASE_ADDR (0x40020C00U)
#define nt_ppd_GPIO_GPIOE_BASE_ADDR (0x40021000U)

/* GPIO Peripheral Pointers */
#define nt_ppd_GPIO_GPIOA_PTR ((nt_ppd_Gpio_RegistersT*) nt_ppd_GPIO_GPIOA_BASE_ADDR)
#define nt_ppd_GPIO_GPIOB_PTR ((nt_ppd_Gpio_RegistersT*) nt_ppd_GPIO_GPIOB_BASE_ADDR)
#define nt_ppd_GPIO_GPIOC_PTR ((nt_ppd_Gpio_RegistersT*) nt_ppd_GPIO_GPIOC_BASE_ADDR)
#define nt_ppd_GPIO_GPIOD_PTR ((nt_ppd_Gpio_RegistersT*) nt_ppd_GPIO_GPIOD_BASE_ADDR)
#define nt_ppd_GPIO_GPIOE_PTR ((nt_ppd_Gpio_RegistersT*) nt_ppd_GPIO_GPIOE_BASE_ADDR)

#endif
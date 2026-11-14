#include "nt_ppd_gpio.h"

void nt_ppd_GpioMcal_LedInit(void)
{
	// Configure PA6 as output
	nt_ppd_GPIO_GPIOA_PTR->MODER   &= ~(3UL << (6 * 2));
	nt_ppd_GPIO_GPIOA_PTR->MODER   |= (1UL << (6 * 2));
	nt_ppd_GPIO_GPIOA_PTR->OTYPER  &= ~(1UL << 6);
	nt_ppd_GPIO_GPIOA_PTR->PUPDR   &= ~(3UL << (6 * 2));
	nt_ppd_GPIO_GPIOA_PTR->OSPEEDR &= ~(3UL << (6 * 2));

	// Configure PA7 as output
	nt_ppd_GPIO_GPIOA_PTR->MODER   &= ~(3UL << (7 * 2));
	nt_ppd_GPIO_GPIOA_PTR->MODER   |= (1UL << (7 * 2));
	nt_ppd_GPIO_GPIOA_PTR->OTYPER  &= ~(1UL << 7);
	nt_ppd_GPIO_GPIOA_PTR->PUPDR   &= ~(3UL << (7 * 2));
	nt_ppd_GPIO_GPIOA_PTR->OSPEEDR &= ~(3UL << (7 * 2));

	// Set initial state to LOW
	nt_ppd_GPIO_GPIOA_PTR->BSRR = ((1UL << 22) | (1UL << 23));
}

void nt_ppd_GpioMcal_Usart1Init(void)
{
	// Configure PA9, PA10 as USART1 output
	nt_ppd_GPIO_GPIOA_PTR->MODER   &= ~((3UL << (9 * 2)) | (3UL << (10 * 2)));
	nt_ppd_GPIO_GPIOA_PTR->MODER   |= ((2UL << (9 * 2)) | (2UL << (10 * 2)));
	nt_ppd_GPIO_GPIOA_PTR->OTYPER  &= ~((1UL << 9) | (1UL << 10));
	nt_ppd_GPIO_GPIOA_PTR->PUPDR   &= ~((3UL << (9 * 2)) | (3UL << (10 * 2)));
	nt_ppd_GPIO_GPIOA_PTR->OSPEEDR |= ((3UL << (9 * 2)) | (3UL << (10 * 2)));
	nt_ppd_GPIO_GPIOA_PTR->AFR[1]  |= ((nt_ppd_GPIO_GPIOA_PTR->AFR[1] & ~((0xFUL << 4) | (0xFUL << 8))) | (7UL << 4) | (7UL << 8));
}

void nt_ppd_GpioMcal_WritePin(void)
{
	nt_ppd_GPIO_GPIOA_PTR->BSRR = ((1UL << 6) | (1UL << 7)); // PA6 and PA7 HIGH (set bits)
}

void nt_ppd_GpioMcal_ResetPin(void)
{
	nt_ppd_GPIO_GPIOA_PTR->BSRR = ((1UL << 22) | (1UL << 23)); // PA6 and PA7 LOW (reset bits)
}

void nt_ppd_GpioMcal_TogglePin(void)
{
	nt_ppd_GPIO_GPIOA_PTR->ODR ^= (1UL << 6); // Toggle PA6
	nt_ppd_GPIO_GPIOA_PTR->ODR ^= (1UL << 7); // Toggle PA7
}

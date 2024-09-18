#include <libopencm3/cm3/nvic.h>
#include <libopencm3/stm32/exti.h>
#include <libopencm3/stm32/flash.h>
#include <libopencm3/stm32/gpio.h>
#include <libopencm3/stm32/rcc.h>
#include <libopencm3/stm32/timer.h>
#include <libopencm3/stm32/usart.h>

#define LED_GREEN_PORT GPIOA
#define LED_GREEN_PIN GPIO5

static void rcc_setup(void)
{
	rcc_clock_setup_pll(&rcc_hsi16_configs[RCC_CLOCK_VRANGE1_80MHZ]);

	// Enable GPIOA clock
	rcc_periph_clock_enable(RCC_GPIOA);
}

static void gpio_setup(void)
{
	gpio_mode_setup(GPIOA, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE, GPIO5);
}

static void delay_cycles(uint32_t cycles)
{
	for (uint32_t i = 0; i < cycles; i++) {
		__asm__("NOP");
	}
}

int main(void)
{
    rcc_setup();
	gpio_setup();

	while (1) {

		gpio_toggle(LED_GREEN_PORT, LED_GREEN_PIN);

		//80000000 cycles = 1 second @ 80MHz with only 1 instruction
		// we have more than 1 instruction, so divide by 4 
		delay_cycles(80000000 / 4);
	}

	return 0;
}
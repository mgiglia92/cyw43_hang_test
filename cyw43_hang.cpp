#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <iostream>


//Pico SDK
#include "pico/stdlib.h"
#include "pico/cyw43_arch.h"
#include "hardware/adc.h"
#include "hardware/i2c.h"
#include "hardware/irq.h"
#include "hardware/gpio.h"
using namespace std;

volatile long countl, countr = 0;
const int lpin = 12;
const int rpin = 13;

const uint32_t isr_events
	= GPIO_IRQ_EDGE_FALL | GPIO_IRQ_EDGE_RISE;

void isr(void)
{
    // cout << "isr activated" << '\n';
    if(gpio_get_irq_event_mask(lpin) & isr_events)
    {gpio_acknowledge_irq(lpin, isr_events);
        countl++;
    }

}

void isr2(void)
{
    if(gpio_get_irq_event_mask(rpin) & isr_events)
    {gpio_acknowledge_irq(rpin, isr_events);
        countr++;
    }
}

void init_isr(void)
{
    irq_set_enabled(IO_IRQ_BANK0, false);
	gpio_set_input_enabled(lpin, true);
    gpio_set_irq_enabled(lpin, isr_events, true);
    gpio_add_raw_irq_handler(lpin, &isr);
	gpio_set_input_enabled(rpin, true);
    gpio_set_irq_enabled(rpin, isr_events, true);
    gpio_add_raw_irq_handler(rpin, &isr2);
    irq_set_enabled(IO_IRQ_BANK0, true);
}

int main()
{
    stdio_init_all();    
    init_isr();

    sleep_ms(1500);
    cout << "Starting..." << '\n';
    if(cyw43_arch_init())
    {
        cout << "CYW43 INIT failed!" << '\n';
    }

    cout << "init worked!" << '\n';
    
    cyw43_arch_gpio_put(CYW43_WL_GPIO_LED_PIN, 1);
    
    while(true)
    {   
        cyw43_arch_poll();
        sleep_ms(100);
        // cyw43_arch_gpio_put(CYW43_WL_GPIO_LED_PIN, !(cyw43_arch_gpio_get(0)));
        cout << "left: " << countl << " right: " << countr;
        cout << '\n';
    }

}
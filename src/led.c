#include "led.h"
#include "gd32vf103.h"

// ------------------------------------------------------------------------
/* BUILTIN LED OF LONGAN BOARDS IS PIN PC13(Red) PA1(Green) PA2(Blue) */
void led_init()
{
    /* enable the led clock */
    rcu_periph_clock_enable(RCU_GPIOA);
    rcu_periph_clock_enable(RCU_GPIOC);
    /* configure led GPIO port */
    gpio_init(GPIOA, GPIO_MODE_OUT_PP, GPIO_OSPEED_50MHZ, GPIO_PIN_1 | GPIO_PIN_2);
    gpio_init(GPIOC, GPIO_MODE_OUT_PP, GPIO_OSPEED_50MHZ, GPIO_PIN_13);
    /* Initialize the output port */
    GPIO_BOP(GPIOA) = GPIO_PIN_1 | GPIO_PIN_2;
    GPIO_BOP(GPIOC) = GPIO_PIN_13;
}

/*
     * LED is hardwired with 3.3V on the anode, we control the cathode
     * (negative side) so we need to use reversed logic: bit clear is on.
     */
void led_set(int c) // c[0:2] = RGB
{
    if (c & 1)
        GPIO_BC(GPIOC) = GPIO_PIN_13; // red
    else
        GPIO_BOP(GPIOC) = GPIO_PIN_13;
    if (c & 2)
        GPIO_BC(GPIOA) = GPIO_PIN_1; // green
    else
        GPIO_BOP(GPIOA) = GPIO_PIN_1;
    if (c & 4)
        GPIO_BC(GPIOA) = GPIO_PIN_2; // blue
    else
        GPIO_BOP(GPIOA) = GPIO_PIN_2;
}

// ------------------------------------------------------------------------

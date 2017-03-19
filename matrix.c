#include <avr/eeprom.h>
#include <util/delay.h>
#include "include/matrix.h"

static void reset(void);
static void init(void);

static void
toggle(uint8_t pin)
{
  PORTB |= (1 << pin);
  PORTB &= ~(1 << pin);
}

static void
ntoggle(uint8_t n, uint8_t pin)
{
  for (uint8_t i = 0; i < n; i++) {
    toggle(pin);
  }
}

static void
on(uint8_t cathode, uint8_t anode)
{
  reset();
  
  /* anode */
  PORTB |= (1 << SER);
  toggle(SCK);
  PORTB &= ~(1 << SER);
  ntoggle(anode, SCK);
  
  /* cathode */
  if (cathode > 3) {
    PORTB |= (1 << PRT);
    PORTB &= ~(1 << SER);
    ntoggle(4, SCK);
  }
  else
  {
    ntoggle(3-cathode, SCK);
    PORTB |= (1 << SER);
    toggle(SCK);
    PORTB &= ~(1 << SER);
    ntoggle(cathode, SCK);
  }
  
  toggle(RCK);
}

static light matrix[20];

static void
init()
{
  for (uint8_t i = 0; i < 20; i++) {
    matrix[i].cathode = (uint8_t)eeprom_read_byte((uint8_t *)(i*2));
    matrix[i].anode = (uint8_t)eeprom_read_byte((uint8_t *)(i*2+1));
  }

  DDRB |= (1 << SER) | (1 << SCK) | (1 << RCK) | (1 << CLR) | (1 << PRT);
  reset();
}

static void
reset()
{
  PORTB &= ~(1 << CLR);
  PORTB &= ~(1 << PRT);
  PORTB |= (1 << CLR);
  toggle(RCK);
}

static void
flash_all(uint8_t n, uint8_t time)
{
  for (uint8_t i = 0; i < n; i++) {
    for (uint8_t i = 0; i < 20; i++) {
      on(matrix[i].cathode, matrix[i].anode);
      _delay_ms(time);
    }
  }
}

static void
flash_cycle(uint8_t n, uint8_t time)
{
  for (uint8_t i = 0; i < n; i++) {
    for (uint8_t j = 0; j < FLASH_CYCLE_S; j++) {
      uint8_t n = (uint8_t)eeprom_read_byte((uint8_t *)(FLASH_CYCLE_P + j));
      on(matrix[n].cathode, matrix[n].anode);
      _delay_ms(time);
    }
  }
}

static void
flash_block(uint8_t n, uint8_t time, uint8_t position, uint8_t size)
{
  for (uint8_t i = 0; i < n; i++) {
    for (uint8_t j = 0; j < size; j++) {
      uint8_t n = (uint8_t)eeprom_read_byte((uint8_t *)(position + j));
      on(matrix[n].cathode, matrix[n].anode);
      _delay_ms(time);
    }
  }
}

static void
flash_blue(uint8_t n, uint8_t time)
{
  flash_block(n, time, FLASH_BLUE_P, FLASH_BLUE_S);
}

static void
flash_white(uint8_t n, uint8_t time)
{
  flash_block(n, time, FLASH_WHITE_P, FLASH_WHITE_S);
}

static void
flash_green(uint8_t n, uint8_t time)
{
  flash_block(n, time, FLASH_GREEN_P, FLASH_GREEN_S);
}

static void
flash_yellow(uint8_t n, uint8_t time)
{
  flash_block(n, time, FLASH_YELLOW_P, FLASH_YELLOW_S);
}

static void
flash_red(uint8_t n, uint8_t time)
{
  flash_block(n, time, FLASH_RED_P, FLASH_RED_S);
}

static void
flash_colors(uint8_t n, uint8_t time)
{
  for (uint8_t i = 0; i< n; i++) {
    flash_blue(10, 4);
    _delay_ms(time);
    flash_white(10, 4);
    _delay_ms(time);
    flash_green(10, 4);
    _delay_ms(time);
    flash_yellow(10, 4);
    _delay_ms(time);
    flash_red(10, 4);
    _delay_ms(time);
    flash_yellow(10, 4);
    _delay_ms(time);
    flash_green(10, 4);
    _delay_ms(time);
    flash_white(10, 4);
    _delay_ms(time);
  }
}

int
main()
{
  init();

  for (;;) {
    flash_colors(10, 50);
    flash_all(5, 200);
    flash_cycle(10, 200);
  }

  return 0;
}

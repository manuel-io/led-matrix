#ifndef MATRIX
#define MATRIX

typedef struct {
  uint8_t cathode;
  uint8_t anode;
} __attribute__((packed)) light;

#define SER PB3
#define SCK PB5
#define RCK PB2
#define CLR PB1
#define PRT PB0

#define FLASH_BLUE_P 40
#define FLASH_BLUE_S 4

#define FLASH_WHITE_P 44
#define FLASH_WHITE_S 4

#define FLASH_GREEN_P 48
#define FLASH_GREEN_S 4

#define FLASH_YELLOW_P 52
#define FLASH_YELLOW_S 4

#define FLASH_RED_P 56
#define FLASH_RED_S 4

#define FLASH_CYCLE_P 60
#define FLASH_CYCLE_S 14

/* BLUE */
#define LED01_K 4
#define LED01_A 1

#define LED02_K 4
#define LED02_A 0

#define LED03_K 4
#define LED03_A 2

#define LED04_K 4
#define LED04_A 3

/* WHITE */
#define LED05_K 0
#define LED05_A 1

#define LED06_K 0
#define LED06_A 0

#define LED07_K 0
#define LED07_A 3

#define LED08_K 0
#define LED08_A 2

/* GREEN */

#define LED09_K 1
#define LED09_A 1

#define LED10_K 1
#define LED10_A 0

#define LED11_K 1
#define LED11_A 3

#define LED12_K 1
#define LED12_A 2

/* YELLOW */

#define LED13_K 2
#define LED13_A 1

#define LED14_K 2
#define LED14_A 0

#define LED15_K 2
#define LED15_A 3

#define LED16_K 2
#define LED16_A 2

/* RED */

#define LED17_K 3
#define LED17_A 1

#define LED18_K 3
#define LED18_A 0

#define LED19_K 3
#define LED19_A 3

#define LED20_K 3
#define LED20_A 2

#endif /* MATRIX */

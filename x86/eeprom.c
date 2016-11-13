#include <stdint.h>
#include <stdio.h> 
#include "../include/matrix.h"

int
main(int argc, char **argv)
{
  light board[] = {
    {LED01_K, LED01_A},
    {LED02_K, LED02_A},
    {LED03_K, LED03_A},
    {LED04_K, LED04_A},
    {LED05_K, LED05_A},
    {LED06_K, LED06_A},
    {LED07_K, LED07_A},
    {LED08_K, LED08_A},
    {LED09_K, LED09_A},
    {LED10_K, LED10_A},
    {LED11_K, LED11_A},
    {LED12_K, LED12_A},
    {LED13_K, LED13_A},
    {LED14_K, LED14_A},
    {LED15_K, LED15_A},
    {LED16_K, LED16_A},
    {LED17_K, LED17_A},
    {LED18_K, LED18_A},
    {LED19_K, LED19_A},
    {LED20_K, LED20_A}
  };

  uint8_t blue[] = {0, 1, 2, 3};
  uint8_t white[] = {4, 5, 6, 7};
  uint8_t green[] = {8, 9, 10, 11};
  uint8_t yellow[] = {12, 13, 14, 15};
  uint8_t red[] = {16, 17, 18, 19};
  uint8_t cycle[] = {1, 4, 8, 12, 16, 17, 18, 19, 15, 11, 7, 3, 2, 0};

  light buffer[sizeof(board)];
  printf("Matrix size: %lu\n", sizeof(board)/sizeof(light));
  printf("Blue size: %lu\n", sizeof(blue));
  printf("White size: %lu\n", sizeof(white));
  printf("Green size: %lu\n", sizeof(green));
  printf("Yellow size: %lu\n", sizeof(yellow));
  printf("Red size: %lu\n", sizeof(red));
  printf("Cycle size: %lu\n", sizeof(cycle));

  FILE *ptr;
  ptr = fopen("eeprom.bin","wb");
  fwrite(&board, sizeof(light), sizeof(board)/sizeof(light), ptr);
  fwrite(blue, sizeof(uint8_t), sizeof(blue), ptr);
  fwrite(white, sizeof(uint8_t), sizeof(white), ptr);
  fwrite(green, sizeof(uint8_t), sizeof(green), ptr);
  fwrite(yellow, sizeof(uint8_t), sizeof(yellow), ptr);
  fwrite(red, sizeof(uint8_t), sizeof(red), ptr);
  fwrite(cycle, sizeof(uint8_t), sizeof(cycle), ptr);
  fclose(ptr);

  return 0;
}

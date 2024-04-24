#include "HX711_light.h"

void HX711_init() {
  HX_DDR_DAT &= ~(1 << HX_DAT); // Data input
  HX_DDR_CLK |= (1 << HX_CLK); // Clock output

  setClk(0);
  // Perform a dummy read to ensure the desired settings are set
  // from the first data acquisition on.
  readData();
}

uint8_t dataReady(){
  if(READ_DAT == 0) return 1;
  return 0;
}

int32_t readData() {
  int i;
  // Wait for data to be available.
  while (!dataReady());
  int32_t result = 0;
  // Read 24 data bits.
  for (i = 23; i >= 0; --i) {
    setClk(1);
    result |= (int32_t)READ_DAT << i;
    setClk(0);
  }
  // Determine number of additional cycles based on the settings.
  uint8_t num_extra_cycles = 0;
  if(CH == 128)
    num_extra_cycles = 1;
  else if(CH == 64)
    num_extra_cycles = 3;
  else if(CH == 32)
    num_extra_cycles = 2;
  else
    return -1;

  // Additional clock cycles to communicate settings.
  for (i = 0; i < num_extra_cycles; ++i) {
    setClk(1);
    setClk(0);
  }
  // Extend the sign bit into the highest byte of result.
  if(result & 1UL << 23)
    result |= 0xFFUL << 24;
  else
    result |= 0x00UL << 24;

  return result;
}

void update(int32_t *result) {
  if(dataReady()){
    *result = readData();
  }
}

void setClk(uint8_t n) {
  if(n)
    HX_PORT_CLK |= (1 << HX_CLK);
  else
    HX_PORT_CLK &= ~ (1 << HX_CLK);
}

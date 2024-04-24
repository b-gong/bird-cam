#include <avr/io.h>

#define HX_DDR_DAT DDRD
#define HX_DDR_CLK DDRD
#define HX_DAT PD5
#define HX_CLK PD4
#define HX_PIN_DAT PIND
#define HX_PORT_CLK PORTD
#define READ_DAT ((HX_PIN_DAT & (1 << HX_DAT)) != 0)
#define CH 128
// #define CH 64
// #define CH 32

void HX711_init();
uint8_t dataReady();
int32_t readData();
void update(int32_t *result);
void setClk(uint8_t n);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  pinMode(14, OUTPUT);

  HX711_init();
}

void loop() {
  // put your main code here, to run repeatedly:
  int32_t data = readData();
  Serial.println(data);
  _delay_ms(100);
}

void HX711_init() {
  HX_DDR_DAT &= ~(1 << HX_DAT); // Data input
  HX_DDR_CLK |= (1 << HX_CLK); // Clock output

  setClk(0);
  // Perform a dummy read to ensure the desired settings are set
  // from the first data acquisition on.
  readData();
}

uint8_t dataReady(){
  //Serial.println(READ_DAT);
  if(READ_DAT == 0) return 1;
  return 0;
}

int32_t readData() {
  int i;
  // Wait for data to be available.
  Serial.println("hi");
  while (!dataReady());
  //Serial.println("bye");
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

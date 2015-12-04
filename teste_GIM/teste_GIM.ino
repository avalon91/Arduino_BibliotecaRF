#include "Radio.h"

int array[4];

void setup() {
  Radio(50, T);

}

void loop() {
  Radio.EnvieArray(array[4]);

}

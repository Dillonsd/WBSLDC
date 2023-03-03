#include "feature_fifo.h"

static float feature_buffer[1200];
static uint16_t fifo_index = 0;

void feature_fifo_push(float* feature) {
  if (fifo_index + 6 > 1200) {
    for (uint16_t i = 6; i < 1200; i++) {
      feature_buffer[i - 6] = feature_buffer[i];
    }
    fifo_index -= 6;
  }
  for (uint8_t i = 0; i < 6; i++) {
    feature_buffer[fifo_index] = feature[i];
    fifo_index++;
  }
}

void feature_fifo_get(float* buffer, uint16_t length) {
  for (uint16_t i = 0; i < length; i++) {
    buffer[i] = feature_buffer[i];
  }
}

uint16_t feature_fifo_get_count() { return fifo_index; }

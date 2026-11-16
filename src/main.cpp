#include <Arduino.h>
#include <Adafruit_NeoPixel.h>

#define NEO_PIN 45
#define LED_COUNT 1

void task_led_blinky(void *pvParameters)
{
  pinMode(GPIO_NUM_48, OUTPUT);

  while (1)
  {
    // LED sang 2 giay
    digitalWrite(GPIO_NUM_48, HIGH);
    vTaskDelay(pdMS_TO_TICKS(1000));

    // LED tat 2 giay
    digitalWrite(GPIO_NUM_48, LOW);
    vTaskDelay(pdMS_TO_TICKS(1000));
  }
}

void task_traffic_light(void *pvParameters)
{
  Adafruit_NeoPixel strip(
      LED_COUNT, NEO_PIN, NEO_GRB + NEO_KHZ800);

  strip.begin();
  strip.clear();
  strip.show();

  while (1)
  {
    // 1. DO
    strip.setPixelColor(0, strip.Color(255, 0, 0));
    strip.show();
    vTaskDelay(pdMS_TO_TICKS(7000));

    // 2. VANG
    strip.setPixelColor(0, strip.Color(255, 255, 0));
    strip.show();
    vTaskDelay(pdMS_TO_TICKS(2000));

    // 3. XANH LA
    strip.setPixelColor(0, strip.Color(0, 255, 0));
    strip.show();
    vTaskDelay(pdMS_TO_TICKS(5000));
  }
}

void setup()
{
  Serial.begin(115200);

  xTaskCreate(
      task_led_blinky,
      "LED Blinky",
      2048,
      NULL,
      2,
      NULL);

  xTaskCreate(
      task_traffic_light,
      "Traffic Light",
      2048,
      NULL,
      2,
      NULL);
}

void loop()
{
}

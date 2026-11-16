#include <Arduino.h>
#include <Adafruit_NeoPixel.h>

#define NEO_PIN 45
#define LED_COUNT 1

void task_led_blinky(void *pvParameters)
{
  pinMode(GPIO_NUM_48, OUTPUT);

  while (1)
  {
    // LED sang 1.5 giay
    digitalWrite(GPIO_NUM_48, HIGH);
    vTaskDelay(pdMS_TO_TICKS(1500));

    // LED tat 0.5 giay
    digitalWrite(GPIO_NUM_48, LOW);
    vTaskDelay(pdMS_TO_TICKS(500));
  }
}

void task_neo_blinky(void *pvParameters)
{
  Adafruit_NeoPixel strip(
      LED_COUNT, NEO_PIN, NEO_GRB + NEO_KHZ800);

  strip.begin();
  strip.clear();
  strip.show();

  while (1)
  {
    // Mau DO trong 1 giay
    strip.setPixelColor(0, strip.Color(255, 0, 0));
    strip.show();
    vTaskDelay(pdMS_TO_TICKS(1000));

    // Mau XANH LA trong 2 giay
    strip.setPixelColor(0, strip.Color(0, 255, 0));
    strip.show();
    vTaskDelay(pdMS_TO_TICKS(2000));

    // Mau XANH DUONG trong 2 giay
    strip.setPixelColor(0, strip.Color(0, 0, 255));
    strip.show();
    vTaskDelay(pdMS_TO_TICKS(2000));
  }
}

void setup()
{
  Serial.begin(115200);

  xTaskCreate(
      task_led_blinky,
      "LED Control",
      2048,
      NULL,
      2,
      NULL);

  xTaskCreate(
      task_neo_blinky,
      "NEO Control",
      2048,
      NULL,
      2,
      NULL);
}

void loop()
{
}

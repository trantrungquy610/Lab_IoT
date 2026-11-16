#include <Arduino.h>
#include <Adafruit_NeoPixel.h>

#define NEO_PIN 45
#define LED_COUNT 1

volatile bool led_state = false;

void neo_blinky(void *pvParameters)
{

  Adafruit_NeoPixel strip(LED_COUNT, NEO_PIN, NEO_GRB + NEO_KHZ800);
  strip.begin();
  // Set all pixels to off to start
  strip.clear();
  strip.show();

  while (1)
  {
    if (led_state == true)
    {
      // LED sang -> NeoPixel mau DO
      strip.setPixelColor(0, strip.Color(255, 0, 0));
    }
    else
    {
      // LED tat -> NeoPixel mau DEN
      strip.setPixelColor(0, strip.Color(0, 0, 0));
    }

    strip.show();

    // Kiem tra trang thai moi sau 10 ms
    vTaskDelay(pdMS_TO_TICKS(10));
  }
}

void led_blinky(void *pvParameters)
{
  pinMode(GPIO_NUM_48, OUTPUT); // Initialize LED pin

  while (1)
  {
    digitalWrite(GPIO_NUM_48, HIGH);
    led_state = true;
    vTaskDelay(pdMS_TO_TICKS(2000));

    // Tat LED trong 2 giay
    digitalWrite(GPIO_NUM_48, LOW);
    led_state = false;
    vTaskDelay(pdMS_TO_TICKS(2000));
  }
}

void setup()
{
  // put your setup code here, to run once for task creation
  Serial.begin(115200);
  xTaskCreate(led_blinky, "LED Control", 2048, NULL, 2, NULL);
  xTaskCreate(neo_blinky, "NEO Control", 2048, NULL, 2, NULL);
}

void loop()
{
  // Serial.println("Hello Custom Board");
  // delay(1000);
}

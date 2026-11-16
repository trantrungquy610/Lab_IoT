#include <Arduino.h>
#include <Adafruit_NeoPixel.h>

#define LED_COUNT 1

void task_led_blinky(void *pvParameters)
{
  pinMode(GPIO_NUM_48, OUTPUT); // Initialize LED pin

  while (1)
  {
    digitalWrite(GPIO_NUM_48, HIGH); // Turn ON LED
    vTaskDelay(1000);
    digitalWrite(GPIO_NUM_48, LOW); // Turn OFF LED
    vTaskDelay(2000);
  }
}

void setup()
{
  // put your setup code here, to run once for task creation
  Serial.begin(115200);
  xTaskCreate(task_led_blinky, "LED Control", 2048, NULL, 2, NULL);
}

void loop()
{
  // Serial.println("Hello Custom Board");
  // delay(1000);
}

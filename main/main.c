/* Hello World Example

   This example code is in the Public Domain (or CC0 licensed, at your option.)

   Unless required by applicable law or agreed to in writing, this
   software is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
   CONDITIONS OF ANY KIND, either express or implied.
*/
#include <stdio.h>
#include "sdkconfig.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"
#if ESP_IDF_VERSION <= ESP_IDF_VERSION_VAL(5, 0, 0)
#include "esp_system.h"
#include "esp_spi_flash.h"
#else
#include "esp_chip_info.h"
#include "esp_flash.h" 
#endif

#define LED_GPIO GPIO_NUM_2
#define BTN_GPIO GPIO_NUM_4

#define DOT     10
#define DASH    (DOT * 3)   
#define PAUSE   (DOT)
#define BREAK   (DOT * 5)
#define END     0

uint8_t mE[] = {DOT, END};
uint8_t mJ[] = {DOT, DASH, DASH, DASH, END};
uint8_t mS[] = {DOT, DOT, DOT, END};
uint8_t mU[] = {DOT, DOT, DASH, END};
uint8_t mEND[] = {END};
uint8_t *name[] = {mJ, mE, mS, mU, mS, mEND}; 

void delayMs(uint16_t ms)
{
    vTaskDelay(ms / portTICK_PERIOD_MS);
}

static void update_led(void)
{
    /* Set the GPIO level according to the button state (LOW or HIGH)
       Inverting button as the button will read '0' when pressed,
       and we want the LED to turn on when the button is pressed. */
    gpio_set_level(LED_GPIO, !gpio_get_level(BTN_GPIO)); 
}

static void configure_led(void)
{
    gpio_reset_pin(LED_GPIO);
    gpio_reset_pin(BTN_GPIO);
    /* Set LED GPIO as a push/pull output */
    gpio_set_direction(LED_GPIO, GPIO_MODE_OUTPUT);
    /* Set LED GPIO as a push/pull output */
    gpio_set_direction(BTN_GPIO, GPIO_MODE_INPUT);
    gpio_pullup_en(BTN_GPIO);
}

void sendMorse(uint8_t *data[])
{

    //while (data)
    {
        //sendLetter();
    }
}

void app_main(void)
{
    printf("Hello world!\n");

#if ESP_IDF_VERSION <= ESP_IDF_VERSION_VAL(5, 0, 0)
    /* Print chip information */
    esp_chip_info_t chip_info;
    esp_chip_info(&chip_info);
    printf("This is %s chip with %d CPU core(s), WiFi%s%s, ",
            CONFIG_IDF_TARGET,
            chip_info.cores,
            (chip_info.features & CHIP_FEATURE_BT) ? "/BT" : "",
            (chip_info.features & CHIP_FEATURE_BLE) ? "/BLE" : "");

    printf("silicon revision %d, ", chip_info.revision);

    printf("%dMB %s flash\n", spi_flash_get_chip_size() / (1024 * 1024),
            (chip_info.features & CHIP_FEATURE_EMB_FLASH) ? "embedded" : "external");

    printf("Minimum free heap size: %d bytes\n", esp_get_minimum_free_heap_size());
#else
    /* Print chip information */
    esp_chip_info_t chip_info;
    esp_chip_info(&chip_info);
    printf("This is %s chip with %d CPU core(s), WiFi%s%s, ",
            CONFIG_IDF_TARGET,
            chip_info.cores,
            (chip_info.features & CHIP_FEATURE_BT) ? "/BT" : "",
            (chip_info.features & CHIP_FEATURE_BLE) ? "/BLE" : "");

    printf("silicon revision %d, ", chip_info.revision);

    uint32_t size_flash_chip;
    esp_flash_get_size(NULL, &size_flash_chip);
    
    printf("%ldMB %s flash\n", size_flash_chip / (1024 * 1024),
            (chip_info.features & CHIP_FEATURE_EMB_FLASH) ? "embedded" : "external");

    printf("Minimum free heap size: %ld bytes\n", esp_get_minimum_free_heap_size());
#endif

    /* GPIO example */
    configure_led();
    
    printf("Sending name through morse");
    sendMorse(name);
    
    while(1)
    {
        update_led();
        delayMs(10);
    }
}

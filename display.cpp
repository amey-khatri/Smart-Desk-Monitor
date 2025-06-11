// Includes code for all timing functions and OLED display setup

#include <display.hpp>


// Screen Setup and Time Elapsed Functionality
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

extern TaskHandle_t timeElapsedTaskHandle;

void setupDisplay() {
    // Wire.begin(MY_SDA, MY_SCL);

    if (! display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
      Serial.println(F("SSD1306 allocation failed"));
      for (;;);  // hang here if the display didn’t initialize
    }

    display.clearDisplay();
    display.setTextSize(1);
    display.setTextColor(SSD1306_WHITE);
    display.setCursor(0,0);
    display.println(F("Amey's Desk"));
    display.display();
}

void timeElapsed(void * parameters) {
    unsigned long startTime = millis();
    display.clearDisplay();
    display.setTextSize(2);
    display.setCursor(30, 26);
    display.println(F("WELCOME"));
    display.setCursor(28, 44);
    display.println(F("BACK"));
    display.display();
    vTaskDelay(2000 / portTICK_PERIOD_MS);

    for(;;) {
        unsigned long timeSpent = millis() - startTime;
        display.clearDisplay();
         display.setTextSize(1);
        display.setCursor(10, 0);
        display.print(F("Time Elapsed: "));
        display.println(timeSpent / 1000 / 60);
        display.display();
        vTaskDelay(1000 * 60 / portTICK_PERIOD_MS);    
    }
}


// Drink Water and stand Timers
TimerHandle_t clearTimerHandle = nullptr;
TimerHandle_t drinkTimerHandle = nullptr;
TimerHandle_t standTimerHandle = nullptr;

constexpr TickType_t DRINK_PERIOD = pdMS_TO_TICKS(20UL * 60UL * 1000UL); //UL = Unsigned Long - 20 minutes 
constexpr TickType_t CLEAR_PERIOD = pdMS_TO_TICKS(5UL * 1000UL); // 5 seconds
constexpr TickType_t STAND_PERIOD = pdMS_TO_TICKS(40UL * 60UL * 1000UL); // 40 minutes


// Callback, clear display
void clearScreenCallback (TimerHandle_t xtimer) {
    display.invertDisplay(false);
    display.clearDisplay();
    display.display();
    vTaskResume(timeElapsedTaskHandle);
}

// Callback, show 'Drink Water' for 5 secs
void drinkTimerCallback (TimerHandle_t xtimer) {
    vTaskSuspend(timeElapsedTaskHandle); // Suspends timeElpased Task to give screen priority to drink water
    display.clearDisplay();
    display.setTextSize(2);
    display.setTextColor(SSD1306_WHITE);
    display.setCursor(30, 26);
    display.println(F("Drink"));
    display.setCursor(28, 44);
    display.println(F("Water"));
    display.invertDisplay(true);
    display.display();

    if (clearTimerHandle) {
        xTimerStart(clearTimerHandle, 0);
        playSound();
    }
}

//Callback, shows "Stand" for 5 secs every 40 minutes
void standTimerCallback (TimerHandle_t xtimer) {
    vTaskSuspend(timeElapsedTaskHandle);
    display.clearDisplay();
    display.setTextSize(2);
    display.setCursor(20, 20);
    display.println(F("STAND UP"));
    display.invertDisplay(true);
    display.display();


    if (clearTimerHandle) {
        xTimerStart(clearTimerHandle, 0);
        playSound();
    }
}

void setupTimers() {
    drinkTimerHandle = xTimerCreate("DrinkTimer", DRINK_PERIOD, pdTRUE, (void*)0, drinkTimerCallback);
    clearTimerHandle = xTimerCreate("ClearScreen", CLEAR_PERIOD, pdFALSE, (void*)0, clearScreenCallback);
    standTimerHandle = xTimerCreate("StandTimer", STAND_PERIOD, pdTRUE, (void*)0, standTimerCallback);
}
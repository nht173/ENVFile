#include <Arduino.h>
#include "ENVFile.h"

/* Default */
ENVFile env;

/* Custom file path */
// ENVFile env(".config");

/* Custom file path and filesystem (default: LittleFS) */
//#include <SPIFFS.h>
//ENVFile env(SPIFFS, ".config");

void setup() {
    Serial.begin(115200);
    delay(2000);

    env.begin();

    // Set a key
    env.set("strValue", "value1");
    env.set("intValue", 123);
    env.set("floatValue", 123.456f);
    env.set("doubleValue", 123.456789);
    env.set("boolValue", true);

    // Get a key
    String strValue = env.getString("strValue", "default");
    int intValue = env.getInt("intValue", 0);
    float floatValue = env.getFloat("floatValue", 0.0f);
    double doubleValue = env.getDouble("doubleValue", 0.0);
    bool boolValue = env.getBool("boolValue", false);

    Serial.printf("String value: %s\n", strValue.c_str());
    Serial.printf("Int value: %d\n", intValue);
    Serial.printf("Float value: %.2f\n", floatValue);
    Serial.printf("Double value: %.6f\n", doubleValue);
    Serial.printf("Bool value: %s\n", boolValue ? "true" : "false");

    // Set many keys and save once
    env.set("key1", "value1", false);
    env.set("key2", "value2", false);
    env.save();

    // Example usage to count startup times
    int startupCount = env.getInt("startupCount", 0);
    if (startupCount == 0) startupCount = 1;
    env.set("startupCount", startupCount + 1);
    Serial.printf("Startup count: %d\n", startupCount);
}

void loop() {

}
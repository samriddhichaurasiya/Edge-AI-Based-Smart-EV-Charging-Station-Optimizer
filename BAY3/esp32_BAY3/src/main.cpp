#include <Arduino.h>
#include "State.h"
#include "config.h"
#include "Peripherals.h"
#include "WiFi.h"
#include "Network.h"
#include "Telemetry.h"
#include "model.h"
#include "Edge_AI.h"
#include "optimization.h"
#include "rpc.h"
#include "attributes.h"



void setup()
{
    //initilize serial monitor
    Serial.begin(115200);

    dht.begin();  // initialise sesnor
    //configure esp32 with real time 
    configTime(0,0, "pool.ntp.org", "time.nist.gov");
    //config peripheral pins
    pinMode(BTN_PLUGIN, INPUT_PULLUP);
    pinMode(BTN_PLUGOUT, INPUT_PULLUP);
    pinMode(RELAY_PIN, OUTPUT);
    pinMode(LED_GREEN, OUTPUT);
    pinMode(LED_YELLOW, OUTPUT);
    pinMode(LED_RED, OUTPUT);

    //connect board to wifi
    connectWiFi();


    //config board to the mqtt server
    mqtt.setServer(MQTT_SERVER, MQTT_PORT);

    //set call back function upon receiving data from the cloud
    mqtt.setCallback(mqttCallback);
    mqtt.setBufferSize(512);

    //connect board to the cloud
    connectMQTT();
}

unsigned long now;
unsigned long last_print;

void loop()
{
    mqtt.loop();
    
    //push data every 5 sec
    now = millis();
    if((now - last_print) > 5000)
    {
        last_print = now;
        //read data from sensor
        sample_sensor();
        //run AI to get the predictions
        runEdgeAIInference();
        //decide load based on the predictions
        if(manualOverrideActive == 0)
        {
            runOptimization();
        }
        
        //publish the data
        publishTelemetry();
        
    }
    plug_status();
    updateLeds();

    
}


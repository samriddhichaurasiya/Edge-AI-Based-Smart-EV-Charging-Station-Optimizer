#include <Arduino.h>
#include <DHT.h>
#include "State.h"
#include "Peripherals.h"
#include "config.h"


DHT   dht(DHT_PIN , DHT_TYPE);

float mapFloat(long x, long inMin, long inMax, float outMin, float outMax)
{
   return(x - inMin) * (outMax - outMin) / (float)(inMax - inMin) + outMin;
}

void sample_sensor(void)
{
   int raw_current = analogRead(CURRENT_PIN); // 0 to 4095 --> 0 to 32A
   int raw_voltage = analogRead(VOLTAGE_PIN); // 0 to 4095 --> 0 to 250V

   // convert raw readings to actual values

   voltage = mapFloat(raw_voltage, 0, 4095, 0, 250); 

   if(bayStatus == "CHARGING")
   {
      current = mapFloat(raw_current, 0, 4095, 0, 32);
   }
   else
   {
      current  = 0;
   }

   //calculate power
   power = voltage * current;
   //to read temperature 
   float t = dht.readTemperature(DHT_PIN );
   if(!(isnan(t)))
   {
      temperature = t;
   }

}

float recentAvgCurrent(void)
{
   float sum = 0;
   //read recent 5 current values
   for(int i = 0; i < 5; i++)
   {
      sum += current;
   }
   return sum / 5;
}






void plug_status(void)
{
   bool pluginReading = digitalRead(BTN_PLUGIN);
   // detect the sw is pressed
   if (pluginReading == LOW) 
   {  
      sessionStartMs = millis();
     // plug in switch is pressed
     // change bay_status FREE to charging
     if(bayStatus == "FREE")
     {
        bayStatus = "CHARGING";
        Serial.println("Bay2 plugin detected, Bay is Charging");
        digitalWrite(RELAY_PIN, HIGH); // turn on relay to start charging
     }
     //update leds
   } 


   
   // plug out switch is pressed
   bool plugoutReading = digitalRead(BTN_PLUGOUT);
   // detect the sw is pressed
   if (plugoutReading == LOW) 
   {
     // plug in switch is pressed
    // change bay_status  charging to FREE
     if(bayStatus == "CHARGING")
     {
        bayStatus = "FREE";
        Serial.println("Bay2 plugout detected, Bay is Free");
        digitalWrite(RELAY_PIN, LOW);
     }
     //update leds
   }
   
}

/*void update_led_status(void)
{
   if (bayStatus == "FREE")
   {
      digitalWrite (LED_GREEN, HIGH);
      digitalWrite (LED_YELLOW, LOW);
   }
   else
   {
      digitalWrite (LED_GREEN, LOW);
      digitalWrite (LED_YELLOW, HIGH);
   }
}
*/
#include <WiFi.h>
#include "secrets.h"
#include "ThingSpeak.h" // always include thingspeak header file after other header files and custom macros

char ssid[] = "MUNOZ ZUNIGA";   // your network SSID (name) 
char pass[] = "25181226";   // your network password
int keyIndex = 0;            // your network key Index number (needed only for WEP)
WiFiClient  client;

unsigned long myChannelNumber = SECRET_CH_ID;
const char * myWriteAPIKey = SECRET_WRITE_APIKEY;

// Initialize our values
int number2 = random(0,100);
String myStatus = "";

void setup() {
  Serial.begin(115200);  //Initialize serial
  while (!Serial) {
    ; // wait for serial port to connect. Needed for Leonardo native USB port only
  }
  
  WiFi.mode(WIFI_STA);   
  ThingSpeak.begin(client);  // Initialize ThingSpeak
}

void loop() {

  // Connect or reconnect to WiFi
  if(WiFi.status() != WL_CONNECTED){
    Serial.print("Attempting to connect to SSID: ");
    Serial.println(SECRET_SSID);
    while(WiFi.status() != WL_CONNECTED){
      WiFi.begin(ssid, pass);  // Connect to WPA/WPA2 network. Change this line if using open or WEP network
      Serial.print(".");
      delay(5000);     
    } 
    Serial.println("\nConnected.");
  }
 
   int n = WiFi.scanNetworks();
    Serial.println("scan done");
    if (n == 0) {
        Serial.println("no networks found");
    } else {
        Serial.print(n);
        Serial.println(" networks found");
        for (int i = 0; i < n; ++i) {
            Serial.print(i + 1);
            Serial.print(": ");
            Serial.print(WiFi.SSID(i));
            Serial.print(" (");
            Serial.print(WiFi.RSSI(i));
            long rssi = WiFi.RSSI(i);
            Serial.print(rssi);
            Serial.print(")");
            Serial.println((WiFi.encryptionType(i) == WIFI_AUTH_OPEN)?" ":"*");

            number2 = random(0,100);
            ThingSpeak.setField(1, rssi);  
            ThingSpeak.setField(2, number2);
            ThingSpeak.setField(3, i);
          
            myStatus = String("SSID") + WiFi.SSID(i);
          
            ThingSpeak.setStatus(myStatus);
            // long rssi= WiFi.RSSI();
            //int httpCode = ThingSpeak.writeField(myChannelNumber, 1, rssi, myWriteAPIKey);
            int x = ThingSpeak.writeFields(myChannelNumber, myWriteAPIKey);
            if(x == 200){
              Serial.println("Channel update successful.");
            }
            else{
              Serial.println("Problem updating channel. HTTP error code " + String(x));
            }

  
  delay(20000); // Wait 20 seconds to update the channel again
        }
    }
}

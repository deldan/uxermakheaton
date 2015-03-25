 /*
Sketch para el UXER MakeAthon 
25/3/2015

 */


#include <SPI.h>
#include <WiFi.h>
#include <LiquidCrystal.h>

LiquidCrystal lcd( 8, 9, 3, 5, 6, 7 );
char ssid[] = "HydraSocialMedia"; //  your network SSID (name) En este caso es la de hydra
char pass[] = "WifiHydraSocialMedia";    // your network password (use for WPA, or use as key for WEP)
//char ssid[] = "WLAN_F015"; //  your network SSID (name) En este caso es la de hydra
//char pass[] = "6ca5459bc98224d386fe";    // your network password (use for WPA, or use as key for WEP)

int keyIndex = 0;            // your network key Index number (needed only for WEP)
int status = WL_IDLE_STATUS;
char server[] = "graph.facebook.com";    // name address for Google (using DNS)
//IPAddress server(31,13,90,113);

// Initialize the WiFi client library
WiFiClient client;

void setup() {
  //Initialize serial and wait for port to open:
  Serial.begin(9600); 
  // check for the presence of the shield:
  if (WiFi.status() == WL_NO_SHIELD) {
    Serial.println("WiFi shield not present"); 
    // don't continue:
    while(true);
  } 
  lcd.begin(16, 2);
  lcd.print("Conectando wifi");
  // attempt to connect to Wifi network:
  conectarWifi();
  printWifiStatus();
  //lcd.begin(16, 2);
  //lcd.print("Conectando con");
  //lcd.setCursor(0,1);
  //lcd.print("Facebook");
  conectarConFacebook();

}
////////////////////////////////////////////////////////////////////////////////////////////////////
void loop() {
  
  // if there are incoming bytes available 
  // from the server, read them and print them:  
  while (client.available()) {
    char c = client.read();
    Serial.print(c);

    }
  }
  client.flush();
  

// if the server's disconnected, stop the client:
//  if (!client.connected()) {
//    Serial.println();
//    Serial.println("disconnecting from server.");
//    client.stop();
//    
//do nothing forevermore:
//    while(true);
//  }

}


void printWifiStatus() {
  // print the SSID of the network you're attached to:
  //Serial.print("SSID: ");
  //Serial.println(WiFi.SSID());

  // print your WiFi shield's IP address:
  IPAddress ip = WiFi.localIP();
  //Serial.print("IP Address: ");
  //Serial.println(ip);

  // print the received signal strength:
  long rssi = WiFi.RSSI();
  //Serial.print("signal strength (RSSI):");
  //Serial.print(rssi);
  //Serial.println(" dBm");
}

void conectarConFacebook(){
  //Serial.println("\nStarting connection to server...");
  // if you get a connection, report back via serial:
  if (client.connect(server, 80)) {
    //Serial.println("connected to server");
    // Make a HTTP request:
    client.println("GET /hydrasocialmedia?fields=id,name,likes HTTP/1.1");
    client.println("Host: graph.facebook.com");
    client.println("Connection: close");
    client.println();
  }
}

void conectarWifi(){
  while ( status != WL_CONNECTED) { 
    //Serial.print("Attempting to connect to SSID: ");
    //Serial.println(ssid);
    // Connect to WPA/WPA2 network. Change this line if using open or WEP network:    
    status = WiFi.begin(ssid, pass);
  
    // wait 10 seconds for connection:
    delay(5000);
  } 
  //Serial.println("Connected to wifi");
}

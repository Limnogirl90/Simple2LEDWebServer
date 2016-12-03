#include <ESP8266WiFi.h>
#include <WiFiClient.h>
//#include <ESP8266WebServer.h>

const char* ssid = "ND-guest"; // change to your wifi name
const char* password = ""; // change to your wifi password

int ledPin = 2; // GPIO2
int ledPin4 = 4; // GPIO4
WiFiServer server( 80);

void setup() {
 Serial.begin( 115200);
 delay( 10);

 pinMode( ledPin, OUTPUT);
 pinMode( ledPin4, OUTPUT);
 digitalWrite( ledPin, LOW); // Connect to WiFi network
 digitalWrite( ledPin4, LOW);
 Serial.println();
 Serial.println();
 Serial.print(" Connecting to ");
 Serial.println( ssid);

 WiFi.begin( ssid, password);
 while (WiFi.status() != WL_CONNECTED)
 {
 delay( 500); Serial.print(".");
 }
 Serial.println("");
 Serial.println(" WiFi connected");
 // Start the server
 server.begin();
 Serial.println(" Server started");
 // Print the IP address
 Serial.print(" Use this URL to connect: ");
 Serial.print(" http://");
 Serial.print( WiFi.localIP());
 Serial.println("/"); }

 void loop() {
 // Check if a client has connected

 WiFiClient client = server.available();
 if (! client)
 { return; }
 // Wait until the client sends some data
 Serial.println(" new client");
 while(! client.available()){
  delay(1);
  } 
// Read the first line of the request
 String request = client.readStringUntil('\r');
 Serial.println(request);

 client.flush();

// Match the request
 int value = LOW;
 int value4 = LOW;
 if (request.indexOf("/LED2=ON") != -1) {
 digitalWrite( ledPin, HIGH);
 value = HIGH;
 }
 if (request.indexOf("/LED2=OFF") != -1) {
 digitalWrite( ledPin, LOW);
 value = LOW;
 }

 if (request.indexOf("/LED4=ON") != -1) {
 digitalWrite( ledPin4, HIGH);
 value4 = HIGH;
 }
 if (request.indexOf("/LED4=OFF") != -1) {
 digitalWrite( ledPin4, LOW);
 value4 = LOW;
 }
 // Set ledPin according to the request
 // digitalWrite( ledPin, value); 
 // Return the response

client.println("HTTP/1.1 200 OK");
 client.println("Content-Type:text/html");
 client.println("");
 // do not forget this one
 client.println("<!DOCTYPE HTML>");
 client.println("<html><body>");
 client.print("Led pin 2 is now: ");
 if( value == HIGH) {
  client.print("On"); 
 } else {
  client.print("Off");
 }
 client.println("<br/><br/>");
 client.println("<a href=\"/LED2=ON\"\"><button>Turn On</button></a>"); 
 client.println("<a href=\"/LED2=OFF\"\"><button>Turn Off</button></a><br/>");
 client.println("<br/><br/>");
 client.print("Led pin 4 is now: ");
 if( value4 == HIGH) {
  client.print("On"); 
 } else {
  client.print("Off");
 }
 client.println("<br/><br/>");
 client.println("<a href=\"/LED4=ON\"\"><button>Turn On</button></a>"); 
 client.println("<a href=\"/LED4=OFF\"\"><button>Turn Off</button></a><br/>");
 client.println("<br/><br/>");
 client.println("</body></html>");
 delay(1);
 Serial.println("Client disonnected"); 
 Serial.println("");
}

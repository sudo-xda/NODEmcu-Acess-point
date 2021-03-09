//Made by SUDO_XDA
#include <ESP8266WiFi.h>

const char* ssid     = "SUS";
const char* password = "aaaaqqqq";

WiFiServer server(80);

// Variable to store the HTTP request
String header;

// Auxiliar variables to store the current output state
String output5State = "off";
String output4State = "off";
String output0State = "off";
String output2State = "off";

// Assign output variables to GPIO pins
const int output5 = 5;
const int output4 = 4;
const int output0 = 0;
const int output2 = 2;

unsigned long currentTime = millis();

unsigned long previousTime = 0; 

const long timeoutTime = 2000;

void setup() {
  Serial.begin(115200);
  
  pinMode(output5, OUTPUT);
  pinMode(output4, OUTPUT);
  pinMode(output0, OUTPUT);
  pinMode(output2, OUTPUT);
  
  digitalWrite(output5, LOW);
  digitalWrite(output4, LOW);
  digitalWrite(output0, LOW);
  digitalWrite(output2, LOW);

  
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.softAP(ssid, password);
  server.begin();
  
  Serial.println("");
  Serial.println("server Started");
  Serial.println("Server IP: ");
  
}

void loop(){
  WiFiClient client = server.available();   // Listen incoming cli

  if (client) {                             
    Serial.println("New Client.");          
    String currentLine = "";                // String to hold incoming data from the client
    currentTime = millis();
    previousTime = currentTime;
    while (client.connected() && currentTime - previousTime <= timeoutTime) {
      currentTime = millis();         
      if (client.available()) {             
        char c = client.read();             
        Serial.write(c);                    
        header += c;
        if (c == '\n') {                    
          
          
          if (currentLine.length() == 0) {
            
            
            client.println("HTTP/1.1 200 OK");
            client.println("Content-type:text/html");
            client.println("Connection: close");
            client.println();
            
            
            if (header.indexOf("GET /5/on") >= 0) {
              Serial.println("GPIO 5 on");
              output5State = "on";
              digitalWrite(output5, HIGH);
            } else if (header.indexOf("GET /5/off") >= 0) {
              Serial.println("GPIO 5 off");
              output5State = "off";
              digitalWrite(output5, LOW);
            } else if (header.indexOf("GET /4/on") >= 0) {
              Serial.println("GPIO 4 on");
              output4State = "on";
              digitalWrite(output4, HIGH);
            } else if (header.indexOf("GET /4/off") >= 0) {
              Serial.println("GPIO 4 off");
              output4State = "off";
              digitalWrite(output4, LOW);
            } else if (header.indexOf("GET /0/on") >= 0) {
              Serial.println("GPIO 0 on");
              output0State = "on";
              digitalWrite(output0, HIGH);
            } else if (header.indexOf("GET /0/off") >= 0) {
              Serial.println("GPIO 0 off");
              output0State = "off";
              digitalWrite(output0, LOW);
            } else if (header.indexOf("GET /2/on") >= 0) {
              Serial.println("GPIO 2 on");
              output2State = "on";
              digitalWrite(output2, HIGH);
            } else if (header.indexOf("GET /2/off") >= 0) {
              Serial.println("GPIO 2 off");
              output2State = "off";
              digitalWrite(output2, LOW);
            } 
            
            
            client.println("<!DOCTYPE html><html>");
            client.println("<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">");
            client.println("<link rel=\"icon\" href=\"data:,\">");
            
            
            client.println("<style>html { font-family: Helvetica; display: inline-block; margin: 0px auto; text-align: center;}");
            client.println(".button { background-color: #08ff1c; border: none; color: white; padding: 26px 26px;border-radius: 50%;");
            client.println("text-decoration: none; font-size: 30px; margin: 2px; cursor: pointer;}");
            client.println(".button2 {background-color:  #fa1403;}</style></head>");
            
            
            client.println("<body><h1>HOME Automation Using NODEMCU</h1>");
            client.println("<body><h2>BY Department of E&TC</h2>");
            
             
            client.println("<p>D1 pin - State " + output5State + "</p>");
                  
            if (output5State=="off") {
              client.println("<p><a href=\"/5/on\"><button class=\"button\">ON</button></a></p>");
            } else {
              client.println("<p><a href=\"/5/off\"><button class=\"button button2\">OFF</button></a></p>");
            } 
               
             
            client.println("<p>D2 pin - State " + output4State + "</p>");
                   
            if (output4State=="off") {
              client.println("<p><a href=\"/4/on\"><button class=\"button\">ON</button></a></p>");
            } else {
              client.println("<p><a href=\"/4/off\"><button class=\"button button2\">OFF</button></a></p>");
            }

            client.println("<p>D3 pin - State " + output0State + "</p>");
                   
            if (output0State=="off") {
              client.println("<p><a href=\"/0/on\"><button class=\"button\">ON</button></a></p>");
            } else {
              client.println("<p><a href=\"/0/off\"><button class=\"button button2\">OFF</button></a></p>");
            }

            client.println("<p>D4 pin - State " + output2State + "</p>");
                   
            if (output2State=="off") {
              client.println("<p><a href=\"/2/on\"><button class=\"button\">ON</button></a></p>");
            } else {
              client.println("<p><a href=\"/2/off\"><button class=\"button button2\">OFF</button></a></p>");
            }


            client.println("<p>Guided By -:</p>");
            client.println("<p>Mrs. MLM Laxmi</p>");
            client.println("<p>Submitted by -:</p>");
            client.println("<p>Arpit Adarsha Mishra(1701109159 )</p>");
            client.println("<p>Yashobanta Prasad Gochhi(1701109259 )</p>");
            client.println("<p>R. Himanshu Reddy(1701109367)</p>");
            client.println("<p>Jigyansha Jeevan Rout( 1821109066 )</p>");
            
            client.println("</body></html>");
            
            
            client.println();
            
            break;
          } else { 
            currentLine = "";
          }
        } else if (c != '\r') {  
          currentLine += c;      
        }
      }
    }
    
    header = "";
    
    client.stop();
    Serial.println("Client disconnected.");
    Serial.println("");
  }
}
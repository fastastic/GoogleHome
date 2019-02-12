#include <ArduinoJson.h>
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

ESP8266WebServer server(8081);

const char* ssid = "Martin Router King";
const char* pass = "a97L61J90r63_55";

void setup() {
  Serial.begin(115200);

  //Setup WiFi connection
  WiFi.begin(ssid, pass);
  Serial.print("Waiting to connect...");
  while(WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  //Setup server
  server.on("/body", handleBody);
  server.begin();
  Serial.println("Server listening on port 8081");

  //Setup pins
  pinMode(D1, OUTPUT);
}

void loop() {
  server.handleClient();
}

void handleBody() {
  if(server.hasArg("plain") == false) {
    server.send(400, "text/plain", "Error 400 Bad Request");
    return;
  }
  
  DynamicJsonBuffer jsonBuffer;
  JsonObject& root = jsonBuffer.parseObject(server.arg("plain"));
  //root.printTo(Serial);

  if(root["pass"] != pass) {
    server.send(401, "text/plain", "Error 401 Unauthorized");
  }
  
  else { //Authenticated user
    if(root["status"] == "On") {
      Serial.print("On");
      digitalWrite(D1, LOW);
    }

    else if (root["status"] == "Off") {
      Serial.print("Off");
      digitalWrite(D1, HIGH);
    }
  }
}

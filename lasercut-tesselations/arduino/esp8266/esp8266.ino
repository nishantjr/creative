#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

// ------------------ Serial Debugging -------
// -------------------------------------------

void serial_setup() {
  Serial.begin(9600);
  Serial1.begin(9600);
  Serial.println();
}

void serial_log_if_error(bool status, char const* const message)
{
    if (!status) {
        Serial.println(message);
        Serial1.println(message);
    }
}

// ------------------ WiFi -------------------
// -------------------------------------------

IPAddress const local_IP(192,168,1,1);
IPAddress const gateway(192,168,1,0);
IPAddress const subnet(255,255,255,0);
 
void wifi_setup()
{
    serial_log_if_error(WiFi.softAPConfig(local_IP, gateway, subnet), "WiFi AP configuration failed.");
    serial_log_if_error(WiFi.softAP("NJR-01"), "WiFi AP: setup failed.");
}

// ------------------ Server -----------------
// -------------------------------------------

ESP8266WebServer server(80);

void server_setup()
{
    server.on("/", server_handle_root);
    server.onNotFound(server_handle_not_found);
    server.begin();
}

void server_loop()
{
    server.handleClient();
}

void server_handle_root() {
    server.send(200, "text/plain", "Hellow World");
}

void server_handle_not_found() {
    server.send(200, "text/plain", "404");
}

// ------------------ LEDs -------------------
// -------------------------------------------

int const pin_num[3] = {2, 3, 4};

void leds_setup() {
  for (int i = 0; i < 3; i++) {
    pinMode(pin_num[i], OUTPUT);
  }
}

int n = 0;
void leds_loop(){
  n++;
  for (int i = 0; i < 3; i++) {
    int value = n % 512 ; // (n + i*(512/3)) % 512;
    if (n < 256) {
        analogWrite(pin_num[i], value);
    }
    else {
        analogWrite(pin_num[i], 512 - value);
    }
  }
}


// ------------------ LEDs -------------------
// -------------------------------------------
 
void setup() {
//    wifi_setup();
    leds_setup();
}

void loop() {
    Serial.println("Loop.");
    Serial1.println("Loop.");
//    server_loop();
    leds_loop();
    delay(100);
}

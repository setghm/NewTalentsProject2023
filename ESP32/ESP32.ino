#include <WiFi.h>
#include "ClienteThingSpeak.h"

#define WIFI_SSID "UPQ Alumnos"
#define WIFI_PWD  ""

#define THINGSPEAK_CHANNEL  2293246
#define THINGSPEAK_APIKEY   "GJ1O4PWAOGMR7SD2"

#define FIELD_VOLTAJE_CPU 1
#define FIELD_CORRIENTE_CPU 2
#define FIELD_VOLTAJE_GPU 3
#define FIELD_CORRIENTE_GPU 4
#define FIELD_VOLTAJE_TPU 5
#define FIELD_CORRIENTE_TPU 6

void setup() {
  // Conectarse a internet
  WiFi.begin(WIFI_SSID, WIFI_PWD);
  while (WiFi.status() != WL_CONNECTED);
  // No iniciar el cliente de thingspeak hasta que haya una conexión a internet existente
  ClienteThingSpeak.begin(THINGSPEAK_CHANNEL, THINGSPEAK_APIKEY);
}

void loop() {
  // Ejemplo
  ClienteThigSpeak.guardarDatos(FIELD_VOLTAJE_CPU, 115);
}

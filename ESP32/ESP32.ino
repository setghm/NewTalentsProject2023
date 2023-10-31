#include <WiFi.h>
#include "ClienteThingSpeak.h"

#define WIFI_SSID "HMWIFI"
#define WIFI_PWD  "vivianita"

#define THINGSPEAK_CHANNEL  2293246
#define THINGSPEAK_APIKEY   "GJ1O4PWAOGMR7SD2"

#define FIELD_ENCENDIDO 1
#define FIELD_POTENCIA 2
#define FIELD_CORRIENTE 3

#define DEFAULT_DELAY 3000

void setup() {
  // Configurar el LED builtin para indicar si se ha conectado o no a internet
  pinMode(2, OUTPUT);
  digitalWrite(2, LOW);
  
  // Conectarse a internet
  WiFi.begin(WIFI_SSID, WIFI_PWD);
  while (WiFi.status() != WL_CONNECTED);

  // Indicar que se ha conectado a internet
  digitalWrite(2, HIGH);
  
  // No iniciar el cliente de thingspeak hasta que haya una conexión a internet existente
  ClienteThingSpeak.begin(THINGSPEAK_CHANNEL, THINGSPEAK_APIKEY);
}

void loop() {
  // Ejemplo
  ClienteThingSpeak.guardarDatos(FIELD_POTENCIA, 1);
  ClienteThingSpeak.guardarDatos(FIELD_CORRIENTE, 1);

  delay(DEFAULT_DELAY);
}

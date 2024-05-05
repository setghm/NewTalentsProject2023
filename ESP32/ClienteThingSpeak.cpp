#include "ClienteThingSpeak.h"
#include <ThingSpeak.h>

void ClienteThingSpeak_Class::begin(unsigned long canal, String api_key) {
  ThingSpeak.begin(this->cliente);
  this->canal = canal;
  this->api_key = api_key;
}

void ClienteThingSpeak_Class::guardarDatos(int numero, int valor) {
  ThingSpeak.setField(numero, valor);
  ThingSpeak.writeFields(canal, api_key.c_str());
}

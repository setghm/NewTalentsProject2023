#pragma once

#include <WiFi.h>

class ClienteThingSpeak_Class {
  private:
    unsigned long canal;
    String api_key;
    WiFiClient cliente;
  public:
    void guardarDatos(int numero, int valor);
    void begin(unsigned long canal, String api_key);
};

static ClienteThingSpeak_Class ClienteThingSpeak;

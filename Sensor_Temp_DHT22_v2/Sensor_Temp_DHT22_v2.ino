#include "DHT.h"

#define DHTPIN 2
#define DHTTYPE DHT22

DHT sensor (DHTPIN, DHTTYPE);


void setup()
{
  Serial.begin(9600);
  Serial.println("Iniciando...");
  sensor.begin();
  pinMode(13,OUTPUT);
}

    long tiempoUltimaLectura =0;

void loop()
{

  if(millis()-tiempoUltimaLectura>2000)
  {
  float humedad = sensor.readHumidity();
  float temperatura = sensor.readTemperature();

    if(isnan(humedad)|| isnan(temperatura))
      {
        Serial.print("Error de Lectura");
        return;
      }

  Serial.print("Temperatura");
  Serial.print( temperatura );
  Serial.println( "°C" );
  Serial.print("Humedad");
  Serial.print(humedad);
  Serial.print( " %" );
  }

  digitalWrite(13, HIGH);
  delay(100);
  digitalWrite(13,LOW);
  delay(100);
}

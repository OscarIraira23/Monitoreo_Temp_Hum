#include <dht.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27,16,4);
dht DHT;

#define DHTPIN 6

void setup()
{

    pantalla(); // Activamos pantalla LCD I2C 
    Serial.begin(9600); // Activamos monitor serial de Arduino
  
    DHT.read22(DHTPIN);// Se especifica que modelo de DHT se está usando, en este caso DHT 22
}

void loop()
{

    float humedad = DHT.humidity;
    float tc = DHT.temperature;

    Serial.print(",");
    Serial.print("Humedad : ");
    Serial.println(humedad, 2);
    Serial.print(" %");
    Serial.print(",");
    Serial.print("Temperatura ºC :");
    Serial.println(tc, 2);

    mostrar_datos(humedad,tc);

}

void pantalla()
  {
    lcd.init();
    lcd.init();
    lcd.backlight();
  }
void mostrar_datos(int h , int t)
  {
    lcd.setCursor(0,0);
    lcd.print("Humedad : ");
    lcd.print(h);
    lcd.print("%");
    lcd.setCursor(0,1);
    lcd.print("Temp: ");
    lcd.print(t);
    lcd.print(" C");
    delay(2000);
  }
  

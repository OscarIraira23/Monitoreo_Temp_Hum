//Incorporamos librerias

#include <DHT.h>
#include <LiquidCrystal_I2C.h>

//Se activa pantalla LCD I2C

LiquidCrystal_I2C lcd(0x27,16,4);

/*
Defino el pin a usar con mi sensor DHT con la funcion 
DHTPIN Nº e indico el modelo a usar con DHTTYPE, en este caso 
DHT 22
*/

#define DHTPIN 6 
#define DHTTYPE DHT22

//Indico el pin a usar y el tipo y genero un objeto o variable llamada dht

DHT dht(DHTPIN,DHTTYPE);

//genero 2 variables para almacenar temperatura y humedad

float humedad;
float tc;

void setup()
{   
 Serial.begin(9600); // Activamos monitor serial de Arduino
    
 lcd.init(); // Activo Pantalla LCD
 lcd.backlight(); 

 dht.begin(); // Activo mi sensor DHT con la instrucción dht.begin
 
}

void loop()
{
    // indico en que variables almacenar la información
    
    humedad = dht.readHumidity();
    tc = dht.readTemperature();
    
    // Muestro la información a través de mi monitor serial
    
    Serial.print("Humedad : ");
    Serial.print(humedad, 2);
    Serial.print(" %");
    Serial.print(",");
    Serial.print("Temperatura ºC :");
    Serial.print(tc, 2);
    Serial.println("");
    
    // Muestro información en mi pantalla LCD 
    
    lcd.setCursor(0,0);
    lcd.print("Humedad : ");
    lcd.print(humedad,1);
    lcd.print("%");
    
    lcd.setCursor(0,1);
    lcd.print("Temp: ");
    lcd.print(tc,1);
    lcd.print("C");
    delay(1000);
}

 

  

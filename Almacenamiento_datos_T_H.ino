/*
 *  Declaramos las librerias que habiliten nuestros componentes:
 *  - DataLogger
 *  - DHT 22
 */

// cambiaremos esta libreria #include "DHT.h"
/* Se recomiendo usar la libreria dht.h en vez de la antes
usada en la línea n° 7
*/

#include <dht.h>
#include <SD.h>
#include <Wire.h>
#include "RTClib.h"
/*
Si desea usar una pantalla LCD I2C, debe solo "descomentar" la línea que indica el uso de la libreria para LiquidCrystal_I2C
y también la línea N° 23, la que corresponde a su configuración respecto a la pantalla.
*/

//#include <LiquidCrystal_I2C.h>

//LiquidCrystal_I2C lcd(0x27,16,4);

RTC_DS3231 RTC;
dht DHT;

#define LOG_INTERVAL 60000
#define ECHO_TO_SERIAL 1
#define DHTPIN 6

const int chipSelect = 10;

File logfile;

void setup()
{
  /*
  Si queremos visualizar la información en nuestra pantalla LCD, el usuario debe descomentar el línea respectiva
   a la que indica pantalla(), pues esta corresponde a una función que inicializa la pantalla como tal.
   */
    //pantalla();
    Serial.begin(9600);
    Serial.print("Inicializando tarjeta SD ... ");
    pinMode(10, OUTPUT);

    if(!SD.begin(chipSelect))
    {
        Serial.println("Fallo en la tarjeta, o no esta conectada ");
        return;
    }
    Serial.println("Tarjeta Iniciada con exito ! ");

    char filename[] = "LOGGER00.CSV";
    for(uint8_t i = 0 ; i < 100; i++)
    {
        filename[6] = i/10 + '0' ;
        filename[7] = i%10 + '0' ;

        if(! SD.exists(filename))
        {
            logfile = SD.open(filename, FILE_WRITE);
            break;
        }
    }

    if(! logfile)
    {
        Serial.println("No se puede crear archivo");
    }
    Serial.print("Iniciando en : ");
    Serial.println(filename);

    Wire.begin();
    if(!RTC.begin())
    {
        logfile.println("RTC Fallo");
       // RTC.adjust(DateTime(__DATE__, __TIME__));
    #if ECHO_TO_SERIAL
        Serial.println("RTC Fallo");
    #endif
    }
        logfile.println("fecha_hora,% humedad,temperatura °C");
    #if ECHO_TO_SERIAL
        Serial.println("fecha_hora, % humedad, temperatura °C");
    #endif
        DHT.read22(DHTPIN);
}

void loop()
{

    DateTime now;

    delay((LOG_INTERVAL -1) - (millis() % LOG_INTERVAL));

    String dataString = "";

    now = RTC.now();

    if(now.day() <10)
    {
        logfile.print(0,DEC);
    }

    logfile.print(now.day(), DEC);
    logfile.print("/");

    if(now.month() < 10)
    {
        logfile.print(0,DEC);
    }

    logfile.print(now.month(), DEC);
    logfile.print("/");
    logfile.print(now.year(),DEC);
    logfile.print(" ");

    if(now.hour() < 10)
    {
        logfile.print(0,DEC);
    }

    logfile.print(now.hour(), DEC);
    logfile.print(":");

    if(now.minute() < 10)
    {
        logfile.print(0,DEC);
    }

    logfile.print(now.minute(), DEC);
    logfile.print(":");

    if(now.second() < 10)
    {
        logfile.print(0,DEC);
    }

    logfile.print(now.second(), DEC);

    #if ECHO_TO_SERIAL
    // Serial.print(now.unixtime()); // seconds since 1/1/1970
    //Serial.print(",");
    if (now.day() < 10)
    {
      Serial.print(0, DEC);
    }
    Serial.print(now.day(), DEC);
    Serial.print("/");
    if (now.month() < 10)
    {
      Serial.print(0, DEC);
    }
    Serial.print(now.month(), DEC);
    Serial.print("/");
    Serial.print(now.year(), DEC);
    Serial.print(" ");

    if (now.hour() < 10)
    {
      Serial.print(0, DEC);
    }
    Serial.print(now.hour(), DEC);
    Serial.print(":");

    if (now.minute() < 10)
    {
      Serial.print(0, DEC);
    }
    Serial.print(now.minute(), DEC);
    Serial.print(":");

    if (now.second() < 10)
    {
      Serial.print(0, DEC);
    }
    Serial.print(now.second(), DEC);

  #endif

  float humedad = DHT.humidity;
  float tc = DHT.temperature;

  if(isnan(tc) || isnan(humedad))
  {
      Serial.println("Fallo en la lectura de sensor DHT");
  }
  else{
    //svd = 5.018 + 0.32321*tc + 8.1847e-3*pow(tc,2) + 3.1243e-4*pow(tc,3);
    //vd = humedad/100*svd;
    logfile.print(",");
    logfile.print(humedad, 2);
    logfile.print(" %");
    logfile.print(",");
    logfile.print(tc, 2);

  #if ECHO_TO_SERIAL
      Serial.print(",");
      Serial.print(humedad, 2);
      Serial.print(" %");
      Serial.print(",");
      Serial.print(tc, 2);
  #endif //ECHO_TO_SERIAL
    }
    /*
    Así como en para iniciar el uso de la pantalla debebmos desbloquear su libreria y la función
    pantalla() , para poder observar los datos en la pantalla LCD, debemos descomentar la línea que cuenta
    con la función mostrar_datos()
    */
  //mostrar_datos(humedad,tc);

  logfile.println();
  #if ECHO_TO_SERIAL
    Serial.println();

  #endif

  logfile.flush();

}

  /* A continuación el usuario podrá encontrarse las dos funciones creadas para el uso de la pantalla LCD I2C, nuevamente
  se reitera que si deseamos hacer uso de la pantalla, debemos descomentar todo lo antes mencionado y también las siguientes
  funciones
  */

  /*
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
  */

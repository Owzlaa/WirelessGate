#include <Wire.h> // Insertion de la librairie "Wire.h"
#include <SeeedOLED.h> // Insertion de la librairie "SeedOLED.h"
#include <ChainableLED.h>
#include <Servo.h>
#include <SoftwareSerial.h>
#include <Bridge.h>
#include <HttpClient.h>
unsigned char buffer[64];
int count = 0;
String essai = "";
String lejeunem = "19002B2B6178";
String fauchert = "19002B2B6178";

HttpClient client;
SoftwareSerial SoftSerial(8, 9);
ChainableLED leds(7, 8, 5);
char MessageArrive[128] = "Bonjour,";
#define BoutonOuverture A0
byte angleOuverture = 72;
byte angleFermeture = 0;
byte variabledutemps = 0;
Servo Servoportail;


void setup() {

  Serial.begin(9600);
  SoftSerial.begin(9600);     // the SoftSerial baud rate
  Serial.begin(9600);         // the Serial port of Arduino baud rate.
  Bridge.begin();
  SerialUSB.begin(9600);
  Servoportail.attach(8);
  Wire.begin();  // Initialisation de la librairie Wire
  Bridge.begin();
  SeeedOled.init();  //Initialisation de l'écran OLED
  Servoportail.attach(8);
  DDRB |= 0x21;
  PORTB |= 0x21;
  SeeedOled.clearDisplay();           // Nettoie l'écran
  SeeedOled.setNormalDisplay();       // L'écran est dans le mode par default
  SeeedOled.setPageMode();            // Définir le mode d'adressage en mode Page
  SeeedOled.setTextXY(0, 0); // Met le curseur sur la ligne 4 et la colonne 3
  SeeedOled.putString("Veuillez, passer"); // Affiche des espaces sur l'écran
  SeeedOled.setTextXY(1, 0); // Met le curseur sur la ligne 4 et la colonne 3
  SeeedOled.putString("votre badge."); // Affiche des espaces sur l'écran
  leds.setColorRGB(0, 255, 0, 0);
  Servoportail.write(angleFermeture);


}

void loop()
{

  bouclelectureinfinisurlelecteurRFID();

  if ( essai.equals(lejeunem) || essai.equals(fauchert) || BoutonOuverture == 1)
  {
    
    SeeedOled.setTextXY(0, 0); // Met le curseur sur la ligne 4 et la colonne 3
    SeeedOled.putString(MessageArrive); // Affiche des espaces sur l'écran
    SeeedOled.setTextXY(2, 0);
    
    if ( essai.equals(lejeunem))
    {

       SeeedOled.putString("Mr Le Jeune"); // Affiche des espaces sur l'écran
       client.get("gatewireless.ecolosia.me/post/lejeunem");
       while (client.available())
       {
          char c = client.read();
          SerialUSB.print(c);
        }
          SerialUSB.flush();
       
    }

    if ( essai.equals(fauchert))
    {

       SeeedOled.putString("Mr Faucher"); // Affiche des espaces sur l'écran
       client.get("gatewireless.ecolosia.me/post/fauchert");

       while (client.available())
       {
          char c = client.read();
          SerialUSB.print(c);
        }
          SerialUSB.flush();
       
    }
    leds.setColorRGB(0, 0, 255, 0);
    delay(1000);
    Servoportail.write(angleOuverture);
    delay(8000);

    while ( essai.equals(lejeunem) || essai.equals(fauchert) || BoutonOuverture == 1)
    {

    }
    Servoportail.write(angleFermeture);
    leds.setColorRGB(0, 255, 0, 0);
    client.get("gatewireless.ecolosia.me/post/ferme");
    
    while (client.available())
       {
          char c = client.read();
          SerialUSB.print(c);
        }
          SerialUSB.flush();
          
    setup();

  }

  else 
  {

    variabledutemps ++;
    delay(1000);

    if (variabledutemps == 30)
    {
        client.get("gatewireless.ecolosia.me/post/active?");

        if (client.read() == "Désactivé")
        {

            SeeedOled.setTextXY(0, 0); // Met le curseur sur la ligne 4 et la colonne 3
            SeeedOled.putString("Accès impossible"); // Affiche des espaces sur l'écran
          
        }

        else
        {

           SeeedOled.clearDisplay();           // Nettoie l'écran
          
        }

      variabledutemps = 0;
    
    }

  }

}

void bouclelectureinfinisurlelecteurRFID()
{
  
  if (SoftSerial.available())
  {

    while (SoftSerial.available())
    {

      buffer[count++] = SoftSerial.read();
      if (count == 64)break;

    }

      Serial.write(buffer, count);
      count = 0;
    
   }

    SoftSerial.write(Serial.read());
    essai =  SoftSerial.readString();
    
}

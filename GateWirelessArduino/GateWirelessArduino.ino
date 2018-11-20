#include <Wire.h>             //Les "include" permet d'inclure une librairie dans un programme.
#include <SeeedOLED.h>
#include <ChainableLED.h>
#include <Servo.h>
#include <SoftwareSerial.h>
#include <Bridge.h>
#include <HttpClient.h>


HttpClient Arduino;             //Au lieu d'avoir HttpClient.get(); nous pouvons avoir Arduino.get();.
SoftwareSerial CommunicationSerieRFID(8, 9);              //Cette librairie permet de créer plusieurs liaison série, nous en avons créer une, sur les port 8,9.
ChainableLED VoyantAcces(1, 7, 6);              //ChainableLED, permet de connecter plusieurs LED RGB en un seul port GROVE, dans notre cas nous avons 1 seul led, et nous l'avons connectés sur les port 7 et 6.
Servo ServoPortail;             //Servo, permet de une liaison entre une Arduino et un servomoteur.

byte angleOuverture = 72;             //Création d'une variable byte (0 à 255) et l'Arduino stock la valeur 70.
byte angleFermeture = 0;

#define BoutonOuverture 4             //Nous définissons un port à une variable.

void setup ()             //Ceci est une variable qui s'éxecute une fois, un démarrage de la carte Arduino.
{

  CommunicationSerieRFID.begin(9600);             //Nous définissons la vitesse de la communication série à 9600 bauds.
  Bridge.begin();            //Initialisation de la librairie Bridge.
  Wire.begin();              //Initialisation de la librairie Wire.
  SeeedOled.init();  //Initialisation de la librairie SeeedOled.
  Re_DemarrerLeProgramme();           //Normalement, à la fin de la boucle setup, la boucle loop est automatiquement mise en route, mais nous décidons d'éxécuter une boucle qui s'appelle "Re_DemarrerLeProgramme".
  
}

void Re_DemarrerLeProgramme()               //Création d'une boucle nommé "Re_DemarrerLeProgramme".
{

  SeeedOled.clearDisplay();                // Nettoie l'écran.
  SeeedOled.setNormalDisplay();                // L'écran est dans le mode par default.
  SeeedOled.setPageMode();                // Définir le mode d'adressage en mode Page.
  SeeedOled.setTextXY(0, 0);                // Met le curseur sur la ligne 0 et la colonne 0.
  SeeedOled.putString("Veuillez, passer");                // Affiche des espaces sur l'écran.
  SeeedOled.setTextXY(1, 0);              // Met le curseur sur la ligne 1 et la colonne 0.
  SeeedOled.putString("votre badge.");              // Affiche ce qui se situe entre les guillemet sur l'écran.
  VoyantAcces.setColorRGB(0, 255, 0, 0);              //La couleur de la LED 0, est désormais rouge.
  ServoPortail.write(angleFermeture);                //Le portail se met à la position 72.
  AutorisationOuverture();                //Lancement de la boucle "AutorisationOuverture"
  
}

void loop() {} //Nous souhaitons rien n'avoir dans cette boucle, mais nous sommes obliger de l'avoir, c'est une nécessité pour l'IDE Arduino

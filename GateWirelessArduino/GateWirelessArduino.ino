#include <Wire.h>             //Les "include" permet d'inclure une librairie dans un programme.
#include <SeeedOLED.h>
#include <ChainableLED.h>
#include <SoftwareSerial.h>
#include <Bridge.h>
#include <HttpClient.h>


SoftwareSerial CommunicationSerieRFID(8, 9);              //Cette librairie permet de créer plusieurs liaison série, nous en avons créer une, sur les port 8,9.
ChainableLED VoyantAcces(5, 6, 1);              //ChainableLED, permet de connecter plusieurs LED RGB en un seul port GROVE, dans notre cas nous avons 1 seul led, et nous l'avons connectés sur les port 7 et 6.
HttpClient Arduino;             //Au lieu d'avoir HttpClient.get(); nous pouvons avoir Arduino.get();.

unsigned char buffer[64];             //Création d'une chaîne de caractère qui peut être de maximum 255 caractères, et nous créons un buffer (stockage momentanné) qui peut sotcker maximum 64 caractères.
int count = 0;             //Création d'une variable int (codage d’un nombre entier sur 2 octets de -32768 à +32767).
boolean ValeurBoutonOuverture = false;             //Création d'une variable boulean (codage d’un nombre binaire sur 1 octet de valeur  true ou false).
String CodeBadge;             //Création d'une chaîne de caractère qui stocke rien.
String lejeunem = "0000A69C9BA1";             //Création d'une chaîne de caractère qui une suite de caractère qui correspond au code des badges de Maxime puis de Théo.
String fauchert = "19002B2B6178";
char MessageArrive[128] = "Bonjour, ";
String Desactive = "Désactivé";
String Active = "Activé";
byte ToutesLes30secCaVerifie = 0;


#define BoutonOuverture A0             //Nous définissons un port à une variable.

void setup()
{

  VoyantAcces.init();
  Bridge.begin();
  Wire.begin();
  SeeedOled.init();
  CommunicationSerieRFID.begin(9600);             //Nous définissons la vitesse de la communication série à 9600 bauds.
  SeeedOled.clearDisplay();                // Nettoie l'écran.
  SeeedOled.setNormalDisplay();                // L'écran est dans le mode par default.
  SeeedOled.setPageMode();                // Définir le mode d'adressage en mode Page.
  SeeedOled.setTextXY(0, 0);                // Met le curseur sur la ligne 0 et la colonne 0.
  SeeedOled.putString("Veuillez, passer");                // Affiche des espaces sur l'écran.
  SeeedOled.setTextXY(1, 0);              // Met le curseur sur la ligne 1 et la colonne 0.
  SeeedOled.putString("votre badge.");              // Affiche ce qui se situe entre les guillemet sur l'écran.
  digitalWrite(4, LOW);
  VoyantAcces.setColorRGB(0, 255, 0, 0);              //La couleur de la LED 0, est désormais rouge.

}



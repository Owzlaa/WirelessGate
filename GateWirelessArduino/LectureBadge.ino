unsigned char buffer[64];             //Création d'une chaîne de caractère qui peut être de maximum 255 caractères, et nous créons un buffer (stockage momentanné) qui peut sotcker maximum 64 caractères. 
int count = 0;             //Création d'une variable int (codage d’un nombre entier sur 2 octets de -32768 à +32767).
boolean ValeurBoutonOuverture = false;             //Création d'une variable boulean (codage d’un nombre binaire sur 1 octet de valeur  true ou false).
String CodeBadge;             //Création d'une chaîne de caractère qui stocke rien.
String lejeunem = "19002B2B6178";             //Création d'une chaîne de caractère qui une suite de caractère qui correspond au code des badges de Maxime puis de Théo.
String fauchert = "19002B2B6178";


void BoucleLectureInfiniLecteurRFID_Bouton()             //Création d'une boucle nommé "Re_DemarrerLeProgramme".
{

  ValeurBoutonOuverture  = digitalRead(BoutonOuverture);             //Le programme lit l'inforamtion du port 4 (#define BoutonOuverture 4) et la stocke dans la variable "#define BoutonOuverture 4".

  if (CommunicationSerieRFID.available())             //Si la communication série nommé "CommunicationSerieRFID" est activé alors ...
  {

    while (CommunicationSerieRFID.available())             //Tans que la communication série nommé "CommunicationSerieRFID" est activé alors ... 
    {

      buffer[count++] = CommunicationSerieRFID.read();             //On stocke l'information lu sur la communication série nommé "CommunicationSerieRFID" puis on la stocke dans le buffer qui a une capacité qui s'adapte.
      if (count == 64)break;             //Si la capcité de caractère que le buffer peut stocker est égale à 64 alors , le programme coupe la lecture du port série. Ceci est une sécurité.

    }

      //CommunicationSerieRFID.write(buffer, count);
      CodeBadge = buffer, count;
      count = 0;
    
   }

    //CodeBadge =  CommunicationSerieRFID.readString();

}

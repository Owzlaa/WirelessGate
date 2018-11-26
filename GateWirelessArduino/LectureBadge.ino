void loop()             //Création d'une boucle nommé "Re_DemarrerLeProgramme".
{

  ValeurBoutonOuverture = digitalRead(BoutonOuverture);

  if (CommunicationSerieRFID.available())             //Si la communication série nommé "CommunicationSerieRFID" est activé alors ...
  {

    while (CommunicationSerieRFID.available())             //Tans que la communication série nommé "CommunicationSerieRFID" est activé alors ...
    {

      buffer[count++] = CommunicationSerieRFID.read();             //On stocke l'information lu sur la communication série nommé "CommunicationSerieRFID" puis on la stocke dans le buffer qui a une capacité qui s'adapte.
      if (count == 64)break;             //Si la capcité de caractère que le buffer peut stocker est égale à 64 alors , le programme coupe la lecture du port série. Ceci est une sécurité.

    }

    CommunicationSerieRFID.write(buffer, count);     // if no data transmission ends, write buffer to hardware serial port
    count = 0;

  }

  CodeBadge =  CommunicationSerieRFID.readString();


  AutorisationOuverture();

  ToutesLes30secCaVerifie ++;
  delay(1000);

  if (ToutesLes30secCaVerifie == 30)
  {


    Arduino.get("gatewireless.ecolosia.me/post/activerdesactiver");
    String ActiverDesactiver = Arduino.readString();
    if (ActiverDesactiver.equals(Desactive))
    {
    
      SeeedOled.clearDisplay(); 
      SeeedOled.setTextXY(0, 0); // Met le curseur sur la ligne 0 et la colonne 0
      SeeedOled.putString("Acces"); // Affiche des espaces sur l'écran
      SeeedOled.setTextXY(1, 0); // Met le curseur sur la ligne 1 et la colonne 0
      SeeedOled.putString("impossible !"); // Affiche des espaces sur l'écran
      VoyantAcces.setColorRGB(0, 255, 0, 0);
      digitalWrite(4, LOW);

    }

    else if (ActiverDesactiver.equals(Active))
    {

      ToutesLes30secCaVerifie = 0;
      setup();

    }

    ToutesLes30secCaVerifie = 0;

  }

}

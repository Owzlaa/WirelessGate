void AutorisationOuverture()
{

    if ( CodeBadge.equals(lejeunem) || CodeBadge.equals(fauchert) || ValeurBoutonOuverture == 1)
    {
        SeeedOled.clearDisplay();                // Nettoie l'écran.
        SeeedOled.setTextXY(0, 0); // Met le curseur sur la ligne 4 et la colonne 3
        SeeedOled.putString(MessageArrive); // Affiche des espaces sur l'écran
        SeeedOled.setTextXY(1, 0);


          if ( CodeBadge.equals(lejeunem))
          {

              SeeedOled.putString("Mr Le Jeune"); // Affiche des espaces sur l'écran
              Arduino.get("gatewireless.ecolosia.me/post/lejeunem");

           }
           

          if ( CodeBadge.equals(fauchert))
          {

              SeeedOled.putString("Mr Faucher"); // Affiche des espaces sur l'écran
              Arduino.get("gatewireless.ecolosia.me/post/fauchert");

          }

              VoyantAcces.setColorRGB(0, 0, 255, 0);
               digitalWrite(4, HIGH);

              delay(8000);

              CodeBadge = " ";
              loop();
                  if ( CodeBadge.equals(lejeunem) || CodeBadge.equals(fauchert) || ValeurBoutonOuverture == 1)
                  {
                    
                      CodeBadge = " ";
                      loop();

                  }

              VoyantAcces.setColorRGB(0, 255, 0, 0);
              digitalWrite(4, LOW);
              Arduino.get("gatewireless.ecolosia.me/post/ferme");

              setup();
    }



}

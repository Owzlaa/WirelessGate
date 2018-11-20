char MessageArrive[128] = "Bonjour,";


void AutorisationOuverture()
{
    BoucleLectureInfiniLecteurRFID_Bouton();

    if ( CodeBadge.equals(lejeunem) || CodeBadge.equals(fauchert) || BoutonOuverture == 1)
    {

        SeeedOled.setTextXY(0, 0); // Met le curseur sur la ligne 4 et la colonne 3
        SeeedOled.putString(MessageArrive); // Affiche des espaces sur l'écran
        SeeedOled.setTextXY(2, 0);

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
              delay(1000);
              ServoPortail.write(angleOuverture);
              delay(8000);

              CodeBadge = " ";
              BoucleLectureInfiniLecteurRFID_Bouton();
             
                  while ( CodeBadge.equals(lejeunem) || CodeBadge.equals(fauchert) || ValeurBoutonOuverture == 1)
                  {

                      CodeBadge = " ";
                      BoucleLectureInfiniLecteurRFID_Bouton();

                  }

              ServoPortail.write(angleFermeture);
              VoyantAcces.setColorRGB(0, 255, 0, 0);
              Arduino.get("gatewireless.ecolosia.me/post/ferme");

              Re_DemarrerLeProgramme();

    }

    else if ( CodeBadge != lejeunem || CodeBadge != fauchert || ValeurBoutonOuverture == 0)
    {

        PortalActiverDesactiver();
      
    }


}

String Desactive = "Désactivé";
String Active = "Activé";
byte ToutesLes30secCaVerifie = 0;

void PortalActiverDesactiver()
{

    ToutesLes30secCaVerifie ++;
    delay(1000);

    if (ToutesLes30secCaVerifie == 30)
    {
        Arduino.get("gatewireless.ecolosia.me/post/activerdesactiver");

        if (Arduino.readString() == Desactive)
        {
         
            SeeedOled.setTextXY(0, 0); // Met le curseur sur la ligne 4 et la colonne 3
            SeeedOled.putString("Accès impossible"); // Affiche des espaces sur l'écran
          
        }

        else if (Arduino.readString() == Active)
        {

           ToutesLes30secCaVerifie = 0;
           Re_DemarrerLeProgramme();
          
        }

      ToutesLes30secCaVerifie = 0;
    
    }

  
}

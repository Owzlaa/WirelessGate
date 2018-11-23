const express = require('express'); //Déclérations des différents modules (ce n'est pas obligatoire, mais si vous n'avez pas installer le module, vous n'aurez pas d'erreur)
      fs = require('fs');
      bodyParser = require('body-parser');
      ejs = require('ejs');
 
let activerdesactiver; //Let, permet de créer une variable qui sotck une chaîne de caractère
let nomprenom;
    
let app = express();                    //Création d'un serveur web avec le module express, serveur hébergé sur le port 8080
    port = process.env.PORT | 8080;

app.use(bodyParser.urlencoded({
    extended: true
}))

app.set('view engine', 'ejs');  //EJS est un module, qui permet d'afficher un des variables particulières
app.set('views', "./views")


app.get('/', (req, res) => {    //Si le serveur reçois une requette http de type GET alors ...
    fs.readFile('files/ouvertferme.txt', (err, ouvertferme) => {    //Le serveur lit le contenu du fichier et le copie dans un variable nommé "ouvetrferme"
        fs.readFile('files/fichier1er.txt', (err, fichier1er) => {
            fs.readFile('files/fichier2nd.txt', (err, fichier2nd) => {
                fs.readFile('files/fichier3eme.txt', (err, fichier3eme) => {
                    res.render('index', {ouvertferme: ouvertferme, historique1er: fichier1er, historique2nd: fichier2nd, historique3eme: fichier3eme}); //Le serveur envoie la page web nommé "index" au client
                     
                    if (ouvertferme == "Activé")
                    {

                        fs.writeFile('files/ouvertferme.txt', 'Fermé', (err) => {});  

                    }
                
                
                });
            });
        });
    });
});



app.post('/post/etat/desactiver', (req, res) => {    //Si le serveur reçois une requette http de type POST alors sur cette URL... 

    fs.writeFile('files/ouvertferme.txt', 'Désactivé', (err) => {}); //Il écrit "Désactivé" dans le fichier "ouvertferme"
    activerdesactiver = 'Désactivé';    //activerdesactiver stock désormais "Désactivé"
    res.redirect('/');   //Pour finir, il redirige le client vers la première page
})

app.post('/post/etat/activer', (req, res) => {    //Même situation que juste au dessus

    fs.writeFile('files/ouvertferme.txt', 'Activé', (err) => {});
    activerdesactiver = 'Activé';
    res.redirect('/');

})

app.get('/post/activerdesactiver', (req, res) => {  //Cette partie de code est utilisé par l'Arduino, ceci permet de savoir si le portail est activé ou désactivé

    res.end(activerdesactiver); //Envoie au client soit l'Arduino le contenu de la variable "activerdesactiver"


})

app.get('/post/fauchert', (req, res) => { 

    nomprenom = 'Théo Faucher';
    fonction( req, res);    //Execute le fonction nommé "fonction"

})

app.get('/post/lejeunem', (req, res) => {

    nomprenom = 'Maxime Le Jeune';
    fonction( req, res);

})

function fonction( req, res)    //Fontion qui permet d'éxécuter à plusieurs endroits ce code, tout en étant à un seul endroit
{

    let my_date = new Date();   //Création d'une date nommé "my_date"
    let my_minute = my_date.getMinutes(); //Stock les minutes par rapport à l'heure qui l'est
    if(my_minute < 10) //Si ...
    {

        my_minute = "0" + my_minute; // On rajoute un 0 pour obtenir 09 au lieu de 9

    }

    let my_good_time =my_date.getHours() +1 + "h" + my_minute;  //Nous assemblons les différentes variables dans une chaîne de caractères
    fs.writeFile('files/ouvertferme.txt', 'Ouvert', (err) => {});
    fs.copyFileSync('files/fichier2nd.txt', 'files/fichier3eme.txt', (err) => {});  //Copie le contenue du fichier nommé "fichier2nd" dans le fichier nommé "fichier3eme"
    fs.copyFileSync('files/fichier1er.txt', 'files/fichier2nd.txt', (err) => {});
    fs.writeFile('files/fichier1er.txt',  nomprenom + " à " + my_good_time , (err) => {});
    res.end(my_good_time);

}

app.get('/post/ferme', (req, res) => {
    fs.writeFile('files/files/ouvertferme.txt', 'Fermé', (err) => {
    })
});

app.use((req, res, next) =>
{
    res.status(404).send("Erreur 404: Page non existante") //Cela envoie ce message si, l'URL, saisie est incorrect
});
  
app.use((err, req, res, next) =>
{
    console.error(err.stack)
    res.status(500).send('Quelque chose est cassé ! Désolé du dérangement')     //Si, le serveur rencontre un problème, il rend ca au client
});

app.listen(port, () =>
{
    console.log(`Server running on localhost:${port}`); //Ecrit dans la console ce message
});


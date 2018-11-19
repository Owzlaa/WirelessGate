const express = require('express');
      fs = require('fs');
      bodyParser = require('body-parser');
      ejs = require('ejs');
 
let activerdesactiver;
let nomprenom;
    
let app = express();
    port = process.env.PORT | 8080;

app.use("/favicon.ico", express.static('/views/favicon.ico')); 

app.use(bodyParser.urlencoded({
    extended: true
}))

app.set('view engine', 'ejs');
app.set('views', "./views")


app.get('/', (req, res) => {
    fs.readFile('files/ouvertferme.txt', (err, ouverferme) => {
        fs.readFile('files/fichier1er.txt', (err, fichier1er) => {
            fs.readFile('files/fichier2nd.txt', (err, fichier2nd) => {
                fs.readFile('files/fichier3eme.txt', (err, fichier3eme) => {
                    res.render('index', {ouvertferme: ouverferme, historique1er: fichier1er, historique2nd: fichier2nd, historique3eme: fichier3eme});
                });
            });
        });
    });
});



app.post('/post/etat/desactiver', (req, res) => {

    fs.writeFile('files/ouvertferme.txt', 'Désactivé', (err) => {});
    activerdesactiver = 'Désactivé';
    res.redirect('/');
})

app.post('/post/etat/activer', (req, res) => {

    fs.writeFile('files/ouvertferme.txt', 'Activé', (err) => {});
    activerdesactiver = 'Activé';
    res.redirect('/');

})

app.get('/post/activerdesactiver', (req, res) => {

    res.end(activerdesactiver);


})

app.get('/post/fauchert', (req, res) => {

    nomprenom = 'Théo Faucher';
    fonction( req, res);

})

app.get('/post/lejeunem', (req, res) => {

    nomprenom = 'Maxime Le Jeune';
    fonction( req, res);

})

function fonction( req, res)
{

    let my_date = new Date();
    let my_minute = my_date.getMinutes();
    if(my_minute < 10)
    {

        my_minute = "0" + my_minute;

    }
    let my_good_time =my_date.getHours() +1 + "h" + my_minute;
    fs.writeFile('files/ouvertferme.txt', 'Ouvert', (err) => {});
    fs.copyFileSync('files/fichier2nd.txt', 'files/fichier3eme.txt', (err) => {});
    fs.copyFileSync('files/fichier1er.txt', 'files/fichier2nd.txt', (err) => {});
    fs.writeFile('files/fichier1er.txt',  nomprenom + " à " + my_good_time , (err) => {});
    res.end(my_good_time);

}

app.get('/post/ferme', (req, res) => {
    fs.writeFile('files/files/ouvertferme.txt', 'Fermé', (err) => {
        res.end("Fermé")
    })
})

app.use((req, res, next) => {
    res.status(404).send("Erreur 404: Page non existante")
  })
  
  app.use((err, req, res, next) => {
    console.error(err.stack)
    res.status(500).send('Quelque chose est cassé ! Désolé du dérangement')
  })

app.listen(port, () => {
    console.log(`Le serveur est en local sur le port: ${port}`);
})
const express = require('express');
      fs = require('fs');
      bodyParser = require('body-parser');
      ejs = require('ejs'); 

let nomprenom;
    app = express();
    port = process.env.PORT | 8080;

app.use(bodyParser.urlencoded({
    extended: true
}))
app.set('view engine', 'ejs');
app.set('views', "./views")

app.get('/', (req, res) => {
    fs.readFile('ouvertferme.txt', (err, ouverferme) => {
        fs.readFile('fichier1er.txt', (err, fichier1er) => {
            fs.readFile('fichier2nd.txt', (err, fichier2nd) => {
                fs.readFile('fichier3eme.txt', (err, fichier3eme) => {
                    res.render('index', {ouvertferme: ouverferme, historique1er: fichier1er, historique2nd: fichier2nd, historique3eme: fichier3eme}); 
                });
            });
        });
    });
});


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
    if(my_minute <= 10)
    {

        my_minute = "0" + my_minute;

    }
    let my_good_time =my_date.getHours() +1 + "h" + my_minute;
    fs.writeFile('ouvertferme.txt', 'Ouvert', (err) => {});
    fs.copyFileSync('fichier2nd.txt', 'fichier3eme.txt', (err) => {});
    fs.copyFileSync('fichier1er.txt', 'fichier2nd.txt', (err) => {});
    fs.writeFile('fichier1er.txt',  nomprenom + " à " + my_good_time , (err) => {});
    res.end(my_good_time);



}

app.get('/post/ferme', (req, res) => {
    fs.writeFile('ouvertferme.txt', 'Fermé', (err) => {
        res.end("yes")
    })
})

app.listen(port, () => {
    console.log(`Server running on localhost:${port}`);
})
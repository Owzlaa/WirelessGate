const express = require('express');
const fs = require('fs');
const bodyParser = require('body-parser');
const ejs = require('ejs');

let test3 = 'Ferme';
let app = express();
let port = process.env.PORT | 8080;

app.use(bodyParser.urlencoded({
    extended: true
}))
app.set('view engine', 'ejs');
app.set('views', "./views")

app.get('/', (req, res) => {
    fs.readFile('fichier.txt', (err, data) => {
        // res.render('index', {kietrentre:data});
        fs.readFile('ouvertferme.txt', (err, data2) => {
            res.render('index', {kietrentre:data, test:test3}); 
        });
    });
});


app.get('/post/fauchert', (req, res) => {
    let my_date = new Date();
    let my_hour = my_date.getHours();
    let my_minute = my_date.getMinutes();
    let my_good_time = my_hour +1 + "h" + "0" + my_minute;
    fs.writeFile('fichier.txt',  " Théo Faucher à " + my_good_time , (err) => {});
    res.render('index', {test:"Ouvert"}); 
       res.end(my_good_time);
})

app.get('/post/lejeunem', (req, res) => {
    let my_date = new Date();
    let my_hour = my_date.getHours();
    let my_minute = my_date.getMinutes();
    let my_good_time = my_hour +1 + "h" + "0" + my_minute;
        fs.writeFile('fichier.txt', " Maxime Le Jeune à " + my_good_time, (err) => {});
        res.render('index', {test:"Ouvert"}); 
        res.end(my_good_time);
});



app.get('/post/ferme', (req, res) => {
    fs.writeFile('ouvertferme.txt', 'Fermé', (err) => {
        res.end("err")
    })
})

app.listen(port, () => {
    console.log(`Server running on localhost:${port}`);
})
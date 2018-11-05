const express = require('express');
const fs = require('fs');
const bodyParser = require('body-parser');
const ejs = require('ejs');

let my_date = new Date();

let my_hour = my_date.getHours();
let my_minute = my_date.getMinutes();

let my_good_time = my_hour + "h" + my_minute;



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
            res.render('index', {kietrentre:data, test:data2}); 
        });
    });
});


app.post('/post/fauchert', (req) => {
    fs.writeFile('fichier.txt',  " Théo Faucher à " + my_good_time , (err) => {});
    fs.writeFile('ouvertferme.txt', 'Ouvert', (err) => {});
    console.log(my_good_time);

})

app.post('/post/lejeunem', (req) => {
    fs.writeFile('fichier.txt', " Maxime Le Jeune à " + my_good_time, (err) => {});
    fs.writeFile('ouvertferme.txt', 'Ouvert', (err) => {});
    console.log(my_good_time);

})

app.post('/post/ferme', (req) => {
    fs.writeFile('ouvertferme.txt', 'Fermé', (err) => {});
    })

app.listen(port, () => {
    console.log(`Server running on localhost:${port}`);
});
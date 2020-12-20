var PORT = 8888

//Přidání potřebných modulů
var http = require("http");
var express = require('express');
var app = express();
var mysql = require('mysql');
var bodyParser = require('body-parser');
const { Console } = require("console");

/*
//Spojení s DB
var con = mysql.createConnection({
  host: 'backend_database',
  database: 'meteoData',
  port: '3306',
  user: 'root',
  password: 'Aa123456',
  insecureAuth : true
});

con.connect(function(err) {
  if (err) throw err;
  console.log("query.js Connected to database meteoData!");
});
*/

//Konfigurace JSON
app.use( bodyParser.json() );       // to support JSON-encoded bodies
app.use(bodyParser.urlencoded({     // to support URL-encoded bodies
  extended: true
}));



//Spuštění node.js serveru
var server = app.listen(PORT, function () {

  var host = server.address().address
  var port = server.address().port

  console.log("Api for Meteostanice listening at http://%s:%s", host, port)

  console.log(new Date().toISOString().replace(/T/, ' ').replace(/\..+/, ''));
});


//rest api to create a new record into mysql database
app.post('/novaData', function (req, res) {
  //var postDataCAS  = req.body.CAS;
  var postDataCAS = datumVeFormatu();
  var postDataTEPLOTA = req.body.TEPLOTA;
  var postDataVlhkost = req.body.VLHKOST;
  var postDataTlak = req.body.TLAK;
  var postDataCO2 = req.body.CO2;
  con.query('INSERT INTO teplota (TeplotaCas, TeplotaTeplota, TeplotaVlhkost, TeplotaTlak, TeplotaCO2) VALUES (?,?,?,?,?)', [postDataCAS, postDataTEPLOTA, postDataVlhkost, postDataTlak, postDataCO2], function (error, results, fields) {
   if (error) throw error;
   res.end(JSON.stringify(results));
 });
});

function datumVeFormatu(){
  var lepsiDatum = new Date().toISOString().replace(/T/, ' ').replace(/\..+/, '');
  return lepsiDatum;
}
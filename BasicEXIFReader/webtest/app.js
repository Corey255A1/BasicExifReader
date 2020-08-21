//WunderVison 2020 Simple Test Runner

'use strict';
const express = require('express');
const app = express();
var http = require('http');
const path = require('path');
var port = process.env.PORT || 1335;
app.use(express.static(__dirname + '/public'));

app.get('/',function(req,res){
    console.log("Sending")
    res.sendFile(path.join(__dirname, "public/runTestExif.html"));
});


const webServer = http.createServer(app).listen(port, () => {
    console.log("LISTENING HTTP!");
});
/*
app.js สำหรับสร้าง Protocol IoT device.
code.isaranu.com
coder : isaranu
created : 2017.Nov.11
updated : 2020.Oct.23
*/
const express = require('express');
const app = express();
var port = 4000;
var Promise = require('promise');

var mongojs = require('mongojs');
var myiotdb = mongojs('myiotdb');
var dhtdb = mongojs('dht');

var data0,data1,data2,data3, datasize;

app.get('/', function (req, res) {
  res.send("My IoT Protocol ready !");
});

app.get('/write/:data0/:data1/:data2/:data3/:data4', function (req, res) {
  data0 = req.params.data0;
  data1 = req.params.data1;
  data2 = req.params.data2;
  data3 = req.params.data3;
  data4  = req.params.data4;
  writedata(data0,data1,data2,data3,data4,res);
});

app.get('/read/:datasize', function (req, res) {
  datasize = req.params.datasize;
  readdata(datasize, res);
});

/* For DHT write */
app.get('/writedht/:a/:b/:c/:d', function (req, res) {
 // writeDHT(a_[0],a_[1],a_[2],a_[3], res);
});

/* For DHT data read */
app.get('/readdht/:datasize', function (req, res) {
  datasize = req.params.datasize;
  readDHT(datasize, res);
});

app.listen(port, function () {
  var nodeStartTime = new Date();
  console.log('My IoT protocol running on port ' + port + ' start at ' + nodeStartTime);
});

/* -- ASYNC / AWAIT function -- */
async function writedata(_data0,_data1,_data2,_data3,_data4, res){
  await writeDataToMongo(_data0,_data1,_data2,_data3,_data4, res);
}

function writeDataToMongo(_data0,_data1,_data2,_data3,_data4,res){
  return new Promise(function(resolve, reject){
    var mywritecollection = myiotdb.collection('mycollection');
    mywritecollection.insert({
      data: [_data0,_data1,_data2,_data3],
      win : _data4,
      recordTime: new Date().getTime()
    }, function(err){
      if(err){
        console.log(err);
        res.send(String(err));
      }else {
        console.log('record data ok');
        res.send('record data ok');
      }
    });
  });
}

async function readdata(_datasize, res){
  await readDataFromMongo(_datasize, res);
}

function readDataFromMongo(_readdatasize, res){
  return new Promise(function(resolve,reject){
    var myreadcollection = myiotdb.collection('mycollection');
    myreadcollection.find({}).limit(Number(_readdatasize)).sort({recordTime: -1}, function(err, docs){
      res.jsonp(docs.reverse());
    });
  });
}

async function writeDHT(_t, _h, res){
  await writeDHTtoMongo(_t, _h, res);
}

function writeDHTtoMongo(_saveA, _saveB,_saveC,_saveD, res){
  return new Promise(function(resolve, reject){
    var dhtwritecollection = dhtdb.collection('dhtcol');
    dhtwritecollection.insert({
     data: [_saveA, _saveB,_saveC,_saveD],
      recordTime: new Date().getTime()
    }, function(err){
      if(err){
        console.log(err);
        res.send(String(err));
      }else {
        console.log('record dht data ok');
        res.send('record dht data ok');
      }
    });
  });
}

async function readDHT(_datasize, res){
  await readDHTFromMongo(_datasize, res);
}

function readDHTFromMongo(_readdatasize, res){
  return new Promise(function(resolve,reject){
    var dhtcollection = dhtdb.collection('dhtcol');
    dhtcollection.find({}).limit(Number(_readdatasize)).sort({recordTime: -1}, function(err, docs){
      res.jsonp(docs.reverse());
    });
  });
}

//erwecrwwihilmhlkfhal;khfan;klcf
//awdadadasdasd
//d;fjfxn;oidsfjd;cfl;ds
//asdasdd

//adasdadd
//aMASDasdasdd
#include <ESP8266WebServer.h>
#include <EEPROM.h>
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClient.h>
#include <SoftwareSerial.h>
#include <WiFiUdp.h>
#include <NTPClient.h>
#include <SoftwareSerial.h>

#define IP_MANUAL false
#define MANUAL_IP_ADDRESS IPAddress(192, 168, 18, 10)  // Endereço IP manual
#define MANUAL_IP_GATEWAY IPAddress(192, 168, 18, 1)    // Gateway manual
#define MANUAL_IP_SUBNET IPAddress(255, 255, 255, 0)   // Máscara de sub-rede manual
WiFiClient wifiClient;
HTTPClient http;


long unsigned int tempo_led = millis();



const char *ssid = "PROJETO GUSTAVO"; // Nome da rede WiFi que será criada
const char *password = "gustavo2023";   // Senha para se conectar nesta rede
ESP8266WebServer server(80); //Server utiliza a porta 80

//String BASE_URL = "http://10.0.0.105:11050/";

String BASE_URL = "http://162.240.226.254/apileite/";
String path_pulsar = "v1/sessoes/platfomr/pulsar/";
String path_encerrar = "v1/sessoes/platfomr/encerrar/";

#define rxPin D1
#define txPin D0
SoftwareSerial arduino(rxPin, txPin);

long unsigned int tempo_msg = millis();
const char MAIN_page[] PROGMEM = R"=====(
<!DOCTYPE html>
<html>
<head>
  <meta http-equiv="Content-Type" content="text/html; charset=utf-8">
  <title>HTML Form ESP8266 - TITANIWM</title>
  <style>
    body {color: #434343; font-family: "Helvetica Neue",Helvetica,Arial,sans-serif; font-size: 14px; background-color: #eeeeee; margin-top: 100px;}
    .container {margin: 0 auto; max-width: 400px; padding: 30px; box-shadow: 0 10px 20px rgba(0,0,0,0.19), 0 6px 6px rgba(0,0,0,0.23); background-color: #ffffff; border-radius: 10px;}
  h2 {text-align: center; margin-bottom: 20px; margin-top: 0px; color: #0ee6b1; font-size: 35px;}
  #titleGreen {color: #00E1AA;}
  #titleBlack {color: #000000;}
    h3 {text-align: center; margin-bottom: 40px; margin-top: 0px; color: #336859; font-size: 35px;}
    form .field-group {box-sizing: border-box; clear: both; padding: 4px 0; position: relative; margin: 1px 0; width: 100%;}
    .text-field {font-size: 15px; margin-bottom: 4%; -webkit-appearance: none; display: block; background: #fafafa; color: #636363; width: 100%; padding: 15px 0px 15px 0px; text-indent: 10px; border-radius: 5px; border: 1px solid #e6e6e6; background-color: transparent;}
    .text-field:focus {border-color: #00bcd4; outline: 0;}
    .button-container {box-sizing: border-box; clear: both; margin: 1px 0 0; padding: 4px 0; position: relative; width: 100%;}
    .button {background: #00E1AA; border: none; border-radius: 5px; color: #ffffff; cursor: pointer; display: block; font-weight: bold; font-size: 16px; padding: 15px 0; text-align: center; text-transform: uppercase; width: 100%; -webkit-transition: background 250ms ease; -moz-transition: background 250ms ease; -o-transition: background 250ms ease; transition: background 250ms ease;}
    p {text-align: center; text-decoration: none; color: #87c1d3; font-size: 18px;}
    a {text-decoration: none; color: #ffffff; margin-top: 0%;}
    #status {text-align: center; text-decoration: none; color: #336859; font-size: 14px;}
  </style>
  <script>
  function validateForm() {
    var ssid = document.forms["myForm"]["ssid"].value;
    var password = document.forms["myForm"]["password"].value;
    var status = document.getElementById("statusDiv");
    if (ssid == "" && password == "") {
    status.innerHTML = "<p id='status' style='color:red;'>Insira SSID e senha.</p>";
    return false;
    }
    else if (ssid == "") {
    status.innerHTML = "<p id='status' style='color:red;'>Insira SSID.</p>";
    return false;
    }
    else if (password == "") {
    status.innerHTML = "<p id='status' style='color:red;'>Insira senha.</p>";
    return false;
    }
    else {
    status.innerHTML = "<p id='status'>Conectando...</p>";
    return true;
    }
  }
  </script>
</head>
<body>
<div class="container">
  <h2><span id="titleBlack">TITANIWM</span></h2>
  <h3>Conexão ESP8266</h3>
  <form name="myForm" action="/action_new_connection" onsubmit="return validateForm()" method="post">
    <div class="field-group">
  <select class='text-field' name='ssid'></select>
    </div>
    <br>
    <div class="field-group">
    <input class="text-field" type="password" name="password" length=64 placeholder="Password">
    </div>
  <br>
  <div id="statusDiv">
    <br><br>
  </div>
    <div class="button-container">
    <input class="button" type="submit" value="Conectar">
    </div>
  </form>
  <p>OU</p>
  <div class="button-container">
    <button class="button" type="button" onclick="window.location.href='/action_previous_connection'">Conectar à última rede utilizada</button>
  </div>
</div>
</body>
</html>
)=====";

void setup() {


  Serial.begin(115200);

  arduino.begin(38400);


  WiFi.softAP(ssid, password);
  Serial.print("Access Point \"");
  Serial.print(ssid);
  Serial.println("\" iniciado");

  Serial.print("IP address:\t");
  Serial.println(WiFi.softAPIP());


  //Tratamento de rotas
  server.on("/", handleRoot);
  server.on("/action_new_connection", handleForm);
  server.on("/action_previous_connection", connectEeprom);

  server.begin();
  Serial.println("Servidor HTTP iniciado");

  connectEeprom();


  Serial.print(WiFi.localIP());



  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, LOW);


}


void loop() {
  piscarLed(); //Pisca o led para sinalizar que o nodemcu está em execução


  server.handleClient();          //Trata requisições de clientes
  if (WiFi.status() != WL_CONNECTED) {
  }

  if (arduino.available() > 0) {

    String mensagem = arduino.readString();
    Serial.print("Mensagem do uno: ");
    Serial.println(mensagem);

    int arroba = mensagem.indexOf("@");
    int sifrao = mensagem.indexOf("$");
    int hashtag = mensagem.indexOf("#");

    if (arroba == 0 && hashtag > 0 && sifrao > 0) {

      String tipo_requisicao = mensagem.substring(arroba + 1, sifrao);
      String canal = mensagem.substring(sifrao + 1, hashtag);

      int Itipo_requisicao = tipo_requisicao.toInt();
      int Icanal = canal.toInt();

      if (Itipo_requisicao > 0 && Icanal > 0) {
        if (Itipo_requisicao == 1) {
           Serial.print("Pulsar");
           pulsar(Icanal);
           
        }

        if (Itipo_requisicao == 2) {
            Serial.print("Encerrar");
             encerrar(Icanal);

        }

      }



    }



  }

}




  void piscarLed() {
    if (millis() - tempo_led > 1000) {
      digitalWrite(LED_BUILTIN, !digitalRead(LED_BUILTIN));

      tempo_led =  millis();
    }

  }


  void handleRoot() {
    String index = listSSID(); //Leia o conteúdo HTML
    server.send(200, "text/html", index); //Enviar pagina Web
  }

  void handleForm() {
    String ssidWifi = server.arg("ssid");
    String passwordWifi = server.arg("password");

    Serial.printf("SSID: %s\n", ssidWifi);
    Serial.printf("Password: %s\n", passwordWifi);

    if (!ssidWifi.equals("") && !passwordWifi.equals("")) {
      connectToWiFi(ssidWifi, passwordWifi);
    }
  }

  void connectToWiFi(String ssidWifi, String passwordWifi) {
    int count = 0;

    if (IP_MANUAL) {
      IPAddress manualIP(MANUAL_IP_ADDRESS);
      IPAddress manualGateway(MANUAL_IP_GATEWAY);
      IPAddress manualSubnet(MANUAL_IP_SUBNET);

      WiFi.config(manualIP, manualGateway, manualSubnet);  // Configuração do IP manual
    }



    WiFi.begin(ssidWifi.c_str(), passwordWifi.c_str());     //Conecta com seu roteador
    Serial.println("");

    //Espera por uma conexão
    while ( count < 40 ) {
      delay(500);
      Serial.print(".");
      if (WiFi.status() == WL_CONNECTED) {
        Serial.println("");
        salvarEeprom(ssidWifi, passwordWifi);
        Serial.println("");
        //Se a conexão ocorrer com sucesso, mostre o endereço IP no monitor serial
        Serial.println("Conectado ao WiFi");


        Serial.print("IP address: ");
        Serial.println(WiFi.localIP());  //Endereço IP do ESP8266




        String responsePage = (const __FlashStringHelper*) MAIN_page; //Leia o conteúdo HTML
        responsePage.replace("<br><br>", "<p id='status'>Conectado!</p>");
        server.send(200, "text/html", responsePage);
        return;
      }
      else if (WiFi.status() == WL_CONNECT_FAILED) {
        String responsePage = (const __FlashStringHelper*) MAIN_page;
        responsePage.replace("<br><br>", "<p id='status' style='color:red;'>Falha na conexão.</p>");
        server.send(200, "text/html", responsePage);
      }
      count++;
    }
    Serial.println();
    Serial.println("Timed out.");
    String responsePage = (const __FlashStringHelper*) MAIN_page;
    responsePage.replace("<br><br>", "<p id='status' style='color:red;'>Erro.</p>");
    server.send(200, "text/html", responsePage);
    return;
  }

  String listSSID() {
    String index = (const __FlashStringHelper*) MAIN_page; //Leia o conteúdo HTML
    String networks = "";
    int n = WiFi.scanNetworks();
    Serial.println("Scan done.");
    if (n == 0) {
      Serial.println("Nenhuma rede encontrada.");
      index.replace("<select class='text-field' name='ssid'></select>", "<select class='text-field' name='ssid'><option value='' disabled selected>Nenhuma rede encontrada</option></select>");
      index.replace("<br><br>", "<p id='status' style='color:red;'>Rede não encontrada.</p>");
      return index;
    }
    else {
      Serial.printf("%d networks found.\n", n);
      networks += "<select class='text-field' name='ssid'><option value='' disabled selected>SSID</option>";
      for (int i = 0; i < n; ++i)
      {
        // Imprime o SSID de cada rede encontrada
        networks += "<option value='" + WiFi.SSID(i) + "'>" + WiFi.SSID(i) + "</option>";
      }
      networks += "</select>";
    }
    index.replace("<select class='text-field' name='ssid'></select>", networks);
    return index;
  }

  void salvarEeprom(String ssidWifi, String passwordWifi) {
    EEPROM.begin(98); // Tamanho da FLASH reservado para EEPROM. Pode ser de 4 a 4096 bytes

    if (!compareEeprom(ssidWifi, passwordWifi)) {
      Serial.println("Salvando:");
      EEPROM.write(0, ssidWifi.length());
      Serial.println(ssidWifi.length());

      for (int i = 2; i < 2 + ssidWifi.length(); i++) {
        Serial.print(ssidWifi.charAt(i - 2));
        EEPROM.write(i, ssidWifi.charAt(i - 2));
      }
      Serial.println("");

      Serial.println("Salvando:");
      EEPROM.write(1, passwordWifi.length());
      Serial.println(passwordWifi.length());

      for (int j = 2 + ssidWifi.length(); j < 2 + ssidWifi.length() + passwordWifi.length(); j++) {
        Serial.print(passwordWifi.charAt(j - 2 - ssidWifi.length()));
        EEPROM.write(j, passwordWifi.charAt(j - 2 - ssidWifi.length()));
      }
      Serial.println("");

      EEPROM.commit(); // Salva alterações na FLASH
    }
    EEPROM.end(); // Apaga a cópia da EEPROM salva na RAM
  }

  boolean compareEeprom(String ssidWifi, String passwordWifi) {
    int idLength = int(EEPROM.read(0)); // Tamanho do SSID armazenado (número de bytes)
    int passLength = int(EEPROM.read(1)); // Tamanho do Password armazenado (número de bytes)
    String id = "";
    String pass = "";

    Serial.println("Lendo SSID:");
    Serial.print("Tamanho:");
    Serial.println(idLength);
    for (int i = 2; i < 2 + idLength; i++) {
      Serial.print("Posição ");
      Serial.print(i);
      Serial.print(": ");
      id = id + char(EEPROM.read(i));
      Serial.println(id[i - 2]);
    }
    Serial.println("");

    Serial.println("Lendo senha:");
    Serial.print("Tamanho:");
    Serial.println(passLength);
    for (int j = 2 + idLength; j < 2 + idLength + passLength; j++) {
      Serial.print("Posição ");
      Serial.print(j);
      Serial.print(": ");
      pass = pass + char(EEPROM.read(j));
      Serial.println(pass[j - 2 - idLength]);
      Serial.println(pass);
    }
    Serial.println("");

    Serial.print("SSID é igual: ");
    Serial.println(id.equals(ssidWifi));

    Serial.print("Senha é igual: ");
    Serial.println(pass.equals(passwordWifi));

    if (id.equals(ssidWifi) && pass.equals(passwordWifi))
    {
      Serial.println("Dados já presentes na memória.");
      return true;
    }
    else
    {
      return false;
    }
  }

  void connectEeprom() {
    EEPROM.begin(98); // Tamanho da FLASH reservado para EEPROM. Pode ser de 4 a 4096 bytes

    int ssidSize = (int)EEPROM.read(0); // Tamanho do SSID armazenado (número de bytes)
    int passwordSize = (int)EEPROM.read(1); // Tamanho do Password armazenado (número de bytes)
    String ssidWifi = "";
    String passwordWifi = "";

    Serial.println("Lendo:");
    for (int i = 2; i < 2 + ssidSize; i++) {
      Serial.print(char(EEPROM.read(i)));
      ssidWifi.concat(char(EEPROM.read(i)));
    }
    Serial.println("");

    Serial.println("Lendo:");
    for (int j = 2 + ssidSize; j < 2 + ssidSize + passwordSize; j++) {
      Serial.print(char(EEPROM.read(j)));
      passwordWifi.concat(char(EEPROM.read(j)));
    }
    Serial.println("");

    EEPROM.end(); // Apaga a cópia da EEPROM salva na RAM

    Serial.println("Leu:");
    Serial.println(ssidWifi);
    Serial.println(passwordWifi);

    connectToWiFi(ssidWifi, passwordWifi);
  }


String pulsar(int canal) {

    Serial.println("Pulsar");

    http.begin(wifiClient, BASE_URL + path_pulsar  + canal);
    http.addHeader("content-type", "application/json");


    int httpCode = http.GET();
    if (httpCode < 0) {
      Serial.println("request error - " + httpCode);
      return "request error - " + httpCode;
    }
    if (httpCode != HTTP_CODE_OK) {
      Serial.println("request error - " + httpCode);
      return "";
    }
    String response =  http.getString();
    Serial.print("Responda da api: ");
    Serial.println(response);
    http.end();

    Serial.println("Feito");


    return response;
  }


  String encerrar(int canal) {

    Serial.println("Pulsar");

    http.begin(wifiClient, BASE_URL + path_encerrar  + canal);
    http.addHeader("content-type", "application/json");


    int httpCode = http.GET();
    if (httpCode < 0) {
      Serial.println("request error - " + httpCode);
      return "request error - " + httpCode;
    }
    if (httpCode != HTTP_CODE_OK) {
      Serial.println("request error - " + httpCode);
      return "";
    }
    String response =  http.getString();
    Serial.print("Responda da api: ");
    Serial.println(response);
    http.end();

    Serial.println("Feito");


    return response;
  }
